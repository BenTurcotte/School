#! /usr/bin/python

# ------------------------------------------------------------------------------
#        Name:  Ben Turcotte
#  Student ID:  Bturcott
#   Student #:  0832217
#       Email:  bturcott@mail.uoguelph.ca
#       Class:  CIS*2750
#  Assignment:  2, "view" program (used in succeeding assignments as well)
# ------------------------------------------------------------------------------
# Note: this program now retrieves data by using an external program 'db'
#       rather than retrieving data from text files.
# ------------------------------------------------------------------------------

import sys, glob, io, re, os, subprocess

# utility functions ------------------------------------------------------------
def is_whitespace(string):
  string = re.sub(r'\s+', '', string)
  if len(string):
    return False
  else:
    return True


# functions for STREAMS --------------------------------------------------------
def get_streams_list(username):
  cmd = './db -streams \"' + username + '\"'
  exec_output = os.popen(cmd)
  out_str = exec_output.read()
  
  streams = list()
  if 'no streams' not in out_str:
    streams = out_str.split("\n")
    for eachStream in streams:
      if is_whitespace(eachStream):
        streams.remove(eachStream)
    
  return streams

def stream_list_to_html_form(username, streamList):
  if not streamList or '- no streams -' in streamList:
    print("<b>User does not yet belong to any streams.</b><br />")
    print("You may add a user from the home page (button at top).")
  else:
    print("<form action=\"index.php\" method=\"post\">")
    print("Stream: <select name=\"streamname\">")
    print("  <option value=\"all\"> all</option>")
    for eachStream in streamList:
      print("  <option value=\"" + eachStream + "\"> " + eachStream + "</option>")
    print("</select>")
    print("  Order: <select name=\"order\">")
    print("  <option value=\"newAtTop\"> Newest post at the top</option>")
    print("  <option value=\"oldAtTop\"> Oldest post at the top</option>")
    print("</select>  ")
    print("<input type=\"hidden\" name=\"username\" value=\"" + username + "\" />")
    print("<input type=\"submit\" align=\"right\" value=\"start viewing\" />")
    print("</form>")


def stream_list_to_html_select(username, streamList):
  if not streamList:
    print("<input type=\"hidden\" name\"errorMessage\"")
    print("value=\"User does not yet belong to any streams.<br />\"")
  else:
    print("Stream: <select name=\"streamname\">")
    for eachStream in streamList:
      print("  <option value=\""+ eachStream +"\"> "+ eachStream +"</option>")
    print("</select><br />")


# functions for POSTS --------------------------------------------------------
def get_date_from_post(postStr):
  date = re.sub(r'(\s|\w|:|<|/|>|\?|\!|\.|,|\'|\"|-)*Date: ', '', postStr)
  date = re.sub(r'<br />(\s|\w|:|<|/|>|\?|\!|\.|,|\'|\"|-|:|;|$|~|`|@|#|%|\^|&|\*|\(|\)|\[|\]|\{|\}|\\)*', '', date)
  return date


def sort_postList_by_date(postList):
  postDict = {}
  dates = list()
  for eachPost in postList:
    date = get_date_from_post(eachPost)
    dates.append(date)
    postDict[date] = eachPost
  
  sortedDates = sorted(dates)
  del postList[:]
  for eachDate in sortedDates:
    postList.append(postDict[eachDate])
  
  return postList


def get_ordered_postList(username, streamname, order):
  cmd = './db -posts \"' + username + '\" \"' + streamname + '\"'
  exec_output = os.popen(cmd)
  out_str = exec_output.read()
  rawPostList = out_str.split("\t\t\t\n")
  
  cleanPostList = list()
  for eachPost in rawPostList:
    if not is_whitespace(eachPost):
      eachPost = re.sub(r'\+(-){131}\+', '', eachPost)
      eachPost = re.sub(r'\| message( ){123}\|', '', eachPost)
      cleanPostList.append(eachPost)
  
  cleanPostList = sort_postList_by_date(cleanPostList)
  
  if 'newAtTop' in order:
    return cleanPostList[::-1]
  else:
    return cleanPostList


