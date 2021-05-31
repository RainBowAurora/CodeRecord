#include <iostream>
#include <gtest/gtest.h>

#include "declare_singleton.h"
#include "define_type_trait.h"

class Test1{
public:
    int32_t GetNum() {return num++; }
    void Shutdown() const {  }

    DECLARE_SINGLETON(Test1);

private:
    static int32_t num; 
};

int32_t Test1::num = 0;


TEST(macro, Singlton){
    for(int i = 0; i < 10; i++){
       ASSERT_EQ(Test1::Instance()->GetNum(), i);
    }
    Test1::Instance()->CleanUp();
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
