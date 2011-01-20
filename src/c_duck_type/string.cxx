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

#include "c_duck_type/string.h"
#include <sstream>
#include <cstring>

namespace CDuckType {

DTI_DEFINE_TYPE(String, "String", Scalar);

String::String()
    : Scalar()
{
}

String::String(const string_type &value)
    : Scalar(), val_(value)
{
}

String::String(const String &value)
    : Scalar(), val_(value.val_)
{
}

String::~String()
{
}

BaseType *String::dup() const
{
    return new String(val_);
}

bool String::equals(const BaseType &value) const
{
    return value.is_a<String>() && val_ == static_cast<const String &>(value).val_;
}

int String::compare(const BaseType &value) const
{
    if (!value.is_a<String>())
        throw DuckTypeError("cannot assign non-String value to String");
    string_type other = static_cast<const String &>(value).val_;
    return val_ == other ? 0 : (val_ < other ? -1 : 1);
}

BaseType &String::assign(const BaseType &value)
{
    if (!value.is_a<String>())
        throw DuckTypeError("Cannot assign non-String value to String");
    val_ = static_cast<const String &>(value).val_;
    return *this;
}

BaseType &String::assign(const string_type &value)
{
    if (frozen_)
        throw DuckTypeError("cannot assign frozen object");
    val_ = value;
    return *this;
}

string_type String::to_string() const
{
    return val_;
}

integer_type String::to_integer() const
{
    return std::atoi(val_.c_str());
}

real_type String::to_real() const
{
    return std::atof(val_.c_str());
}

string_type &String::value()
{
    return val_;
}

const string_type &String::value() const
{
    return val_;
}

} // namespace CDuckType
