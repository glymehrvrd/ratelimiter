//
// Created by jasonjsyuan on 2020/1/20.
//

#ifndef HARD_RATELIMITER_H
#define HARD_RATELIMITER_H

#include <chrono>
#include <climits>

namespace rate_limiter
{
    // BucketRateLimiter 实现一个基本的令牌桶算法频控，非线程安全
    class BucketRateLimiter
    {
    public:
        static double now() noexcept
        {
            auto const now = std::chrono::steady_clock::now().time_since_epoch();
            return std::chrono::duration<double>(now).count();
        }

        // BucketRateLimiter 建立一个实例
        // limit 限制频控数（每秒放入令牌数）
        // 如果 limit <= 0，那么不会进行频控
        // 如果 limit > 0，那么按照 limit 进行频控
        // burst 限制最大并发数（令牌桶大小）
        // 如果 burst <= 0，那么令牌桶大小无限大
        // 如果 burst > 0，那么令牌桶大小按照 burst 设置
        explicit BucketRateLimiter(double limit, int burst) noexcept
        {
            repairParam(limit, burst);
            this->limit_ = limit;
            this->burst_ = burst;
            this->tokens_ = 0;
            this->last_ = 0;
        };

        // Adjust 调整令牌桶参数
        void Adjust(double limit, int burst);

        // Allow 尝试从令牌桶获取一个令牌
        bool Allow();

    private:
        static void repairParam(double &limit, int &burst);
        bool allowAt(double t);
        void advance(double now, double &newLast, double &newTokens);

        double limit_; // 允许的事件发生速率（据此可估算令牌桶大小)
        int burst_; // 允许单次获取的最大令牌数量

        double tokens_;
        double last_; // last is the last time the limiter's tokens field was updated
    };
};


#endif //HARD_RATELIMITER_H
