/*******************************************************************************
        Name:  Ben Turcotte
  Student ID:  Bturcott
   Student #:  0832217
       Email:  bturcott@mail.uoguelph.ca
       Class:  CIS*3110
  Assignment:  2
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************
 * Header Stuff *
 ****************/
#define err(msg)\
{printf("Error! %s\n\t%s:%d\n", msg, __FILE__, __LINE__); exit(1);}
enum State {
  NEW,
  READY,
  RUNNING,
  BLOCKED,
  TERMINATED
};
struct Burst {
  int burst_id;
  int CPU_t;
  int io_t;
};
struct Thread {
  int process_id;
  int thread_id;
  int arrival_t;  // when thread arrives
  int execute_t;  // when thread begins execution
  int termin8_t;  // when thread finishes execution
  int waiting_t;  // time between arrivaed & executed
  int service_t;  // sum of CPU of each burst of the thread
  int total_io_t; // sum of io of each burst of the thread
  int time_left;
  int turnaround;
  int n_bursts;
  struct Burst bursts[10];
  enum   State state;
};
struct Process {
  int process_id;
  int total_t;
  int n_threads;
  struct Thread threads[50];
};
struct Info {
  int d_flag;
  int v_flag;
  int rr_flag;
  int quantum;
  int thread_switch;
  int process_switch;
  int n_processes;
<<<<<<< HEAD
  int q_size;
  struct Thread  empty_thread;
  struct Thread  thread_q[25600];
  struct Process processes[512];
=======
  int total_n_threads;
  struct Thread  thread_q[512];
  struct Process processes[64];
>>>>>>> a213f1c9c130976dd588c488c851388972c05719
};
typedef enum   State   State;
typedef struct Burst   Burst;
typedef struct Thread  Thread;
typedef struct Process Process;
typedef struct Info    Info;

/************************
 * Function Definitions *
 ************************/
void fcfs(Info info) {
  
  double total_t        = 0.00;
  double total_wait_t   = 0.00;
  double avg_turnaround = 0.00;
  double CPU_usage      = 0.00;

  for (int i = 0; i < info.q_size; i++) {
    
    info.thread_q[i].state = READY;
    if (info.v_flag) {
      printf("At time %.0lf: thread %d of process %d moves from NEW     to READY\n",
                  total_t, info.thread_q[i].thread_id, info.thread_q[i].process_id);
    }

    // advance clock to next event
    if (info.thread_q[i].arrival_t > total_t) {
      total_wait_t += info.thread_q[i].arrival_t - total_t;
      total_t       = info.thread_q[i].arrival_t;
    }

    // account for process switch
    if (i == 0 || info.thread_q[i -1].process_id != info.thread_q[i].process_id) {
      total_wait_t += info.process_switch;
      total_t      += info.process_switch;
    }
    
    // account for thread switch
    else if (info.thread_q[i -1].thread_id != info.thread_q[i].thread_id) {
      total_wait_t += info.thread_switch;
      total_t      += info.thread_switch;
    }

    // calculate time of execution & waiting time
    info.thread_q[i].execute_t = total_t;
    info.thread_q[i].waiting_t = info.thread_q[i].execute_t - info.thread_q[i].arrival_t;
    
    info.thread_q[i].state = RUNNING;
    if (info.v_flag) {
      printf("At time %.0lf: thread %d of process %d moves from READY   to RUNNING\n",
                      total_t, info.thread_q[i].thread_id, info.thread_q[i].process_id);
    }

    for (int j = 0; j < info.thread_q[i].n_bursts; j++) {
      info.thread_q[i].service_t  += info.thread_q[i].bursts[j].CPU_t;
      info.thread_q[i].total_io_t += info.thread_q[i].bursts[j].io_t;
      total_t                     += info.thread_q[i].bursts[j].CPU_t + info.thread_q[i].bursts[j].io_t;
    }

    CPU_usage                 += info.thread_q[i].service_t;
    info.thread_q[i].termin8_t = total_t;
    
    info.thread_q[i].state     = TERMINATED;
    if (info.v_flag) {
      printf("At time %.0lf: thread %d of process %d moves from RUNNING to TERMINATED\n",
                          total_t, info.thread_q[i].thread_id, info.thread_q[i].process_id);
    }

    // calculate turnaround time
    info.thread_q[i].turnaround = info.thread_q[i].termin8_t - info.thread_q[i].arrival_t;
    avg_turnaround += info.thread_q[i].turnaround;
  
    if (info.d_flag) {
      printf("-------------------------------\n");
      printf(" Process: %d",            info.thread_q[i].process_id);
      printf(" - Thread: %d\n",         info.thread_q[i].thread_id);
      printf("\tArrival time:    %d\n", info.thread_q[i].arrival_t);
      printf("\tService time:    %d\n", info.thread_q[i].service_t);
      printf("\tIO time:         %d\n", info.thread_q[i].total_io_t);
      printf("\tTurnaround time: %d\n", info.thread_q[i].turnaround);
      printf("\tFinish time:     %d\n", info.thread_q[i].termin8_t);
      printf("\n");
    }

  }

  avg_turnaround /= info.q_size;
  CPU_usage       = (CPU_usage / total_t) * 100;

  printf("\n");
  printf("Total time ................ %.0lf\n", total_t);
  printf("Average turnaround time ... %.2lf\n", avg_turnaround);
  printf("CPU utilization ........... %.2lf\n", CPU_usage);
  printf("\n");
}

