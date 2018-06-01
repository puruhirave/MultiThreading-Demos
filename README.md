# MultiThreading-Demos
Multi-threading use cases explained with different scenarios using all kinds of synchronisation objects like Mutex, Semaphore, Condition variables.

# 1. Traffic Signal
   Problem: Implement a Traffic signal program with either single threaded or multi-treaded solutions. When one signal becomes GREEN others signals will becomes RED. After the GREEN signal expires it becomes RED and the successive next signal will becomes GREEN and others become RED.

For example: Suppose there are 5 Signals, which expires in Round-robin fashion. If Signal-1 is expired then it becomes GREEN to RED and Signal-2 becomes RED to GREEN. Same way next successive numbered signal becomes GREEN after expiry.
   
This problem is solved by using Mutex and Condition variable. Every Signal will print signal status on expiry.
```C
First Signal-1 is Green then status is printed like,

Signal-1: Green
Signal-2: Red
Signal-3: Red
Signal-4: Red
Signal-5: Red

After Signal-1 is expired, it will broadcast to all Signals about expiry status and then Signal-2 becomes GREEN 
and all Signals will print current state.

Signal-1: Red
Signal-2: Green
Signal-3: Red
Signal-4: Red
Signal-5: Red

........
....

```

Here provided two solutions for this problem.

## Single threaded Traffic signal
TrafficSignal_1: This is implemented by using only one Signal thread and one condition variable as 'signalExpired' and one more variable 'curr_green_signal' which is increamented at every signal expiry. The main thread will act as Signal Timer.

## Multi-threaded Traffic signal
TrafficSignal_2: This is implemented by using multiple Signal threads such as each thread for dedicated indexed Signal and one condition variable as 'signalExpired' and one more variable 'curr_green_signal' which is increamented at every signal expiry.

Every signal has given 'signalId' which is checked against 'curr_green_signal' after expiry.
The main thread will act as Signal Timer.
