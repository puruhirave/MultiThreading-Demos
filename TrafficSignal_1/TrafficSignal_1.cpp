// TrafficSingnal-SingleThreaded.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Signal.h"

int _tmain(int argc, _TCHAR* argv[])
{
    thread signalNotifier = thread(threadfun);

    ////////////// Signal Timer logic //////////////
    while (1)
    {
        //Sleep main thread to simulate wait logic of signal timer expiry
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::unique_lock<std::mutex> lk(m);

        //Program stop logic
        if (stop_count == MAX_STOP)
            break;

        //Increase curr_expired_signal in rotating manner to be notified as green signal.
        curr_green_signal++;
        if (curr_green_signal > MAX_SIGNALS)
        {
            curr_green_signal = 1;
        }

        //Set signal expired condition variables
        SignalExpired = true;

        //Notify signal expiry status to signal notifier thread.
        cv.notify_all();
        lk.unlock();

    }

    //Program exit clean up code
    curr_green_signal++;
    SignalExpired = true;
    cv.notify_all();

    //Join signal thread
    signalNotifier.join();

    std::cout << endl << "Press enter to Exit ....";
    std::cin.get();
    return 0;
}

