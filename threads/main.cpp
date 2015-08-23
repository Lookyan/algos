#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>
boost::mutex io_mutex;


void count(int id)
{
    int now = 0;
    while(true)
    {
        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << id << ": " << now << std::endl;
        now++;
        if(now > 1000) return;
    }
}

int main()
{
    boost::thread thrd1(boost::bind(&count, 1));
    boost::thread thrd2(boost::bind(&count, 2));
    thrd1.join();
    thrd2.join();
    return 0;
}
