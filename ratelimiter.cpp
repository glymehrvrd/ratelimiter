//
// Created by jasonjsyuan on 2020/1/20.
//

#include "ratelimiter.h"

// durationFromTokens is a unit conversion function from the number of tokens to the duration
// of time it takes to accumulate them at a rate of limit tokens per second.
double durationFromTokens(double tokens, double limit)
{
    return tokens / limit;
}

// tokensFromDuration is a unit conversion function from a time duration to the number of tokens
// which could be accumulated during that duration at a rate of limit tokens per second.
double tokensFromDuration(double d, double limit)
{
	return d * limit;
}

// advance calculates and returns an updated state for lim resulting from the passage of time.
// lim is not changed.
void rate_limiter::BucketRateLimiter::advance(double now, double &newLast, double &newTokens)
{
    newLast = this->last_;
	if (now < newLast) {
        newLast = now;
	}

	// Avoid making delta overflow below when last is very old.
	double maxElapsed = durationFromTokens(this->burst_ - this->tokens_, this->limit_);
	double elapsed = now - newLast;
	if (elapsed > maxElapsed) {
		elapsed = maxElapsed;
	}

	// Calculate the new number of tokens, due to time that passed.
	double delta = tokensFromDuration(elapsed, this->limit_);
	newTokens = this->tokens_ + delta;
    if (newTokens > this->burst_) {
        newTokens = this->burst_;
	}
}

bool rate_limiter::BucketRateLimiter::allowAt(double t)
{
    double last;
    double tokens;
    this->advance(t, last, tokens);

    // Calculate the remaining number of tokens resulting from the request.
    tokens--;

    // Calculate the wait duration
    double waitDuration = 0;
    if (tokens < 0) {
        waitDuration = durationFromTokens(-tokens, this->limit_);
    }

    // Decide result
    bool ok = 1 <= this->burst_ && waitDuration <= 0;

    // Update state
    if (ok)
    {
        this->last_ = t;
        this->tokens_ = tokens;
    }

    return ok;
}

bool rate_limiter::BucketRateLimiter::Allow()
{
    auto now = rate_limiter::BucketRateLimiter::now();
    return this->allowAt(now);
}

void rate_limiter::BucketRateLimiter::repairParam(double &limit, int &burst)
{
    // 如果 limit == 0，设置 limit_ = -1，不限制频控
    limit = limit == 0 ? -1: limit;
    // 如果 burst <= 0，设置 burst_ = INT_MAX，不限制令牌桶大小
    burst = burst <= 0 ? INT_MAX : burst;
}

void rate_limiter::BucketRateLimiter::Adjust(double limit, int burst)
{
    repairParam(limit, burst);
    this->limit_ = limit;
    this->burst_ = burst;
}
