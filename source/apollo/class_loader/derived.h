#ifndef __CLASS_LOADER_DERIVED_H__
#define __CLASS_LOADER_DERIVED_H__

#include <iostream>
#include "base.h"

struct Derived: public Base{
    void print_name() override;
    int add(int a, int b) override;
};

#endif /*__CLASS_LOADER_DERIVED_H__*/