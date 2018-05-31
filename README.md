# MultiThreading-Demos
Multi-threading demos for exploring all synchronisation objects like Mutex, Semaphore, Condition variables.

# 1. Traffic Signal
   Problem: Implement a Traffic signal program with either single threaded or multi-treaded signals. When one signal becomes GREEN others signals will be RED. After the GREEN signal expires it becomes RED and the successive next signal will becomes GREEN and others also becomes RED.

For example: Suppose there are 5 Signals, which expires in Round-robin fashion. If Signal-1 is expired then it becomes GREEN to RED and Signal-2 becomes RED to GREEN. Same way next successive numbered signal becomes GREEN after expiry.
   
The program should print every signals status on expiry.

Signal-1: Green
Signal-2: Red
Signal-3: Red
Signal-4: Red
Signal-5: Red

Signal-1 is expired then it will broadcast to all signals about expiry status and then all Signals will update and print the state.

Signal-1: Red
Signal-2: Green
Signal-3: Red
Signal-4: Red
Signal-5: Red

........

This problem is solved by using one condition variable as 'signalExpired' and one more variable 'curr_green_signal' which is increamented at every signal expiry.
