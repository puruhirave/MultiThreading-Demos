#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex m;
std::condition_variable cv;

const int MAX_SIGNALS = 4; //Max signals count
const int MAX_STOP = 10; //Signal program max stop count
int next_signal_id = 0;//To print next signal status
int wakeup_signal_id = -1;//To set wakeup Signal status to be green
int stop_count = 0;
bool SignalExpired = false;//Signal expired condition

void signalFun(int sigId)
{
    while (1)
    {
        unique_lock<mutex> lock(m);

        //Wait for signal expiry and next wake up SIGNAL to be Green is the current SIGNAL thread.
        cv.wait(lock, [&sigId]{return ((SignalExpired) && (wakeup_signal_id == sigId)); });

        //Logic to stop SIGNAL thread after some expiry counts.
        if (stop_count >= MAX_STOP)
            break;

        //Print signal state for each thread after expiry.
        cout << "Signal (" << sigId + 1 << ") : " << ((curr_green_signal == sigId) ? "Green" : "Red") << endl;

        //Increase wakeup_signal_id in rotating manner to set next wakup signal's turn.
        wakeup_signal_id = sigId + 1;
        if (wakeup_signal_id == MAX_SIGNALS)
        {
            wakeup_signal_id = 0;
            SignalExpired = false;
            cout << "Wait for signal expire...." << endl << endl;
        }

        //Broadcast to all signals to print next signal state.
        cv.notify_all();
        lock.unlock();
    }

    ///Signal Thread exit clean up code
    wakeup_signal_id = sigId + 1;
    if (wakeup_signal_id == MAX_SIGNALS)
    {
        wakeup_signal_id = 0;
    }
    SignalExpired = true;
    cv.notify_all();
}
