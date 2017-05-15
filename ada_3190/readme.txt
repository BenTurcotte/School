================================================================================
        Name:  Ben Turcotte
  Student ID:  Bturcott
   Student #:  0832217
       Email:  bturcott@mail.uoguelph.ca
       Class:  CIS*3190
  Assignment:  2
--------------------------------------------------------------------------------
DESCRIPTION:

This program takes a text file that describes a maze as input & outputs the
  directions for one way to get from the starting point to the ending point.

--------------------------------------------------------------------------------
TO RUN:

in command line, type the following:
  $ make
  $ ./go

--------------------------------------------------------------------------------
NOTES:

Input (especially from a file) with Ada is quite fragile. If you feed this
  program anything other than exactly what it is expecting (described in the
  assignment specification), the program will likely crash.

It is assumed that the input file formatted perfectly. There must not be any
  extra characters anywhere or any other monkey business.

This program will find A solution path for the input maze. However, it may not
  be the shortest path.

I have provided some test files these are the a few of the files I used for testing.
- t0, t1, and t2

END ======================================================================== END