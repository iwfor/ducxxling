#include "c_duck_type/nil_class.h"
#include "c_duck_type/integer.h"
#include <cxxtest/TestSuite.h>

using CDuckType::nil;
using CDuckType::NilClass;
using CDuckType::Integer;

class TestNilClass : public CxxTest::TestSuite {
public:

    void test_dup() {
        NilClass n;
        CDuckType::BaseType *x = n.dup();
        TS_ASSERT_EQUALS(x, &nil);
    }

    void test_is_a() {
        TS_ASSERT(nil.is_a<NilClass>());
        TS_ASSERT(nil.is_a(nil));
        TS_ASSERT(nil.is_a<CDuckType::BaseType>());
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
        TS_ASSERT_THROWS(x.assign(i), CDuckType::DuckTypeError);
    }
};

