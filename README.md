# MultiThreading-Demos
Multi-threading examples described with different scenarios using all kinds of synchronisation objects like Mutex, Semaphore, Condition variables.

# 1. Traffic Signal
   Problem:  
   Implement a Traffic Signal program with either single threaded or multi-treaded solutions. When first SIGNAL becomes GREEN other SIGNAL'S will become RED. After the GREEN SIGNAL expires it becomes RED and the successive next SIGNAL will become GREEN and others will become RED.

For example: Suppose there are 5 SIGNAL'S, which expires in Round-robin fashion. If SIGNAL-1 is expired then it becomes GREEN to RED and SIGNAL-2 becomes RED to GREEN. Same way next successive numbered SIGNAL becomes RED to GREEN after previous expired.
   
This problem is solved by using Mutex and Condition variable. Every Signal will print signal status on expiry.
```C
Initially SIGNAL-1 is Green then status is printed like,

SIGNAL-1: Green
SIGNAL-2: Red
SIGNAL-3: Red
SIGNAL-4: Red
SIGNAL-5: Red

After SIGNAL-1 is expired, it will broadcast to all SIGNAL'S about expired status and then SIGNAL-2 becomes GREEN 
and all SIGNAL'S will print there current state.

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
TrafficSignal_2: This program is implemented by using multiple SIGNAL threads. Every thread is numbered with dedicated SIGNAL ID. And one condition variable named 'signalExpired', Signal status variable 'curr_green_signal' and one more variable 'next_signal_id' which is incremented by current expired SIGNAL thread, which is used to wake up next successive SIGNAL thread to become GREEN on next SIGNAL expiry.

Every SIGNAL thread will check there own 'SIGNAL ID' with 'curr_green_signal' variable to print there own status on SIGNAL expiry.
The main thread will act as SIGNAL Timer.
