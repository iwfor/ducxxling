#include "ducxxling.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::NilClass;
using Ducxxling::DuckType;

class TestDuckType : public CxxTest::TestSuite {
public:

    void test_is_a_nil() {
        DuckType x;
        DuckType n(nil);
        TS_ASSERT(x.is_a<NilClass>());
        TS_ASSERT(x.is_a(nil));
    }
};
