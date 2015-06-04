/*
 * Copyright (c) 2011-2015 Isaac W. Foraker, all rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. Neither the name of the Author nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE AND DOCUMENTATION IS PROVIDED BY THE AUTHOR AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ducxxling/duck_type.h"
#include "ducxxling/boolean.h"
#include "ducxxling/integer.h"
#include "ducxxling/iterator.h"
#include "ducxxling/nil_class.h"
#include "ducxxling/pair.h"
#include "ducxxling/real.h"
#include "ducxxling/string.h"
#include <sstream>
#include <cstring>

namespace Ducxxling {

DuckType::DuckType()
{
    value_ = &nil;
}

DuckType::DuckType(const DuckType &val)
{
    value_ = val.value_->dup();
}

DuckType::DuckType(const BaseType &val)
{
    value_ = val.dup();
}

DuckType::DuckType(const char *val)
{
    value_ = new String(val);
}

DuckType::DuckType(integer_type val)
{
    value_ = new Integer(val);
}

DuckType::DuckType(real_type val)
{
    value_ = new Real(val);
}

DuckType::DuckType(bool val)
{
    value_ = new Boolean(val);
}

DuckType::~DuckType()
{
    free();
}

void DuckType::free()
{
    if (value_ && value_ != &nil)
        delete value_;
    value_ = &nil;
}

BaseType &DuckType::value()
{
    return *value_;
}

const BaseType &DuckType::value() const
{
    return *value_;
}

DuckType &DuckType::swap(DuckType &val)
{
    BaseType *v = value_;
    value_ = val.value_;
    val.value_ = v;
    return *this;
}

DuckType &DuckType::operator=(const DuckType &val)
{
    free();
    value_ = val.value_->dup();
    return *this;
}

DuckType &DuckType::operator=(const BaseType &val)
{
    free();
    value_ = val.dup();
    return *this;
}

DuckType &DuckType::operator=(const char* val)
{
    if (value_ && value_->is_a<String>()) {
        static_cast<String*>(value_)->assign(val);
    }
    else {
        free();
        value_ = new String(val);
    }
    return *this;
}

DuckType &DuckType::operator=(const string_type &val)
{
    if (value_ && value_->is_a<String>()) {
        static_cast<String*>(value_)->assign(val);
    }
    else {
        free();
        value_ = new String(val);
    }
    return *this;
}

DuckType &DuckType::operator=(integer_type val)
{
    if (value_ && value_->is_a<Integer>()) {
        static_cast<Integer*>(value_)->assign(val);
    }
    else {
        if (value_ && value_ != &nil)
            delete value_;
        value_ = new Integer(val);
    }
    return *this;
}

DuckType &DuckType::operator=(real_type val)
{
    if (value_ && value_->is_a<Real>()) {
        static_cast<Real*>(value_)->assign(val);
    }
    else {
        if (value_ && value_ != &nil)
            delete value_;
        value_ = new Real(val);
    }
    return *this;
}

DuckType &DuckType::operator=(bool val)
{
    if (value_ && value_->is_a<Boolean>()) {
        Boolean *b = static_cast<Boolean*>(value_);
        b->assign(val);
    }
    else {
        if (value_ && value_ != &nil)
            delete value_;
        value_ = new Boolean(val);
    }
    return *this;
}

string_type DuckType::to_string() const
{
    if (!value_->is_a<Scalar>())
        throw DuckTypeError("cannot convert non-scalar to string");
    return static_cast<const Scalar*>(value_)->to_string();
}

integer_type DuckType::to_integer() const
{
    if (!value_->is_a<Scalar>())
        throw DuckTypeError("cannot convert non-scalar to string");
    return static_cast<const Scalar*>(value_)->to_integer();
}

real_type DuckType::to_real() const
{
    if (!value_->is_a<Scalar>())
        throw DuckTypeError("cannot convert non-scalar to string");
    return static_cast<const Scalar*>(value_)->to_real();
}

string_type &DuckType::string()
{
    return static_cast<String*>(value_)->value();
}
const string_type &DuckType::string() const
{
    return static_cast<const String*>(value_)->value();
}


bool DuckType::is_a(const DuckType &object) const
{
    if (value_)
        return value_->is_a(*object.value_);
    else
        return false;
}

bool DuckType::is_a(const BaseType &object) const
{
    if (value_)
        return value_->is_a(object);
    else
        return false;
}

DuckType &DuckType::first()
{
    if (!value_->is_a<Pair>())
        throw DuckTypeError("cannot get first of non-Pair object");
    return static_cast<Pair *>(value_)->first;
}

const DuckType &DuckType::first() const
{
    if (!value_->is_a<Pair>())
        throw DuckTypeError("cannot get first of non-Pair object");
    return static_cast<const Pair *>(value_)->first;
}

DuckType &DuckType::second()
{
    if (!value_->is_a<Pair>())
        throw DuckTypeError("cannot get second of non-Pair object");
    return static_cast<Pair *>(value_)->second;
}

const DuckType &DuckType::second() const
{
    if (!value_->is_a<Pair>())
        throw DuckTypeError("cannot get second of non-Pair object");
    return static_cast<const Pair *>(value_)->second;
}

Iterator &DuckType::iterator()
{
    if (!value_->is_a<Iterator>())
        throw DuckTypeError("cannot convert non-Iterator to Iterator");
    return *static_cast<Iterator *>(value_);
}

const Iterator &DuckType::iterator() const
{
    if (!value_->is_a<Iterator>())
        throw DuckTypeError("cannot convert non-Iterator to Iterator");
    return *static_cast<const Iterator *>(value_);
}

} // Ducxxling
