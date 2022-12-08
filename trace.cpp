#include "trace.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include <iostream>
#include <iomanip>

template <TraceDirection TD>
TraceT<TD>::~TraceT()
try
{
    static boost::mutex mtx;

    auto& os = []() -> std::ostream&
    {
        if (TD == TraceDirection::STDOUT) // FIXME: 'constexpr' could be here
        {
            return std::cout;
        }
        else // TD == TraceDirection::STDERR
        {
            return std::cerr;
        }
    }();

    {
        boost::lock_guard<boost::mutex> guard(mtx);

        os << m_ss.rdbuf();
        os << '\n';
        os.flush();
    }
}
catch (...)
{
}

template class TraceT<TraceDirection::STDOUT>;
template class TraceT<TraceDirection::STDERR>;
