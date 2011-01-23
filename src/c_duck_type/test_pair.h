#include "c_duck_type/nil_class.h"
#include "c_duck_type/integer.h"
#include "c_duck_type/string.h"
#include "c_duck_type/pair.h"
#include <cxxtest/TestSuite.h>

using CDuckType::nil;
using CDuckType::NilClass;
using CDuckType::Pair;
using CDuckType::Integer;
using CDuckType::String;

class TestPairClass : public CxxTest::TestSuite {
public:

    void test_dup() {
        Pair p(String("abc"), Integer(123));
        CDuckType::BaseType *x = p.dup();
        TS_ASSERT(x->equals(p));
    }

    void test_is_a() {
        Pair p(String("abc"), Integer(123));
        TS_ASSERT(p.is_a<Pair>());
        TS_ASSERT(p.is_a<CDuckType::BaseType>());
        TS_ASSERT(p.first.is_a<String>());
        TS_ASSERT(p.second.is_a<Integer>());
    }

    void test_equals() {
        Pair x(String("abc"), Integer(123));
        Pair y(String("abc"), Integer(123));
        Pair z(Integer(123), String("abc"));
        TS_ASSERT(x.equals(y));
        TS_ASSERT(!x.equals(z));
    }

    void test_assign() {
        Pair x;
        Pair y(String("abc"), Integer(123));
        Pair z(Integer(123), String("abc"));
        TS_ASSERT_THROWS_NOTHING(x.assign(y));
        TS_ASSERT(x.equals(y));
        TS_ASSERT_THROWS(x.assign(String("abc")), CDuckType::DuckTypeError);
        TS_ASSERT_THROWS_NOTHING(x.assign(z));
        TS_ASSERT(x.equals(z));
    }
};
