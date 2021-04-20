#include <Poco/SharedLibrary.h>
#include "base.h"
#include "factory.h"

using Poco::SharedLibrary;

// typedef void (*HelloFunc)(); // function pointer type

int main(int argc, char **argv)
{
    std::string path("/home/xiaoyu/test/poco/class_loader/build/libderived_plugin.so");
    SharedLibrary library(path);          // will also load the library
    std::cout << "Finished loading shared library." << std::endl;
    Base* object = create_object("Derived");
    object->print_name();
    std::cout << "object->add(1, 2) = "<< object->add(1, 2) << std::endl;;
    library.unload();
    return 0;
}