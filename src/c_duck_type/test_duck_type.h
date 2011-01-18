#include "c_duck_type.h"
#include <cxxtest/TestSuite.h>

using CDuckType::nil;
using CDuckType::NilClass;
using CDuckType::DuckType;

class TestDuckType : public CxxTest::TestSuite {
public:

    void test_is_a_nil() {
        DuckType x;
        DuckType n(nil);
        TS_ASSERT(x.is_a<NilClass>());
        TS_ASSERT(x.is_a(nil));
    }
};