void rr(Info info) {
  
  double total_t         =  0.00;
  double total_wait_t    =  0.00;
  double avg_turnaround  =  0.00;
  double CPU_usage       =  0.00;
  int    prev_thread_id  = -1;
  int    prev_process_id = -1;
  int    is_new_thread   =  0;
  int    initial_q_size  =  info.q_size;

  while (info.q_size > 0) {

    if (info.thread_q[0].state == NEW) is_new_thread = 1;
    else                               is_new_thread = 0;
    
    if (info.v_flag && info.thread_q[0].arrival_t >= 0) {
      if (is_new_thread)
        printf("At time %.0lf: thread %d of process %d moves from NEW     to READY\n",
                      total_t, info.thread_q[0].thread_id, info.thread_q[0].process_id);
      else
        printf("At time %.0lf: thread %d of process %d moves from BLOCKED to READY\n",
                      total_t, info.thread_q[0].thread_id, info.thread_q[0].process_id);
    }
    info.thread_q[0].state = READY;

    // advance clock to next event
    if (info.thread_q[0].arrival_t > total_t) {
      total_wait_t += info.thread_q[0].arrival_t - total_t;
      total_t       = info.thread_q[0].arrival_t;
    }

    // account for process switch
    if (prev_process_id != info.thread_q[0].process_id) {
      total_wait_t += info.process_switch;
      total_t      += info.process_switch;
    }
    
    // account for thread switch
    else if (prev_thread_id != info.thread_q[0].thread_id) {
      total_wait_t += info.thread_switch;
      total_t      += info.thread_switch;
    }

    if (info.v_flag && info.thread_q[0].arrival_t >= 0) {
      printf("At time %.0lf: thread %d of process %d moves from READY   to RUNNING\n",
                      total_t, info.thread_q[0].thread_id, info.thread_q[0].process_id);
    }
    info.thread_q[0].state = RUNNING;

    // IF this thread is new, add necessary service (CPU) time to total CPU time
    if (is_new_thread)
      CPU_usage += info.thread_q[0].service_t;

    // run thread for 'quantum' time units
    if (info.quantum > info.thread_q[0].time_left)
      total_t += info.thread_q[0].time_left;
    else
      total_t += info.quantum;
    info.thread_q[0].time_left = info.thread_q[0].time_left - info.quantum;

    // set previous IDs before de-queueing the thread
    prev_thread_id  = info.thread_q[0].thread_id;
    prev_process_id = info.thread_q[0].process_id;

    //  thread is not finished: de-queue the thread, then re-queue
    if (info.thread_q[0].time_left > 0) {

      if (info.v_flag && info.thread_q[0].arrival_t >= 0) {
        printf("At time %.0lf: thread %d of process %d moves from RUNNING to BLOCKED\n",
                            total_t, info.thread_q[0].thread_id, info.thread_q[0].process_id);
      }
      info.thread_q[0].state = BLOCKED;

      // insert thread back into pq
      int i;
      Thread temp;
      temp = info.thread_q[0];
      for (i = 0; i < info.q_size; i++) {
        if (info.thread_q[i].arrival_t > total_t)
          break;
        info.thread_q[i] = info.thread_q[i +1];
      }
      info.thread_q[i] = temp;
    }

    // thread is finished: de-queue thread
    else {

      // calculate turnaround time
      info.thread_q[0].termin8_t = total_t;
      info.thread_q[0].turnaround = info.thread_q[0].termin8_t - info.thread_q[0].arrival_t;
      avg_turnaround += info.thread_q[0].turnaround;
    
      if (info.d_flag && info.thread_q[0].arrival_t >= 0) {
        printf("-------------------------------\n");
        printf(" Process: %d",            info.thread_q[0].process_id);
        printf(" - Thread: %d\n",         info.thread_q[0].thread_id);
        printf("\tArrival time:    %d\n", info.thread_q[0].arrival_t);
        printf("\tService time:    %d\n", info.thread_q[0].service_t);
        printf("\tIO time:         %d\n", info.thread_q[0].total_io_t);
        printf("\tTurnaround time: %d\n", info.thread_q[0].turnaround);
        printf("\tFinish time:     %d\n", info.thread_q[0].termin8_t);
        printf("\n");
      }

      if (info.v_flag && info.thread_q[0].arrival_t >= 0) {
        printf("At time %.0lf: thread %d of process %d moves from RUNNING to TERMINATED\n",
                            total_t, info.thread_q[0].thread_id, info.thread_q[0].process_id);
      }
      info.thread_q[0].state = TERMINATED;

      // de-queue thread
      for (int i = 0; i < info.q_size; i++)
        info.thread_q[i] = info.thread_q[i +1];
      info.q_size--;
    }
  }

  avg_turnaround /= initial_q_size;
  CPU_usage       = (CPU_usage / total_t) * 100;

  printf("\n");
  printf("Total time ................ %.0lf\n", total_t);
  printf("Average turnaround time ... %.2lf\n", avg_turnaround);
  printf("CPU utilization ........... %.2lf\n", CPU_usage);
  printf("\n");
}

