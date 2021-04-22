#include <chrono>
#include <iomanip>
#include <thread>
#include <sstream> //for std::stringstream
#include "chrono_time.h"

//[cppreference - chrono](https://zh.cppreference.com/w/cpp/chrono)

//[c++数值极限numeric_limits](https://blog.csdn.net/yhc166188/article/details/90287807)
const Time Time::MAX = Time(std::numeric_limits<uint64_t>::max());
const Time Time::MIN = Time(0);

using std::chrono::high_resolution_clock; //拥有可用的最短嘀嗒周期的时钟
using std::chrono::steady_clock; //决不会调整的单调时钟
using std::chrono::system_clock; //来自系统范畴实时时钟的挂钟时间

Time::Time(uint64_t nanoseconds) { nanoseconds_ = nanoseconds; }

Time::Time(int nanoseconds) {
  nanoseconds_ = static_cast<uint64_t>(nanoseconds);
}

Time::Time(double seconds) {
  nanoseconds_ = static_cast<uint64_t>(seconds * 1000000000UL); //1 秒=1000000000 纳秒
}

Time::Time(uint32_t seconds, uint32_t nanoseconds) {
  nanoseconds_ = static_cast<uint64_t>(seconds) * 1000000000UL + nanoseconds; //1 秒=1000000000 纳秒
}

Time::Time(const Time& other) { nanoseconds_ = other.nanoseconds_; }

Time& Time::operator=(const Time& other) {
  this->nanoseconds_ = other.nanoseconds_;
  return *this;
}

/**
 * @brief 
 * 
 * @return Time 
 * [std::chrono::time_point<Clock,Duration>::time_since_epoch](https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch)
 * 
 */
Time Time::Now() {
    auto now = high_resolution_clock::now();
    auto nano_time_point =
        std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto epoch = nano_time_point.time_since_epoch(); //返回time_point 与 clock 的纪元间的时间量
    uint64_t now_nano =
        std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count(); 
    return Time(now_nano);   
}

Time Time::MonoTime() {
    auto now = steady_clock::now();
    auto nano_time_point =
        std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto epoch = nano_time_point.time_since_epoch();
    uint64_t now_nano =
        std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
    return Time(now_nano);
}

double Time::ToSecond() const {
  return static_cast<double>(nanoseconds_) / 1000000000UL;
}

bool Time::IsZero() const { return nanoseconds_ == 0; }

uint64_t Time::ToNanosecond() const { return nanoseconds_; }

uint64_t Time::ToMicrosecond() const {
  return static_cast<uint64_t>(nanoseconds_ / 1000.0);
}

std::string Time::ToString() const {
    auto nano = std::chrono::nanoseconds(nanoseconds_);
    system_clock::time_point tp(nano);
    auto time = system_clock::to_time_t(tp);
    struct tm stm;
    //[cppreference - localtime](https://zh.cppreference.com/w/c/chrono/localtime)
    auto ret = localtime_r(&time, &stm); //转换给定的纪元起的时间为本地时间的日历时间

    if (ret == nullptr) {
        return std::to_string(static_cast<double>(nanoseconds_) / 1000000000.0);
    }

    std::stringstream ss;
    #if __GNUC__ >= 5
    ss << std::put_time(ret, "%F %T");
    ss << "." << std::setw(9) << std::setfill('0') << nanoseconds_ % 1000000000UL;
    #else
    char date_time[128];
    strftime(date_time, sizeof(date_time), "%F %T", ret);
    ss << std::string(date_time) << "." << std::setw(9) << std::setfill('0')
        << nanoseconds_ % 1000000000UL;
    #endif
    return ss.str();
}

void Time::SleepUntil(const Time& time) {
  auto nano = std::chrono::nanoseconds(time.ToNanosecond());
  system_clock::time_point tp(nano);
  std::this_thread::sleep_until(tp);
}

Duration Time::operator-(const Time& rhs) const
{
    return Duration(static_cast<int64_t>(nanoseconds_ - rhs.nanoseconds_));
}

Time Time::operator+(const Duration& rhs) const
{
    return Time(nanoseconds_ + rhs.ToNanosecond());
}

Time Time::operator-(const Duration& rhs) const
{
    return Time(nanoseconds_ - rhs.ToNanosecond());
}

Time& Time::operator+=(const Duration& rhs)
{
    *this = *this + rhs;
    return *this;
}

Time& Time::operator-=(const Duration& rhs)
{
    *this = *this - rhs;
    return *this;
}

bool Time::operator==(const Time& rhs) const
{
    return this->nanoseconds_ == rhs.nanoseconds_;
}

bool Time::operator!=(const Time& rhs) const
{
    return this->nanoseconds_ != rhs.nanoseconds_;
}

bool Time::operator>(const Time& rhs) const
{
    return this->nanoseconds_ > rhs.nanoseconds_;
}
bool Time::operator<(const Time& rhs) const
{
    return this->nanoseconds_ < rhs.nanoseconds_;
}

bool Time::operator>=(const Time& rhs) const
{
    return this->nanoseconds_ >= rhs.nanoseconds_;
}

bool Time::operator<=(const Time& rhs) const
{
    return this->nanoseconds_ <= rhs.nanoseconds_;
}

std::ostream& operator<<(std::ostream& os, const Time& rhs)
{
    os << rhs.ToString();
    return os;
}
