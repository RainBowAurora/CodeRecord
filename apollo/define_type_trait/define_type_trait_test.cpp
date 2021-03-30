#include <iostream>
#include "define_type_trait.h"


struct A{
    void Print(){ std::cout << "A::Print\n";}
};


DEFINE_TYPE_TRAIT(Test1, Print1)

int main(int argc, char *argv[])
{

    std::cout << Test1<A>::value << std::endl;
    return 0;
}