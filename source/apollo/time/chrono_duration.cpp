#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "chrono_duration.h" //for std::setprecision

Duration::Duration(int64_t nanoseconds)
{
    nanosecond_ = nanoseconds;
}

Duration::Duration(int nanoseconds)
{
    nanosecond_ = static_cast<int64_t>(nanoseconds);
}

Duration::Duration(double seconds)
{
    nanosecond_ = static_cast<int64_t>(seconds * 1000000000UL);
}

Duration::Duration(uint32_t seconds, uint32_t nanoseconds)
{
    this->nanosecond_ = static_cast<int64_t>(seconds * 1000000000UL) +  nanoseconds;
}

Duration::Duration(const Duration& other)
{
    this->nanosecond_ = other.nanosecond_;
}

Duration &Duration::operator=(const Duration &other) {
  this->nanosecond_ = other.nanosecond_;
  return *this;
}

double Duration::ToSecond() const
{
    return static_cast<double>(nanosecond_) / 1000000000UL;
}

int64_t Duration::ToNanosecond() const
{
    return nanosecond_;
}

bool Duration::IsZero() const { return nanosecond_ == 0; }

void Duration::Sleep() const
{
    auto sleep_time = std::chrono::nanoseconds(nanosecond_);
    std::this_thread::sleep_for(sleep_time);
}


Duration Duration::operator+(const Duration &rhs) const
{
    return Duration(this->nanosecond_ + rhs.nanosecond_);
}
Duration Duration::operator-(const Duration &rhs) const
{
    return Duration(this->nanosecond_ - rhs.nanosecond_);
}
Duration Duration::operator-() const
{
    return Duration(-(this->nanosecond_));
}

Duration Duration::operator*(double scale) const
{
    return Duration(int64_t(static_cast<double>(nanosecond_) * scale));
}

Duration& Duration::operator+=(const Duration &rhs)
{
    *this = *this + rhs;
    return *this;
}
Duration& Duration::operator-=(const Duration &rhs)
{
    *this = *this - rhs;
    return *this;
}
Duration& Duration::operator*=(double scale)
{
    *this = Duration(int64_t(static_cast<double>(nanosecond_)* scale));
    return *this;
}

bool Duration::operator==(const Duration &rhs) const
{
    return this->nanosecond_ == rhs.nanosecond_;
}
bool Duration::operator!=(const Duration &rhs) const
{
    return this->nanosecond_ != rhs.nanosecond_;
}
bool Duration::operator>(const Duration &rhs) const
{
    return this->nanosecond_ > rhs.nanosecond_;
}
bool Duration::operator<(const Duration &rhs) const
{
    return this->nanosecond_ < rhs.nanosecond_;
}
bool Duration::operator>=(const Duration &rhs) const
{
    return this->nanosecond_ >= rhs.nanosecond_;
}
bool Duration::operator<=(const Duration &rhs) const
{
    return this->nanosecond_ <= rhs.nanosecond_;
}

std::ostream& operator<<(std::ostream& os, const Duration& rhs)
{
    std::ios::fmtflags before(os.flags());
    //精度设置 9
    os << std::fixed << std::setprecision(9) << rhs.ToSecond() << "s";
    os.flags(before);
    return os;
}