//
// Created by jasonjsyuan on 2020/1/20.
//

#ifndef HARD_RATELIMITER_H
#define HARD_RATELIMITER_H

#include <chrono>
#include <climits>

namespace rate_limiter
{
    // BucketRateLimiter ʵ��һ������������Ͱ�㷨Ƶ�أ����̰߳�ȫ
    class BucketRateLimiter
    {
    public:
        static double now() noexcept
        {
            auto const now = std::chrono::steady_clock::now().time_since_epoch();
            return std::chrono::duration<double>(now).count();
        }

        // BucketRateLimiter ����һ��ʵ��
        // limit ����Ƶ������ÿ�������������
        // ��� limit <= 0����ô�������Ƶ��
        // ��� limit > 0����ô���� limit ����Ƶ��
        // burst ������󲢷���������Ͱ��С��
        // ��� burst <= 0����ô����Ͱ��С���޴�
        // ��� burst > 0����ô����Ͱ��С���� burst ����
        explicit BucketRateLimiter(double limit, int burst) noexcept
        {
            repairParam(limit, burst);
            this->limit_ = limit;
            this->burst_ = burst;
            this->tokens_ = 0;
            this->last_ = 0;
        };

        // Adjust ��������Ͱ����
        void Adjust(double limit, int burst);

        // Allow ���Դ�����Ͱ��ȡһ������
        bool Allow();

    private:
        static void repairParam(double &limit, int &burst);
        bool allowAt(double t);
        void advance(double now, double &newLast, double &newTokens);

        double limit_; // ������¼��������ʣ��ݴ˿ɹ�������Ͱ��С)
        int burst_; // �����λ�ȡ�������������

        double tokens_;
        double last_; // last is the last time the limiter's tokens field was updated
    };
};


#endif //HARD_RATELIMITER_H
