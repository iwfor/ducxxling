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

#include "array_iterator.h"

namespace CDuckType {

DTI_DEFINE_TYPE(ArrayIterator, IteratorImpl);
DTI_DEFINE_TYPE(ArrayConstIterator, IteratorImpl);
DTI_DEFINE_TYPE(ArrayReverseIterator, IteratorImpl);
DTI_DEFINE_TYPE(ArrayConstReverseIterator, IteratorImpl);

#define ARRAY_ITERATOR_CLASS_IMPL(class_name, iterator_type) \
class_name::class_name() \
{ \
} \
\
class_name::class_name(const iterator_type &value) \
    : i_(value) \
{ \
} \
\
class_name::~class_name() \
{ \
} \
\
BaseType *class_name::dup() const \
{ \
    return new class_name(i_); \
} \
\
bool class_name::equals(const BaseType &value) const \
{ \
    if (!value.is_a<class_name>()) \
        return false; \
    const class_name &v = static_cast<const class_name &>(value); \
    return i_ == v.i_; \
} \
\
BaseType &class_name::assign(const BaseType &value) \
{ \
    if (!value.is_a<class_name>()) \
        throw DuckTypeError("Cannot assign non-" #class_name "value to " #class_name); \
    const class_name &v = static_cast<const class_name &>(value); \
    i_ = v.i_; \
    return *this; \
} \
\
BaseType &class_name::assign(const iterator_type &value) \
{ \
    i_ = value; \
    return *this; \
} \
\
IteratorImpl &class_name::increment() \
{ \
    ++i_; \
    return *this; \
} \
\
IteratorImpl &class_name::decrement() \
{ \
    --i_; \
    return *this; \
} \
\
DuckType &class_name::value() \
{ \
    return const_cast<DuckType &>(*i_); /* cheater */ \
} \
\
const DuckType &class_name::value() const \
{ \
    return *i_; \
} \
\
class_name &class_name::operator=(const iterator_type &value) \
{ \
    i_ = value; \
    return *this; \
}

ARRAY_ITERATOR_CLASS_IMPL(ArrayIterator, array_type::iterator);
ARRAY_ITERATOR_CLASS_IMPL(ArrayConstIterator, array_type::const_iterator);
ARRAY_ITERATOR_CLASS_IMPL(ArrayReverseIterator, array_type::reverse_iterator);
ARRAY_ITERATOR_CLASS_IMPL(ArrayConstReverseIterator, array_type::const_reverse_iterator);

} // namespace CDuckType
