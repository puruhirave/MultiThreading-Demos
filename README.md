# Multi-Threading Demos
Multi-threading examples described with different scenarios using all kinds of synchronisation objects like Mutex, Semaphore, Condition variables.

# 1. Traffic Signal
   Problem:  
   Implement a Traffic Signal program with either single threaded or multi-treaded solutions. 
  
For example: Suppose there are 5 SIGNAL's, which expires in Round-robin fashion. When first SIGNAL becomes GREEN, other SIGNAL's will become RED. After the GREEN SIGNAL expires it becomes RED and the successive next SIGNAL will become GREEN and others will become RED. Same way next successive numbered SIGNAL becomes RED to GREEN after previous expired.
   
This problem is solved by using Mutex and Condition variable. Every Signal will print signal status on expiry.
```C
Initially SIGNAL-1 is Green then status is printed like,

SIGNAL-1: Green
SIGNAL-2: Red
SIGNAL-3: Red
SIGNAL-4: Red
SIGNAL-5: Red

After SIGNAL-1 is expired, it will broadcast to all SIGNAL's about expired status and then SIGNAL-2 becomes GREEN 
and all SIGNAL's will print there current state.

SIGNAL-1: Red
SIGNAL-2: Green
SIGNAL-3: Red
SIGNAL-4: Red
SIGNAL-5: Red

........
....

```

Provided two solutions for this problem.

## Single threaded Traffic Signal
TrafficSignal_1: This program is implemented by using only one SIGNAL thread, one condition variable as 'signalExpired' and one more variable 'curr_green_signal' which is increamented at every SIGNAL expiry. The main thread will act as SIGNAL Timer.

## Multi-threaded Traffic Signal
TrafficSignal_2: This program is implemented by using multiple SIGNAL threads. Every thread is numbered with dedicated SIGNAL ID  as 'sig_id'. 

Following are other variables and their uses.

* 'signalExpired'     => Condition variable used to notify all SIGNALS on expiry.
* 'curr_green_signal' => Signal status variable used to check if current status is GREEN while printing status of each SIGNAL.
* 'wakeup_signal_id'  => Variable used to wake up next successive SIGNAL thread to become GREEN on immediate expiry of previous SIGNAL.    Incremented by current expired SIGNAL thread after printing status. 

Every SIGNAL thread will check there own 'SIGNAL ID' with 'curr_green_signal' variable to check & print there own status as GREEN or RED on every SIGNAL expiry.
The main thread will act as SIGNAL Timer.
