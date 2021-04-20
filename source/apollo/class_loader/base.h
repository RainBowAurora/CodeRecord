#pragma once

#include <iostream>

struct Base{
    virtual ~Base() = default;
    virtual void  print_name() = 0;
    virtual int add(int a, int b) = 0;
};