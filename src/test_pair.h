#include "ducxxling/nil_class.h"
#include "ducxxling/integer.h"
#include "ducxxling/string.h"
#include "ducxxling/pair.h"
#include <cxxtest/TestSuite.h>

using Ducxxling::nil;
using Ducxxling::NilClass;
using Ducxxling::Pair;
using Ducxxling::Integer;
using Ducxxling::String;

class TestPairClass : public CxxTest::TestSuite {
public:

    void test_dup() {
        Pair p(String("abc"), Integer(123));
        Ducxxling::BaseType *x = p.dup();
        TS_ASSERT(x->equals(p));
    }

    void test_is_a() {
        Pair p(String("abc"), Integer(123));
        TS_ASSERT(p.is_a<Pair>());
        TS_ASSERT(p.is_a<Ducxxling::BaseType>());
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
        TS_ASSERT_THROWS(x.assign(String("abc")), Ducxxling::DuckTypeError);
        TS_ASSERT_THROWS_NOTHING(x.assign(z));
        TS_ASSERT(x.equals(z));
    }
};
