================================================================================
        Name:  Ben Turcotte
  Student ID:  Bturcott
   Student #:  0832217
       Email:  bturcott@mail.uoguelph.ca
       Class:  CIS*3110
  Assignment:  2
--------------------------------------------------------------------------------
DESCRIPTION:

This program is a CPU scheduling simulator. It parses input from stdin
  (probably redirected to a file via command line), stores the information in
  arrays of processes, threads, and CPU bursts, uses either a fcfs or a
  round-robin scheduling algorithm to set up an event queue, then
  processes & reports statistics on the execution of the threads & processes.

--------------------------------------------------------------------------------
TO RUN:

in command line, type the following:
  $ make
  $ ./simcpu ${FLAGS} < input_file

replace ${FLAGS} with any of the following flags:
  -d    : detailed info mode
  -v    : verbose mode
  -r Q  : use round-robin scheduling, replace 'Q' with your desired
          quantum value (must be an integer).

if the '-r' flag is not present, fcfs scheduling will be used.

if no 'mode' flags are present, the program will run in default mode which
provides basic stats:
- total time
- average turnaround time
- CPU utilization


--------------------------------------------------------------------------------
FCFS ALGORITHM:

  Every thread from every process is put into an array.
  The array is sorted by arrival time (accending order).

  For each thread in the array:

    advance clock to next event if next event occurs after current clock time

    if process switch needs to occur
      clock <-- clock + process_switch
    else if thread switch needs to ocur
      clock <-- clock + thread_switch

    CPU_use            <-- CPU_use + sum of CPU_time for each burst
    clock              <-- clock + sum of (CPU_time + io_time) for each burst
    thread.turnaround  <-- thread.termination_time - thread.arrival_time
    average_turnaround <-- average_turnaround + thread.turnaround

  average_turnaround <-- average_turnaround/total_number_of_threads
  CPU_use            <-- (CPU_use / clock) * 100


--------------------------------------------------------------------------------
ROUND-ROBIN ALGORITHM:

Every thread from every process is put into a priority queue.

The priority queue is sorted by arrival time (accending order).

Arrival time is either the arrival time of the thread, or the time it was
  pushed back onto the queue.

begin algorithm rr:
  while the queue is not empty:

    thread <-- queue.pop()

    advance clock to next event if next event occurs after current clock time

    if process switch needs to occur
      clock <-- clock + process_switch
    else if thread switch needs to ocur
      clock <-- clock + thread_switch

    if thread is new
      CPU_use <-- CPU_use + sum of CPU_time for each burst
    if quantum > thread.remaining_time
      clock <-- clock + thread.remaining_time
    else
      clock <-- clock + quantum

    thread.remaining_time <-- thread.remaining_time - quantum

    if thread.remaining_time > 0
      queue.push(thread)
    else
      thread.turnaround  <-- thread.termination_time - thread.arrival_time
      average_turnaround <-- average_turnaround + thread.turnaround

  average_turnaround <-- average_turnaround/total_number_of_threads
  CPU_use            <-- (CPU_use / clock) * 100
end algorithm rr


--------------------------------------------------------------------------------
"BRIEF REPORT":

Q1. Does your simulator include switch overhead for the first ready state to
    running state transition? Explain.

    Yes. I included a process_switch overhead before the first process. I did
      this because it seemed reasonable to have to spend time switching
      contexts from the current state to the state for the first process.


Q2. Does your simulator include switch overhead if a thread moves from ready
    state to running state and the CPU is idle? Explain.

    Yes, but only if the previous thread and the next thread belong to the
      same process. Otherwise, the process switch overhead time is added to
      the total time.
    My algorithm includes thread/process switch overhead time based on
      the previous thread/process. However, if the last thread to run belonged
      to the same process as the next thread to be run, the thread switch
      overhead time would be added to the total time instead of adding the
      process switch overhead time.


Q3. Does your simulator include switch overhead if a thread moves from running
    state to blocked state and the ready queue is empty? Explain.

    No. I only have one queue. If the queue is empty, we're all done.


Q4. Does your simulation include switch overhead if a thread is interrupted
    (due to a time slice) and either the ready queue is empty or the thread
    has the highest priority? Explain.

    For fcfs, no. The priotiy queue is sorted based on arrival time. Threads
      are processed in full, one at a time. Thread/process switch overhead
      times are added according to the relationship between the previously
      run thread & the next thread to run.
    For round-robin, yes-ish. If a thread still has execution time remaining,
      it is pushed onto the priority queue. The queue is sorted based on the
      time the thread was pushed onto the stack. A new thread's time of being
      pushed onto the stack is the same as it's arrival time.


--------------------------------------------------------------------------------
NOTES:

To minimize the time you have to spend marking this assignment, I have added
  make targets for testing. Refer to 'Makefile' to see all available options.

testcase0.txt is the same as testcase1.txt, except the comments have been
  removed.

CPU_use is (total_CPU_time / total_time) * 100
- total_CPU_time is just CPU time -- it DOES NOT include io time

When a thread arrives, it is processed in full

State of a thread:
- threads in the queue are initialized to NEW
- when a thread reaches the front of the queue, it changes from NEW (or
  BLOCKED*) to READY.
- appropriate process/thread switch time is added to the clock
- the thread changes from ready to running
- total run time of the thread is added to the clock
- the thread changes from running to terminated

* when using the round-robin algorithm, if remaining_time > quantum, the
  thread is pushed back onto the priority queue & it's state is set to BLOCKED


END ======================================================================== END