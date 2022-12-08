#include "trace.h"

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <iostream>
#include <string>

#include <stdlib.h>

static void PrintDigin(int value)
{
    const auto secs = boost::chrono::seconds(value);

    while (true)
    {
        TraceOut() << value;

        boost::this_thread::sleep_for(secs);
    }
}

static boost::thread threadOne;
static boost::thread threadTwo;

static void StartThreads()
{
    threadOne = boost::thread(boost::bind(&PrintDigin, 1));
    threadTwo = boost::thread(boost::bind(&PrintDigin, 2));
}

static void StopThreads()
{
    const auto stopThread = [](boost::thread& thr)
    {
        if (thr.joinable())
        {
            thr.interrupt();
            thr.join();
        }
    };

    stopThread(threadOne);
    stopThread(threadTwo);
}

int main(int argc, char* argv[])
try
{
    enum CmdState
    {
        RUNNING,
        STOPPED
    };

    CmdState cmdState = STOPPED;

    while (true)
    {
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "s")
        {
            if (cmdState != RUNNING)
            {
                StartThreads();
                cmdState = RUNNING;
            }
        }
        else if (cmd == "q")
        {
            if (cmdState != STOPPED)
            {
                StopThreads();
                cmdState = STOPPED;
            }
        }
        else if (!cmd.empty())
        {
            TraceErr() << "Invalid command: " << cmd;
        }
    }

    return 0;
}
catch(std::exception& ex)
{
    TraceErr() << "Exception: " << ex.what() << '\n';
    return 2;
}
catch( ...)
{
    TraceErr() << "Unknown exception\n";
    return 3;
}
