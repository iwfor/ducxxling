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

#include "c_duck_type/integer.h"
#include <sstream>

namespace CDuckType {

DTI_DEFINE_TYPE(Integer, Scalar);

Integer::Integer()
    : Scalar(), val_(0)
{
}

Integer::Integer(integer_type value)
    : Scalar(), val_(value)
{
}

Integer::Integer(const Integer &value)
    : Scalar(), val_(value.val_)
{
}

Integer::~Integer()
{
}

BaseType *Integer::dup() const
{
    return new Integer(val_);
}

bool Integer::equals(const BaseType &value) const
{
    return value.is_a<Integer>() && val_ == static_cast<const Integer &>(value).val_;
}

int Integer::compare(const BaseType &value) const
{
    if (!value.is_a<Integer>())
        throw DuckTypeError("cannot compare Integer to non-Integer value");
    integer_type other = static_cast<const Integer &>(value).val_;
    return val_ == other ? 0 : (val_ < other ? -1 : 1);
}

BaseType &Integer::assign(const BaseType &value)
{
    if (!value.is_a<Scalar>())
        throw DuckTypeError("Cannot assign non-Integer value to Integer");
    assign(static_cast<const Integer &>(value).val_);
    return *this;
}

BaseType &Integer::assign(integer_type value)
{
    if (frozen_)
        throw DuckTypeError("cannot assign frozen object");
    val_ = value;
    return *this;
}

std::string Integer::to_string() const
{
    std::stringstream s;
    s << val_;
    return s.str();
}

integer_type Integer::to_integer() const
{
    return val_;
}

real_type Integer::to_real() const
{
    return static_cast<double>(val_);
}

} // CDuckType
