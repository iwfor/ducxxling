#include "ducxxling/boolean.h"
#include "ducxxling/integer.h"
#include "ducxxling/nil_class.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::Boolean;
using Ducxxling::Integer;

class TestBoolean : public CxxTest::TestSuite {
public:

    void test_is_a() {
        Boolean f(false);
        TS_ASSERT(f.is_a<Boolean>());
        TS_ASSERT(f.is_a(f));
        TS_ASSERT(f.is_a<Ducxxling::BaseType>());
        TS_ASSERT(f.is_a<Ducxxling::Scalar>());
        TS_ASSERT(!f.is_a(nil));
        TS_ASSERT(!f.is_a<Integer>());
    }

    void test_equals() {
        Boolean f(false);
        Boolean t(true);
        TS_ASSERT(f.equals(f));
        TS_ASSERT(t.equals(t));
        TS_ASSERT(!f.equals(t));
        TS_ASSERT(!t.equals(f));
        TS_ASSERT(f.equals(nil));
        TS_ASSERT(!t.equals(nil));
    }

    void test_compare() {
        Boolean f(false);
        Boolean t(true);
        TS_ASSERT_EQUALS(t.compare(t), 0);
        TS_ASSERT_EQUALS(t.compare(f), 1);
        TS_ASSERT_EQUALS(f.compare(t), -1);
        TS_ASSERT_THROWS(t.compare(nil), Ducxxling::DuckTypeError);
        TS_ASSERT_EQUALS(f.compare(nil), 0);
    }

    void test_assign() {
        Boolean x;
        Integer i;
        TS_ASSERT_THROWS_NOTHING(x.assign(nil));
        TS_ASSERT_THROWS(x.assign(i), Ducxxling::DuckTypeError);
    }

    void test_to_string() {
        Boolean f(false);
        Boolean t(true);
        TS_ASSERT_EQUALS(t.to_string(), "true");
        TS_ASSERT_EQUALS(f.to_string(), "false");
    }

    void test_to_integer() {
        Boolean f(false);
        Boolean t(true);
        TS_ASSERT_EQUALS(t.to_integer(), 1);
        TS_ASSERT_EQUALS(f.to_integer(), 0);
    }

    void test_to_real() {
        Boolean f(false);
        Boolean t(true);
        TS_ASSERT_EQUALS(t.to_real(), 1.0);
        TS_ASSERT_EQUALS(f.to_real(), 0.0);
    }
};


