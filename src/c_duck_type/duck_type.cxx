/*
 * Copyright (c) 2011 Isaac W. Foraker, all rights reserved.
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

#include "c_duck_type/duck_type.h"
#include "c_duck_type/nil_class.h"
#include "c_duck_type/string.h"
#include "c_duck_type/integer.h"
#include "c_duck_type/real.h"
#include "c_duck_type/boolean.h"
#include <sstream>
#include <cstring>

namespace CDuckType {

DuckType::DuckType()
{
    value_ = &nil;
}

DuckType::DuckType(const DuckType &object)
{
    value_ = object.value_->dup();
}

DuckType::DuckType(const BaseType &object)
{
    value_ = object.dup();
}

DuckType::DuckType(const char *value)
{
    value_ = new String(value);
}

DuckType::DuckType(integer_type value)
{
    value_ = new Integer(value);
}

DuckType::DuckType(real_type value)
{
    value_ = new Real(value);
}

DuckType::DuckType(bool value)
{
    value_ = new Boolean(value);
}

DuckType::~DuckType()
{
    if (value_ && value_ != &nil)
        delete value_;
}

DuckType &DuckType::swap(DuckType &value)
{
    BaseType *v = value_;
    value_ = value.value_;
    value.value_ = v;
    return *this;
}

DuckType &DuckType::operator=(const DuckType &value)
{
    throw std::runtime_error("implement me");
    return *this;
}

DuckType &DuckType::operator=(const BaseType &value)
{
    throw std::runtime_error("implement me");
    return *this;
}

DuckType &DuckType::operator=(const char* value)
{
    if (value_ && value_->is_a<String>()) {
        static_cast<String*>(value_)->assign(value);
    }
    else if (value_ && value_->equals(nil)) {
        value_ = new String(value);
    }
    else {
        delete value_;
        value_ = new String(value);
    }
    return *this;
}

DuckType &DuckType::operator=(integer_type value)
{
    if (value_ && value_->is_a<Integer>()) {
        static_cast<Integer*>(value_)->assign(value);
    }
    else if (value_ && value_->equals(nil)) {
        value_ = new Integer(value);
    }
    else {
        delete value_;
        value_ = new Integer(value);
    }
    return *this;
}

DuckType &DuckType::operator=(real_type value)
{
    if (value_ && value_->is_a<Real>()) {
        static_cast<Real*>(value_)->assign(value);
    }
    else if (value_ && value_->equals(nil)) {
        value_ = new Real(value);
    }
    else {
        delete value_;
        value_ = new Real(value);
    }
    return *this;
}

DuckType &DuckType::operator=(bool value)
{
    if (value_ && value_->is_a<Boolean>()) {
        Boolean *b = static_cast<Boolean*>(value_);
        b->assign(value);
    }
    else if (value_ && value_->equals(nil)) {
        value_ = new Boolean(value);
    }
    else {
        delete value_;
        value_ = new Boolean(value);
    }
    return *this;
}

string_type DuckType::to_string() const
{
    return value_->to_string();
}

integer_type DuckType::to_integer() const
{
    return value_->to_integer();
}

real_type DuckType::to_real() const
{
    return value_->to_real();
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

} // CDuckType
