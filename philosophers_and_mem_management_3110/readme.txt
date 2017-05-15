================================================================================
        Name:  Ben Turcotte
  Student ID:  Bturcott
   Student #:  0832217
       Email:  bturcott@mail.uoguelph.ca
       Class:  CIS*3110
  Assignment:  3
--------------------------------------------------------------------------------
DESCRIPTION:

Two programs have been submited--one for each part of assignment 3. The first
  program is a simulator that solves the dining philosophers problem. The second
  program is a memory management simulator.


--------------------------------------------------------------------------------
TO RUN:

  Compile: $ make

  Run part 1: $ dine n m
  - n is the number of philosophers
  - m is the number of times they each must eat

  Run part 2: $ holes input_file
  - input_file is the name of the file to be used by the holes program as input


--------------------------------------------------------------------------------
NOTES:

dine:
  I used an integer array that is accessible to all threads (philosophers) to
    indicate when a fork was made available. As suggested by our testbook, odd
    numbered philosophers grab the left fork first, then the right. Vice versa
    for even numbered philosophers. I have tested this relatively extensively.
    Should work fine no matter what numbers are input.
  Largest test input: $ dine 50 25

holes:
  Structure used: hashmap (process id used as array index).

  Processes are swapped in & out of memory based on their timestamp. Their
    timestamps are updated every time a process switches from the wait list to
    the loaded list or vice versa.

  Memory is represented as an array of process IDs. Each array block is 1MB of
    memory. If a process occupies MB 4 to 7 in memory, the array will hold a
    copy of the process ID in each index 4 through 7.

  FIRST FIT inserts a new process into the first available space in memory.
  BEST FIT  inserts a new process into the smallest available space that the 
    new process will fit in.
  WORST FIT inserts a new process into the largest available space in memory.
  FIRST FIT inserts a new process into the first available space in memory.
    However, the previous insertion point is kept track of & searching beins
    from there every time a new process is to be inserted.

  The test files I included are the test files I used for testing the holes
    program.


Developed on macOS Sierra 10.12.3


============================================================================ END