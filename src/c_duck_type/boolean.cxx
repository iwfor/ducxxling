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

#include "c_duck_type/boolean.h"
#include "c_duck_type/nil_class.h"
#include <sstream>

namespace CDuckType {

DTI_DEFINE_TYPE(Boolean, Scalar);

Boolean::Boolean()
    : Scalar(), val_(0)
{
}

Boolean::Boolean(bool value)
    : Scalar(), val_(value)
{
}

Boolean::Boolean(const Boolean &value)
    : Scalar(), val_(value.val_)
{
}

Boolean::~Boolean()
{
}

BaseType *Boolean::dup() const
{
    return new Boolean(val_);
}

bool Boolean::equals(const BaseType &value) const
{
    if (value.is_a<Boolean>())
        return static_cast<const Boolean &>(value).val_ == val_;
    else if (val_ == false)
        if (value.is_a<NilClass>())
            return true;
        else
            return false;
    else
        return false;
}

bool Boolean::equals(bool value) const
{
    return val_ == value;
}


int Boolean::compare(const BaseType &value) const
{
    if (val_ == false) {
        if (value.is_a<Boolean>())
            return val_ == static_cast<const Boolean &>(value).val_ ? 0 : -1;
        else if (value.is_a<NilClass>())
            return 0;
        else
            throw DuckTypeError("incompatible types for comparison");
    }
    else {
        if (!value.is_a<Boolean>())
            throw DuckTypeError("incompatible types for comparison");
        else
            return val_ == static_cast<const Boolean &>(value).val_ ? 0 : 1;
    }
}

BaseType &Boolean::assign(const BaseType &value)
{
    if (value.is_a<Boolean>())
        assign(static_cast<const Boolean &>(value).val_);
    else if (value.is_a<NilClass>())
        assign(false);
    else
        throw DuckTypeError("incompatible type for assigment");
    return *this;
}

BaseType &Boolean::assign(bool value)
{
    if (frozen_)
        throw DuckTypeError("cannot assign frozen object");
    val_ = value;
    return *this;
}


std::string Boolean::to_string() const
{
    return val_ ? "true" : "false";
}

integer_type Boolean::to_integer() const
{
    return val_ ? 1 : 0;
}

real_type Boolean::to_real() const
{
    return val_ ? 1.0 : 0;
}

} // CDuckType
