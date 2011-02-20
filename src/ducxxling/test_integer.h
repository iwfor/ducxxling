#include "ducxxling/integer.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::Integer;

class TestInteger : public CxxTest::TestSuite {
public:
    void test_is_a() {
        Integer x;
        TS_ASSERT(x.is_a<Integer>());
        TS_ASSERT(x.is_a(x));
        TS_ASSERT(x.is_a<Ducxxling::Scalar>());
        TS_ASSERT(x.is_a<Ducxxling::BaseType>());
        TS_ASSERT(!x.is_a(nil));
        TS_ASSERT(!x.is_a<Ducxxling::NilClass>());
    }

    void test_equals() {
        Integer a(5);
        Integer b(5);
        Integer c(10);
        TS_ASSERT(a.equals(b));
        TS_ASSERT(!a.equals(c));
    }

    void test_compare() {
        Integer a(5);
        Integer b(10);
        Integer c(15);
        TS_ASSERT_EQUALS(b.compare(a), 1);
        TS_ASSERT_EQUALS(b.compare(b), 0);
        TS_ASSERT_EQUALS(b.compare(c), -1);
    }

    void test_assign() {
        Integer a(5);
        Integer b(10);
        TS_ASSERT(!a.equals(b));
        TS_ASSERT_THROWS_NOTHING(a.assign(b));
        TS_ASSERT(a.equals(b));
        TS_ASSERT_THROWS(a.assign(nil), Ducxxling::DuckTypeError);
    }

    void test_to_string() {
        Integer x(123);
        TS_ASSERT_EQUALS(x.to_string(), "123");
    }

    void test_to_integer() {
        Integer x(123);
        TS_ASSERT_EQUALS(x.to_integer(), 123);
    }

    void test_to_real() {
        Integer x(123);
        TS_ASSERT_EQUALS(x.to_real(), 123.0);
    }
};
