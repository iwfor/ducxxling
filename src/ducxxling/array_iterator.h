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

#ifndef include_ducxxling_array_iterator_h
#define include_ducxxling_array_iterator_h

#include "ducxxling/array.h"
#include "iterator_impl.h"

namespace Ducxxling {
#define ARRAY_ITERATOR_CLASS(class_name, iterator_type) \
    class class_name : public IteratorImpl { \
        DTI_DECLARE_DYNAMIC_TYPE; \
    public: \
        class_name(); \
        class_name(const iterator_type &value); \
        virtual ~class_name(); \
 \
        virtual BaseType *dup() const; \
        virtual bool equals(const BaseType &value) const; \
        virtual BaseType &assign(const BaseType &value); \
        virtual BaseType &assign(const iterator_type &value); \
 \
        virtual IteratorImpl &increment(); \
        virtual IteratorImpl &decrement(); \
        virtual DuckType &value(); \
        virtual const DuckType &value() const; \
        virtual class_name &operator=(const iterator_type &value); \
 \
    protected: \
        iterator_type i_; \
    };

    ARRAY_ITERATOR_CLASS(ArrayIterator, array_type::iterator);
    ARRAY_ITERATOR_CLASS(ArrayConstIterator, array_type::const_iterator);
    ARRAY_ITERATOR_CLASS(ArrayReverseIterator, array_type::reverse_iterator);
    ARRAY_ITERATOR_CLASS(ArrayConstReverseIterator, array_type::const_reverse_iterator);
} // namespace Ducxxling

#endif // include_ducxxling_iterator_h
