#include "c_duck_type/string.h"
#include <cxxtest/TestSuite.h>

using CDuckType::nil;
using CDuckType::String;

class TestString : public CxxTest::TestSuite {
public:
    void test_is_a() {
        String x;
        TS_ASSERT(x.is_a<String>());
        TS_ASSERT(x.is_a(x));
        TS_ASSERT(x.is_a<CDuckType::Scalar>());
        TS_ASSERT(x.is_a<CDuckType::BaseType>());
        TS_ASSERT(!x.is_a(nil));
        TS_ASSERT(!x.is_a<CDuckType::NilClass>());
    }

    void test_string_equals() {
        String a("abcdef");
        String b("abcdef");
        String c("fedcba");
        TS_ASSERT(a.equals(b));
        TS_ASSERT(!a.equals(c));
    }

    void test_string_compare() {
        String a("apple");
        String b("banana");
        String c("grape");
        TS_ASSERT_EQUALS(b.compare(a), 1);
        TS_ASSERT_EQUALS(b.compare(b), 0);
        TS_ASSERT_EQUALS(b.compare(c), -1);
    }

    void test_assign() {
        String a("sock");
        String b("shoe");
        TS_ASSERT(!a.equals(b));
        TS_ASSERT_THROWS_NOTHING(a.assign(b));
        TS_ASSERT(a.equals(b));
        TS_ASSERT_THROWS(a.assign(nil), CDuckType::DuckTypeError);
    }

    void test_string_to_string() {
        String x("abcdef");
        TS_ASSERT_EQUALS(x.to_string(), "abcdef");
    }

    void test_string_to_integer() {
        String x("123");
        TS_ASSERT_EQUALS(x.to_integer(), 123);
    }

    void test_string_to_real() {
        String x("1.5");
        TS_ASSERT_EQUALS(x.to_real(), 1.5);
    }
};
