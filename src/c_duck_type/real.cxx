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

#include "c_duck_type/real.h"
#include <sstream>

namespace CDuckType {

DTI_DEFINE_TYPE(Real, "Real", Scalar);

Real::Real()
    : Scalar(), val_(0)
{
}

Real::Real(real_type value)
    : Scalar(), val_(value)
{
}

Real::Real(const Real &value)
    : Scalar(), val_(value.val_)
{
}

Real::~Real()
{
}

BaseType *Real::dup() const
{
    return new Real(val_);
}

bool Real::equals(const BaseType &value) const
{
    return value.is_a<Real>() && val_ == static_cast<const Real &>(value).val_;
}

int Real::compare(const BaseType &value) const
{
    if (!value.is_a<Real>())
        throw DuckTypeError("cannot assign Real to non-Real");
    real_type other = static_cast<const Real &>(value).val_;
    return val_ == other ? 0 : (val_ < other ? -1 : 1);
}

BaseType &Real::assign(const BaseType &value)
{
    if (!value.is_a<Real>())
        throw DuckTypeError("cannot assign non-Real value to Real");
    val_ = static_cast<const Real &>(value).val_;
    return *this;
}

BaseType &Real::assign(real_type value)
{
    if (frozen_)
        throw DuckTypeError("cannot assign frozen object");
    val_ = value;
    return *this;
}

string_type Real::to_string() const
{
    std::stringstream s;
    s << val_;
    return s.str();
}

integer_type Real::to_integer() const
{
    return val_;
}

real_type Real::to_real() const
{
    return static_cast<double>(val_);
}

} // CDuckType
