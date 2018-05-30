# MultiThreading-Demos
Multi-threading demos for exploring all synchronisation objects like Mutex, Semaphore, Condition variables.

# 1. Traffic Signal
   Problem: Implement a Traffic signal program with single threaded of multi-treaded signals. When one signal becomes GREEN others signals will be RED. After the GREEN signal expires it becomes RED and the successive next signal will becomes RED and others also becomes RED.
   For example: Suppose there are 5 Signals, which expires in Round-robin fashion. If Signal-1 is expired then it becomes GREEN to RED and Signal-2 becomes RED to GREEN. Same way next successive numbered signals becomes GREEN after expiry.
   
   The program should print every signals status on expiry.
