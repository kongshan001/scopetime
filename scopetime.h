#include <chrono>
#include <string>
#include <vector>
#include <utility>

#ifdef ENABLE_SCOPE_TIMER
#define SCOPE_TIME(name) CScopeTime ANONYMOUS_VAR(timer_)(name)
#define ANONYMOUS_VAR(name) name##__COUNTER__

class CScopeTime {
public:
    CScopeTime(std::string name): 
        name_(name),
        start_(std::chrono::steady_clock::now()) {}
    ~CScopeTime() {
        auto end = std::chrono::steady_clock::now();
        auto duration = end - start_;
        auto duration_count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        auto res = get_time_unit_and_count(duration_count);
        printf("%s耗时: %lld %s, duration: %lld\n", name_.c_str(), res.first, res.second.c_str(), duration_count);
    }
private:
    std::pair<long long, std::string> get_time_unit_and_count(long long& nanoseconds) {
        const std::vector<std::string> t = {
            "纳秒",
            "微秒",
            "毫秒",
            "秒",
        };
        auto s_time_unit = t[0];
        auto temp = nanoseconds;
        for(auto i=0;i<t.size() - 1;i++) {
            if(temp < 1000) {
                break;
            }
            s_time_unit = t[i + 1];
            temp /= 1000;
        }
        return std::make_pair(temp, s_time_unit);
    }
private:
    std::string name_;
    std::chrono::time_point<std::chrono::steady_clock> start_;
};


#else
#define SCOPE_TIME(name) ((void)0)

#endif