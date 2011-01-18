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

#include "c_duck_type/nil_class.h"

namespace CDuckType {

DTI_DEFINE_TYPE(NilClass, "NilClass", BaseType);

NilClass::NilClass()
    : BaseType()
{
}

NilClass::~NilClass()
{
}

BaseType *NilClass::dup() const
{
    return new NilClass;
}

int NilClass::compare(const BaseType &value) const
{
    return value.is_a<NilClass>() ? 0 : -1;
}

bool NilClass::equals(const BaseType &value) const
{
    return value.get_dti_type().is_a(&NilClass::type_);
}

BaseType &NilClass::assign(const BaseType &value)
{
    if (!value.is_a<NilClass>()) {
        throw DuckTypeError("cannot assign value to a nil object");
    }
    return *this;
}

string_type NilClass::to_string() const
{
    throw DuckTypeError("cannot convert nil to string");
    return "";
}

integer_type NilClass::to_integer() const
{
    throw DuckTypeError("cannot convert nil to integer");
    return 0;
}

real_type NilClass::to_real() const
{
    throw DuckTypeError("cannot convert nil to real");
    return 0.0;
}

// Declare the global "nil" instance.
NilClass nil;

} // CDuckType
