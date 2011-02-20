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

#include "ducxxling/pair.h"

namespace Ducxxling {

DTI_DEFINE_TYPE(Pair, BaseType);

Pair::Pair()
    : BaseType()
{
}

Pair::Pair(const Pair &p)
    : BaseType(), first(p.first), second(p.second)
{
}

Pair::Pair(const DuckType &f, const DuckType &s)
    : BaseType(), first(f), second(s)
{
}

Pair::Pair(const BaseType &f, const BaseType &s)
    : BaseType(), first(f), second(s)
{
}

Pair::~Pair()
{
}

BaseType *Pair::dup() const
{
    return new Pair(first, second);
}

BaseType &Pair::assign(const BaseType &val)
{
    if (!val.is_a<Pair>())
        throw DuckTypeError("cannot assign non-Pair to Pair");
    const Pair &p = static_cast<const Pair&>(val);
    first = p.first;
    second = p.second;
    return *this;
}

bool Pair::equals(const BaseType &val) const
{
    if (!val.is_a<Pair>())
        return false;
    const Pair &p = static_cast<const Pair&>(val);
    bool fr = first.value().equals(p.first.value());
    return fr ? second.value().equals(p.second.value()) : fr;
}

} // Ducxxling
