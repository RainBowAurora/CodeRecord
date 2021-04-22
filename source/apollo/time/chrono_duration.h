#ifndef __CHRONO_DURATION_TIME_H__
#define __CHRONO_DURATION_TIME_H__

#include <iostream>

//copy for https://github.com/ApolloAuto/apollo/tree/master/cyber/time

class Duration{
public:
    Duration():nanosecond_(0){};
    ~Duration() = default;

    explicit Duration(int64_t nanoseconds);
    explicit Duration(int nanoseconds);
    explicit Duration(double seconds);
    explicit Duration(uint32_t seconds, uint32_t nanoseconds);

    Duration(const Duration& other);
    Duration& operator=(const Duration& other);

    double ToSecond() const;
    int64_t ToNanosecond() const;
    bool IsZero() const;
    void Sleep() const;

    Duration operator+(const Duration &rhs) const;
    Duration operator-(const Duration &rhs) const;
    Duration operator-() const;
    Duration operator*(double scale) const;
    Duration &operator+=(const Duration &rhs);
    Duration &operator-=(const Duration &rhs);
    Duration &operator*=(double scale);

    bool operator==(const Duration &rhs) const;
    bool operator!=(const Duration &rhs) const;
    bool operator>(const Duration &rhs) const;
    bool operator<(const Duration &rhs) const;
    bool operator>=(const Duration &rhs) const;
    bool operator<=(const Duration &rhs) const;

private:
    int64_t nanosecond_;
};

std::ostream &operator<<(std::ostream &os, const Duration &rhs);

#endif /*__CHRONO_DURATION_TIME_H__*/