void sort_all_threads(Info *info) {
  
  // load all threads into thread queue
  for (int n = 0; n < info->n_processes; n++) {
    for (int i = 0; i < info->processes[n].n_threads; i++) {
      info->thread_q[info->q_size] = info->processes[n].threads[i];
      info->q_size += 1;
    }
  }

  // sort thread queue based on arrival time
  for (int i = 0; i < info->q_size -1; i++) {
    for (int j = i +1; j < info->q_size; j++) {
      if (info->thread_q[i].arrival_t > info->thread_q[j].arrival_t) {
        Thread temp_thread = info->thread_q[i];
        info->thread_q[i]  = info->thread_q[j];
        info->thread_q[j]  = temp_thread;
      }
    }
  }
}

void parse_input(Info *info) {
  
  char BUFFER[128];
  int p_id   = 0;
  int n_th   = 0;
  int th_id  = 0;
  int arvl_t = 0;
  int n_CPU  = 0;
  int CPU_id = 0;
  int CPU_t  = 0;
  int io_t   = 0;
  
  /* each process */
  for (int i = 0; i < info->n_processes; i++) {
    
    if ( !fgets(BUFFER, 128, stdin) ) err("EOF was reached prematurely.")
    sscanf(BUFFER, "%d %d", &p_id, &n_th);
    
    info->processes[i].process_id = p_id;
    info->processes[i].n_threads  = n_th;

    /* each thread */
    for (int j = 0; j < n_th; j++) {
      
      if ( !fgets(BUFFER, 128, stdin) ) err("EOF was reached prematurely.")
      sscanf(BUFFER, "%d %d %d", &th_id, &arvl_t, &n_CPU);
      
      info->processes[i].threads[j].process_id = p_id;
      info->processes[i].threads[j].thread_id  = th_id;
      info->processes[i].threads[j].arrival_t  = arvl_t;
      info->processes[i].threads[j].n_bursts   = n_CPU;
      info->processes[i].threads[j].state      = NEW;

      /* each CPU burst */
      for (int k = 0; k < n_CPU; k++) {
        
        if ( !fgets(BUFFER, 128, stdin) ) err("EOF was reached prematurely.")
        if (sscanf(BUFFER, "%d %d %d", &CPU_id, &CPU_t, &io_t) < 3) io_t = 0;
        
        info->processes[i].threads[j].bursts[k].burst_id = CPU_id;
        info->processes[i].threads[j].bursts[k].CPU_t    = CPU_t;
        info->processes[i].threads[j].bursts[k].io_t     = io_t;
        info->processes[i].threads[j].service_t  += CPU_t;
        info->processes[i].threads[j].total_io_t += io_t;
      }

      info->processes[i].threads[j].time_left = info->processes[i].threads[j].total_io_t + info->processes[i].threads[j].service_t;
    }
  }
}

