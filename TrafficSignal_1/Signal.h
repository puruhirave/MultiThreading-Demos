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

const int MAX_SIGNALS = 4; //Max signal count
const int MAX_STOP = 10; //Max program stop count
int curr_green_signal = 0; //current signal to be green after previous expired
int stop_count = 0;
bool SignalExpired = false; //Signal expired condition

void threadfun()
{
    while (1)
    {
        //Wait for signal expired
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return (SignalExpired); });

        //Signal thread stop logic
        stop_count++;
        if (stop_count == MAX_STOP)
            break;

        //Print all signals status after expiry
        for (int i = 0; i < MAX_SIGNALS; i++)
            cout << "Signal(" << (i + 1) << ")  => " << ((curr_green_signal == (i + 1)) ? "GREEN" : "RED") << endl;
        cout << endl;
        cout << endl;

        //Notify after printing signal status and try to reaquire lock
        SignalExpired = false;
        cv.notify_all();
        lock.unlock();
    }

    //Signal thread exit clean up code
    SignalExpired = false;
    cv.notify_all();
}