def post_to_html_p_str(post):
  if not is_whitespace(post):
    post = re.sub(r'(\s|\w|:|<|/|>|\?|\!|\.|,|\'|\")*User: ', '<b>User:</b> ', post)
    post = re.sub(r'Date:', '<b>Date:</b>', post)
    post = re.sub(r'Stream:', '<b>Stream:</b>', post)
    post = re.sub(r'\n', ' ', post)
    post = re.sub(r'\r', ' ', post)
    return '<p id=\"postView\">\n' + post + '\n</p>\n'
  else:
    return ''


def postList_to_html_p_str(postList):
  html_str = ''
  if not postList or '- no posts yet -' in postList:
    html_str = "<p id=\"postView\"><b> no posts yet. </b></p>"
  else:
    for eachPost in postList:
      html_str += post_to_html_p_str(eachPost)
  return html_str


# functions for READ COUNT -----------------------------------------------------
def update_reads(streamName, username, numRead):
  printf("update_reads not complete.")

def get_num_read(username, streamname):
  printf("get_num_read not complete.")

def increment_read_count(username, streamname):
  printf("increment_read_count not complete.")

def get_index_of_post(username, streamname, reverseFlag, thePostToFind):
  postList = get_ordered_postList(username, streamname, reverseFlag)
  htmlPostList = list()
  for eachPost in postList:
    htmlPostList.append(post_to_html_p_str(eachPost))
  
  if thePostToFind in htmlPostList:
    return postList.index(thePostToFind)
  else:
    return -1;


# functions for making POST HTML PAGE ------------------------------------------
def setup_post(username, streamList):
  if not streamList or streamList[0] == "- no streams -":
    print("<b>User does not yet belong to any streams.</b><br />")
    print("You may add a user from the home page (button at top).")
  else:
    print("<form action=\"index.php\" id=\"postForm\" method=\"post\">")
    print("<textarea name=\"postContent\" id=\"textarea_post\" form=\"postForm\" rows=\"10\" cols=\"60\" placeholder=\"enter your new post here.\"></textarea><br />")
    print("Stream: <select name=\"streamname\">")
    for eachStream in streamList:
      print("  <option value=\"" + eachStream + "\"> " + eachStream + "</option>")
    print("</select>")
    print("<input type=\"hidden\" name=\"username\" value=\"" + username + "\" />")
    print("<input type=\"hidden\" name=\"sendPost\" value=\"yes\" />")
    print("<input type=\"submit\" value=\"send post\" />")
    print("</form>")


# ------------------------------------------------------------------------------
''' ------------------------------------------------------------------- MAIN '''
# sys.stderr = sys.stdout # open('errorlog.txt', 'w')

# output each post as separate html paragraphs
if len(sys.argv) == 5: # view.py, username, streamname, order, messageNumber
  postList = get_ordered_postList(sys.argv[1], sys.argv[2], sys.argv[3])
  print(postList_to_html_p_str(postList))
  
# output streams list HTML select block/tag for specific username
elif len(sys.argv) == 3 and sys.argv[2] == "GiveMeSelect":
  print("<p>Gimme Sel START</p>")
  availableStreams = get_streams_list(sys.argv[1])
  stream_list_to_html_select(sys.argv[1], availableStreams)
  print("<p>Gimme Sel END</p>")

# output HTML form for POST for specific username
elif len(sys.argv) == 3 and sys.argv[2] == "SetupPost":
  availableStreams = get_streams_list(sys.argv[1])
  setup_post(sys.argv[1], availableStreams)

# output posts from stream(s) for username, newest at the top
elif len(sys.argv) == 3: # view.py, username, streamname
  postList = get_postList(sys.argv[1], sys.argv[2], "newestAtTop")
  for eachPost in postList:
    print(eachPost)

# output list of streams username belongs to
elif len(sys.argv) == 2: # view.py, username
  availableStreams = get_streams_list(sys.argv[1])
  stream_list_to_html_form(sys.argv[1], availableStreams)
  

# -------------------------------------------------------------------------- END