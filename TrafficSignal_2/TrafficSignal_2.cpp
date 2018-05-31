// TrafficSignal_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Signal.h"

int _tmain(int argc, _TCHAR* argv[])
{
    thread signals[MAX_SIGNALS];

    //Start multiple signal threads
    int i = 0;
    for (i = 0; i < MAX_SIGNALS; ++i)
        signals[i] = thread(signalFun, i);

    ////////// Signal Timer logic ///////
    while (1)
    {

        //Sleep main thread to simulate wait logic of signal timer expiry
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::unique_lock<std::mutex> lk(m);

        //Logic to stop signal timer loop
        if (stop_count >= MAX_STOP)
            break;

        //Increase curr_expired_signal in rotating manner to be notified as green signal.
        curr_green_signal++;
        if (curr_green_signal == MAX_SIGNALS)
        {
            curr_green_signal = 0;
        }

        //Set signal expired condition variables
        SignalExpired = true;
        stop_count++;

        //Broadcast signal expiry status to all signals.
        cv.notify_all();
        lk.unlock();

    }

    //All Signal Thread exit clean up code
    SignalExpired = true;
    cv.notify_all();

    //join signal threads
    for (i = 0; i < MAX_SIGNALS; ++i)
        signals[i].join();

    cin.get();
    return 0;
}

