# ratelimiter

This project implements a token bucket rate limiter.

## Usage
1. Create a `rate_limiter::BucketRateLimiter` instance, giving two parameters: `limit` and `burst`.
2. Use `Allow` to consume a token.
