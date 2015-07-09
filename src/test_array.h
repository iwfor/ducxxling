#include "ducxxling.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::Array;
using Ducxxling::Boolean;
using Ducxxling::Container;
using Ducxxling::Integer;
using Ducxxling::Scalar;

class TestArray : public CxxTest::TestSuite {
public:

    void test_is_a() {
        Array a;
        TS_ASSERT(a.is_a<Array>());
        TS_ASSERT(a.is_a<Container>());
        TS_ASSERT(a.is_a(a));
        TS_ASSERT(a.is_a<Ducxxling::BaseType>());
        TS_ASSERT(a.is_a<Container>());
        TS_ASSERT(!a.is_a<Ducxxling::Scalar>());
        TS_ASSERT(!a.is_a<Boolean>());
        TS_ASSERT(!a.is_a(nil));
        TS_ASSERT(!a.is_a<Integer>());
    }

};
