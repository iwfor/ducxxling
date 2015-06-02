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

#include "ducxxling/iterator.h"
#include "ducxxling/duck_type.h"
#include "iterator_impl.h"

namespace Ducxxling {

DTI_DEFINE_TYPE(Iterator, BaseType);

Iterator::Iterator(const Iterator &value)
    : BaseType(), pimpl_(0)
{
    pimpl_ = static_cast<IteratorImpl*>(value.pimpl_->dup());
}

Iterator::Iterator(const IteratorImpl &value)
    : BaseType(), pimpl_(0)
{
    pimpl_ = static_cast<IteratorImpl*>(value.dup());
}

Iterator::~Iterator()
{
    if (pimpl_)
        delete pimpl_;
}

BaseType *Iterator::dup() const
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    return new Iterator(*pimpl_);
}

bool Iterator::equals(const BaseType &value) const
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    return pimpl_->equals(*static_cast<const Iterator&>(value).pimpl_);
}

BaseType &Iterator::assign(const BaseType &value)
{
    if (!value.is_a<Iterator>()) {
        throw DuckTypeError("cannot assign non-Iterator to Iterator");
    }
    if (pimpl_)
        delete pimpl_;
    const IteratorImpl *imp = static_cast<const Iterator &>(value).pimpl_;
    pimpl_ = static_cast<IteratorImpl*>(imp->dup());
    return *this;
}

/**
 * Prefix increment.
 */
Iterator &Iterator::operator++()
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    pimpl_->increment();
    return *this;
}

/**
 * Postfix increment.
 */
Iterator Iterator::operator++(int)
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    Iterator copy(*pimpl_);
    pimpl_->increment();
    return copy;
}

/**
 * Prefix decrement.
 */
Iterator &Iterator::operator--()
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    pimpl_->decrement();
    return *this;
}

/**
 * Postfix decrement.
 */
Iterator Iterator::operator--(int)
{
    if (pimpl_ == 0)
        throw DuckTypeError("pimpl_ is NULL");
    Iterator copy(*pimpl_);
    pimpl_->decrement();
    return copy;
}

/**
 * Get reference to value.
 */
DuckType &Iterator::value()
{
    if (pimpl_ == 0)
        return terminator;
    return pimpl_->value();
}

/**
 * Get reference to const value.
 */
const DuckType &Iterator::value() const
{
    if (pimpl_ == 0)
        return terminator;
    return pimpl_->value();
}

} // Ducxxling
