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

#include "c_duck_type/array.h"
#include "array_iterator.h"

namespace CDuckType {

DTI_DEFINE_TYPE(Array, Container);

array_type instantiate_array;

Array::Array()
    : Container()
{
}

Array::Array(const Array &data)
    : Container()
{
    size_type s = data.size();
    data_.resize(s);
    for (size_type i = 0; i < s; ++s) {
        data_[i] = data[i];
    }
}

Array::~Array()
{
}

BaseType *Array::dup() const
{
    return new Array(*this);
}

bool Array::equals(const BaseType &value) const
{
    if (!value.is_a<Array>())
        return false;
    const Array &data = static_cast<const Array &>(value);
    if (data.size() != data_.size())
        return false;
    // TODO
//    size_type s = data.size();
//    for (size_type i = 0; i < s; ++i)
//        if (data[i] != data_[i])
//            return false;
    return true;
}

BaseType &Array::assign(const BaseType &data)
{
    if (!data.is_a<Array>()) {
        throw DuckTypeError("cannot assign non-Array to Array");
    }
    return *this;
}

size_type Array::size() const
{
    return data_.size();
}

Iterator Array::begin()
{
    ArrayIterator i(data_.begin());
    Iterator it(i);
    return it;
}

const Iterator Array::begin() const
{
    ArrayConstIterator i(data_.begin());
    Iterator it(i);
    return it;
}

Iterator Array::end()
{
    ArrayIterator i(data_.end());
    Iterator it(i);
    return it;
}

const Iterator Array::end() const
{
    ArrayConstIterator i(data_.end());
    Iterator it(i);
    return it;
}

Iterator Array::rbegin()
{
    ArrayReverseIterator i(data_.rbegin());
    Iterator it(i);
    return it;
}

const Iterator Array::rbegin() const
{
    ArrayConstReverseIterator i(data_.rbegin());
    Iterator it(i);
    return it;
}

Iterator Array::rend()
{
    ArrayReverseIterator i(data_.rend());
    Iterator it(i);
    return it;
}

const Iterator Array::rend() const
{
    ArrayConstReverseIterator i(data_.rend());
    Iterator it(i);
    return it;
}

DuckType &Array::operator[](size_type index)
{
    return data_[index];
}

const DuckType &Array::operator[](size_type index) const
{
    return data_[index];
}


} // CDuckType
