<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="basic_style.css">
  </head>
<body>


<?php

  // exec("make");
  exec("chmod 775 view.py");
  if (isset($_POST[username])) {

    if (isset($_POST[streamname])) {
      
      if (isset($_POST[order])) {
        if (!isset($_POST[messageNumber])) {
          $_POST[messageNumber] = -1;
        }
        // load viewer
        if (isset($_POST[markAll])) {
          if ($_POST[markAll] == "read") {
            exec("./db -mark \"$_POST[username]\" \"$_POST[streamname]\" all", $output, $status);
            if ($status) {
              $_POST[updateMessage] = "<p id=error> Error! Could not mark all posts in the $_POST[streamname] stream as read</p>";
            }
            else {
              $_POST[updateMessage] = "<p id=success>" . $output[0] . "</p>";
            }
          }
          if ($_POST[markAll] == "unread") {
            exec("./db -mark \"$_POST[username]\" \"$_POST[streamname]\" none", $output, $status);
            if ($status) {
              $_POST[updateMessage] = "<p id=error> Error! Could not mark all posts in the $_POST[streamname] stream as unread</p>";
            }
            else {
              $_POST[updateMessage] = "<p id=success>" . $output[0] . "</p>";
            }
          }
        }
        $cmd = 'make get_page IN="viewer.wpml"';
      }
      elseif (isset($_POST[sendPost])) {

        if ( !isset($_POST[postContent]) || $_POST[postContent] == "enter your new post here." || strlen($_POST[sendPost]) < 1 || (strlen($_POST[sendPost]) > 0 && strlen(trim($_POST[sendPost])) < 1)) {
          // postContent is invalid
          // set updateMessage
          $_POST[updateMessage] = "<p id=\"error\">Error: User's post must not be empty. Please try again.</p>";
          // back to dashboard
          $cmd = 'make get_page IN="dashboard.wpml"';
        }
        else {
          // send post to ./post program
          $postContent = escapeshellarg($_POST[postContent]);

          $cmd = "./post \"$_POST[username]\" \"$_POST[streamname]\" $postContent";
          exec($cmd, $output, $status);
          $usr = $_POST[username];
          $msg = "";
          if ($status) {
            $msg = "<p id=\"error\">Error: failed to post.</p>";
          }
          else {
            foreach ($output as $line) {
               $msg .= $line;
            }
          }
          $_POST = array();
          $_POST[updateMessage] = $msg;
          $_POST[username] = $usr;
          $cmd = 'make get_page IN="dashboard.wpml"';
        }
      }
      elseif (isset($_POST[sendAddUser])) {
        // run ./addauthor with username, new streamname, & add flag
        $cmd = "./addauthor \"$_POST[username]\" \"$_POST[streamname]\" \"add\"";
        exec($cmd, $output, $status);
        $msg = "";
        if ($status) {
          $msg = "<p id=\"error\">Error: failed to post.</p>";
        }
        else {
          foreach ($output as $line) {
              $msg .= $line;
          }
        }
        $_POST = array();
        $_POST[updateMessage] = $msg;
        $cmd = 'make get_page';
      }
      elseif (isset($_POST[sendRemoveUser])) {
        // run ./addauthor with username, new streamname, & remove flag
        $cmd = "./addauthor \"$_POST[username]\" \"$_POST[streamname]\" \"remove\"";
        exec($cmd, $output, $status);
        $msg = "";
        if ($status) {
          $msg = "<p id=\"error\">Error: failed to post.</p>";
        }
        else {
          foreach ($output as $line) {
              $msg .= $line;
          }
        }
        $_POST = array();
        $_POST[updateMessage] = $msg;
        $cmd = 'make get_page';
      }
    }
    elseif (isset($_POST[dashboard])) {
      // load dashboard for user
      $cmd = 'make get_page IN="dashboard.wpml"';
    }
    else {
      // username is only thing that is set -- load dashboard
      $cmd = 'make get_page IN="dashboard.wpml"';
    }
  }
  elseif (isset($_POST[add])) {
    // load "add_user" page
    $cmd = 'make get_page IN="add_user.wpml"';
  }
  elseif (isset($_POST[remove])) {
    // load "add_user" page
    $cmd = 'make get_page IN="remove_user.wpml"';
  }
  else {
    $cmd = 'make get_page'; // IN defaults to home.wpml in Makefile
  }

  if (isset($_POST[updateMessage])) {
    echo $_POST[updateMessage];
  }

  exec($cmd, $output, $status);
  if ($status) {
    echo "Error: could not load page.<br />";
    echo '<form action="index.php" method="post"><input type="submit" value="home"</form>';
  }
  else {
    $indexCallOutput = $output;
    $endIndex = sizeof($indexCallOutput);
    $i = 0;
    $phpCode = " ";
    while ($i < $endIndex && $indexCallOutput[$i-1] != "<START>") {
      $i++; // skip echo of make commands
    }
    while ($i < $endIndex) {
      if (strpos($indexCallOutput[$i], 'echo') !== false && strpos($indexCallOutput[$i], ';') !== false) {
        eval($indexCallOutput[$i]);
      }
      elseif ($indexCallOutput[$i] == '<?php') {
        $i++;
        while ($indexCallOutput[$i] != '?>') {
          $phpCode .= $indexCallOutput[$i];
          $i++;
        }
        // ob_start();
        // echo "STARTPHP" . $phpCode . "ENDPHP <br />";
        eval($phpCode);
        $phpCode = NULL;
        // $evaluatedCode = ob_get_contents();
        // ob_end_clean();
        // echo $evaluatedCode;
        // echo "<hr><b>STARTEVAL<br />$evaluatedCode <br />ENDEVAL</b><hr>";
        $i++; // skip php end tag
      }
      else {
        echo $indexCallOutput[$i];
      }
      $i++;
    }
  }
?>
</body>
</html>