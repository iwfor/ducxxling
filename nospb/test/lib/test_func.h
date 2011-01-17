#include <cxxtest/TestSuite.h>

int some_func(int, int);

class TestFunc : public CxxTest::TestSuite
{
public:
    void test_some_func()
    {
        TS_ASSERT_EQUALS(some_func(1,2), 3);
        TS_ASSERT_EQUALS(some_func(20,22), 42);
    }

};
