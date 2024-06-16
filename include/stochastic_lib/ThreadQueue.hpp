#ifndef THREADQUEUE_HPP
#define THREADQUEUE_HPP
#include <queue>
#include <mutex>
#include <condition_variable>

namespace stochastic
{
    template <typename T>
    class ThreadQueue
    {
    private:
        std::queue<T> _q;
        std::mutex _m;
        std::condition_variable _c;

    public:
        T get()
        {
            std::unique_lock<std::mutex> lock{_m};
            T value = _q.front();
            _c.wait(lock, [this] { return !_q.empty(); });
            _q.pop();

            return value;
        }
        void add(T value)
        {
            std::unique_lock<std::mutex> lock{_m};
            _q.push(value);
            _c.notify_one();
        }
        bool empty()
        {
            std::unique_lock<std::mutex> lock{_m};
            return _q.empty();
        }
    };
}  // namespace stochastic

#endif  // !THREADQUEUE_HPP