void init_info(Info *info, int argc, char **argv) {
  
  char BUFFER[128];
  if ( !fgets(BUFFER, 128, stdin) ) err("empty file.")
  sscanf(BUFFER,"%d %d %d", &(info->n_processes),
                            &(info->thread_switch),
                            &(info->process_switch));

  if (info->n_processes > 512) err("TOO MANY PROCESSES!")
  
  info->d_flag  = 0;
  info->v_flag  = 0;
  info->rr_flag = 0;
  
  for (int i = 0; argv[i] != NULL; i++) {
    if (!strcmp("-d", argv[i]))
      info->d_flag = 1;
    else if (!strcmp("-v", argv[i]))
      info->v_flag = 1;
    else if (!strcmp("-r", argv[i])) {
      if ( !argv[i +1] ) err("must provide value for quantum.")
      info->rr_flag = 1;
      info->quantum = atoi(argv[i +1]);
    }
  }

  for (int i = 0; i < 25600; i++) {
    info->thread_q[i].process_id = -1;
    info->thread_q[i].thread_id  = -1;
    info->thread_q[i].arrival_t  = -1;
    info->thread_q[i].execute_t  = -1;
    info->thread_q[i].turnaround = -1;
    info->thread_q[i].n_bursts   = -1;
    info->thread_q[i].state      = TERMINATED;
  }
  info->q_size       = 0;
  info->empty_thread = info->thread_q[0];

  for (int i = 0; i < 512; i++) {
    info->processes[i].process_id = -1;
    info->processes[i].total_t    = -1;
    info->processes[i].n_threads  = -1;

    for (int j = 0; j < 50; j++) {
      info->processes[i].threads[j].process_id = -1;
      info->processes[i].threads[j].thread_id  = -1;
      info->processes[i].threads[j].arrival_t  = -1;
      info->processes[i].threads[j].execute_t  = -1;
      info->processes[i].threads[j].waiting_t  = -1;
      info->processes[i].threads[j].termin8_t  = -1;
      info->processes[i].threads[j].service_t  =  0;
      info->processes[i].threads[j].total_io_t =  0;
      info->processes[i].threads[j].turnaround = -1;
      info->processes[i].threads[j].n_bursts   = -1;
      info->processes[i].threads[j].state      = TERMINATED;

      for (int k = 0; k < 50; k++) {
        info->processes[i].threads[j].bursts[k].burst_id = -1;
        info->processes[i].threads[j].bursts[k].CPU_t    = -1;
        info->processes[i].threads[j].bursts[k].io_t     = -1;
      }
    }
  }
}

/********
 * MAIN *
 ********/
int main(int argc, char *argv[]) {
  Info info;
  init_info(&info, argc, argv);
  parse_input(&info);
  sort_all_threads(&info);
  if (info.rr_flag) rr(info);
  else fcfs(info);
  return 0;
}