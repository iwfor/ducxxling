#include "ducxxling/nil_class.h"
#include "ducxxling/integer.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::NilClass;
using Ducxxling::Integer;

class TestNilClass : public CxxTest::TestSuite {
public:

    void test_dup() {
        NilClass n;
        Ducxxling::BaseType *x = n.dup();
        TS_ASSERT_EQUALS(x, &nil);
    }

    void test_is_a() {
        TS_ASSERT(nil.is_a<NilClass>());
        TS_ASSERT(nil.is_a(nil));
        TS_ASSERT(nil.is_a<Ducxxling::BaseType>());
        TS_ASSERT(!nil.is_a<Integer>());
    }

    void test_equals() {
        NilClass x;
        Integer i;
        TS_ASSERT(x.equals(nil));
        TS_ASSERT(!x.equals(i));
    }

    void test_assign() {
        NilClass x;
        Integer i;
        TS_ASSERT_THROWS_NOTHING(x.assign(nil));
        TS_ASSERT_THROWS(x.assign(i), Ducxxling::DuckTypeError);
    }
};
