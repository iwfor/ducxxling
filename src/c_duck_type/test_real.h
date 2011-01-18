#include "c_duck_type/real.h"
#include <cxxtest/TestSuite.h>

using CDuckType::nil;
using CDuckType::Real;

class TestReal : public CxxTest::TestSuite {
public:
    void test_is_a() {
        Real x;
        TS_ASSERT(x.is_a<Real>());
        TS_ASSERT(x.is_a(x));
        TS_ASSERT(x.is_a<CDuckType::Scalar>());
        TS_ASSERT(x.is_a<CDuckType::BaseType>());
        TS_ASSERT(!x.is_a(nil));
        TS_ASSERT(!x.is_a<CDuckType::NilClass>());
    }

    void test_equals() {
        CDuckType::Real a(1.5);
        CDuckType::Real b(1.5);
        CDuckType::Real c(3.3);
        TS_ASSERT(a.equals(b));
        TS_ASSERT(!a.equals(c));
    }

    void test_compare() {
        CDuckType::Real a(1.5);
        CDuckType::Real b(2.2);
        CDuckType::Real c(2.7);
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
        TS_ASSERT_THROWS(a.assign(nil), CDuckType::DuckTypeError);
    }

    void test_to_string() {
        CDuckType::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_string(), "1.23");
    }

    void test_to_integer() {
        CDuckType::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_integer(), 1);
    }

    void test_to_real() {
        CDuckType::Real x(1.23);
        TS_ASSERT_EQUALS(x.to_real(), 1.23);
    }
};

