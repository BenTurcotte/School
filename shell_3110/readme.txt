Ben Turcotte
Bturcott - 0832217

CIS*3110 Assignment 1

DESCRIPTION:
This program is a basic shell program. My custom command "genbin n" prints all
binary strings of length n in lexographic order.


Algorithm:

Start always-true loop

args <-- getln()

set input stream to file if "<" is present
set output strem to file if ">" is present
set wait flag if "&" is present"

if first arg is "exit", then exit program

else if first arg is "add", then compute sum of all args excluding the first

else if first arg is "arg", then run small function to print arg count & list of args

else if first arg is "bingen", then check if a second argument was given
    if no argument given, then error message, back to top of loop
    else run my binary string generator function

else
    create child process
    attempt to run execvp command
    if not success print "invalid command"
    else back to top of loop

end loop


Bugs:

1. "input in flex scanner failed"

    Not sure what this is all about... tried a bunch of different potential
    solutions to no avail. I have come to the concusion that its a problem
    with the parser that was provided.

    Occurs when the following command is entered:
    $ sort < inputFile

    Sort works fine, the sorted contents of inputFile are printed to the screen
    then the error message prints to the screen and the program terminates.

2. Segmentation fault when trying to run process in the background (using "&")

    I believe this error has something to do with sigset. Can't seem to figure
    out how it works. Documentation is unclear & difficult to understand.

3. Infinite loop occurs when trying to read an input file
