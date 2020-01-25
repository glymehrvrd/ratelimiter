#include <iostream>
#include <ratelimiter.h>
#include "unistd.h"

rate_limiter::BucketRateLimiter getLimiter0()
{
    auto limiter=rate_limiter::BucketRateLimiter(-10, -10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter1()
{
    auto limiter=rate_limiter::BucketRateLimiter(0, 10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter2()
{
    auto limiter=rate_limiter::BucketRateLimiter(10, 0);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter3()
{
    auto limiter=rate_limiter::BucketRateLimiter(-10, 0);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter4()
{
    auto limiter=rate_limiter::BucketRateLimiter(0, -10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter5()
{
    auto limiter=rate_limiter::BucketRateLimiter(-10, 10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter6()
{
    auto limiter=rate_limiter::BucketRateLimiter(10, -10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter7()
{
    auto limiter=rate_limiter::BucketRateLimiter(100, 10);
    return limiter;
}

rate_limiter::BucketRateLimiter getLimiter8()
{
    auto limiter=rate_limiter::BucketRateLimiter(10, 20);
    return limiter;
}

int main()
{
    auto limiter = getLimiter0();
    std::cout<< "0 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter1();
    std::cout<< "1 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter2();
    std::cout<< "2 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter3();
    std::cout<< "3 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter4();
    std::cout<< "4 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter5();
    std::cout<< "5 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter6();
    std::cout<< "6 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter7();
    std::cout<< "7 \tallow:" <<limiter.Allow()<< std::endl;

    limiter = getLimiter8();
    std::cout<< "8 \tallow:" <<limiter.Allow()<< std::endl;

    std::cout<< "round 1"<< std::endl;
    limiter = getLimiter8();
    for (int i = 0; i < 1000 ; ++i)
    {
        std::cout<< "i:"<<i << "\tnow:"<<limiter.now() << "\tallow:" <<limiter.Allow()<< std::endl;
        usleep(1000);
    }
    // increase token bucket size & rate
    std::cout<< "round 2"<< std::endl;
    limiter.Adjust(20,40);
    for (int i = 0; i < 1000 ; ++i)
    {
        std::cout<< "i:"<<i << "\tnow:"<<limiter.now() << "\tallow:" <<limiter.Allow()<< std::endl;
        usleep(1000);
    }
    // decrease token bucket size & rate
    std::cout<< "round 3"<< std::endl;
    limiter.Adjust(5,10);
    for (int i = 0; i < 1000 ; ++i)
    {
        std::cout<< "i:"<<i << "\tnow:"<<limiter.now() << "\tallow:" <<limiter.Allow()<< std::endl;
        usleep(1000);
    }
    return 0;
}

