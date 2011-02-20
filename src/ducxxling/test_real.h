#include "ducxxling/real.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::Real;

class TestReal : public CxxTest::TestSuite {
public:
    void test_is_a() {
        Real x;
        TS_ASSERT(x.is_a<Real>());
        TS_ASSERT(x.is_a(x));
        TS_ASSERT(x.is_a<Ducxxling::Scalar>());
        TS_ASSERT(x.is_a<Ducxxling::BaseType>());
        TS_ASSERT(!x.is_a(nil));
        TS_ASSERT(!x.is_a<Ducxxling::NilClass>());
    }

    void test_equals() {
        Ducxxling::Real a(1.5);
        Ducxxling::Real b(1.5);
        Ducxxling::Real c(3.3);
        TS_ASSERT(a.equals(b));
        TS_ASSERT(!a.equals(c));
    }

    void test_compare() {
        Ducxxling::Real a(1.5);
        Ducxxling::Real b(2.2);
        Ducxxling::Real c(2.7);
        TS_ASSERT_EQUALS(b.compare(a), 1);
        TS_ASSERT_EQUALS(b.compare(b), 0);
        TS_ASSERT_EQUALS(b.compare(c), -1);
    }

    void test_assign() {
        Real a(1.5);
        Real b(1.7);
        TS_ASSERT(!a.equals(b));
        TS_ASSERT_THROWS_NOTHING(a.assign(b));
        TS_ASSERT(a.equals(b));
        TS_ASSERT_THROWS(a.assign(nil), Ducxxling::DuckTypeError);
    }

    void test_to_string() {
        Ducxxling::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_string(), "1.23");
    }

    void test_to_integer() {
        Ducxxling::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_integer(), 1);
    }

    void test_to_real() {
        Ducxxling::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_real(), 1.23);
    }
};

