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

#ifndef include_ducxxling_iterator_h
#define include_ducxxling_iterator_h

#include "ducxxling/base_type.h"

namespace Ducxxling {
    // Forward Declarations
    class IteratorImpl;
    class DuckType;

    /**
     * The Iterator class is a pure virtual class for an object that allows
     * iteration through a container of DuckTypes.
     */
    class Iterator : public BaseType {
        DTI_DECLARE_DYNAMIC_TYPE;
    public:
        Iterator(const Iterator &);
        Iterator(const IteratorImpl &);
        virtual ~Iterator();

        virtual BaseType *dup() const;
        virtual bool equals(const BaseType &) const;
        virtual BaseType &assign(const BaseType &);

        /**
         * Prefix increment.
         */
        Iterator &operator++();

        /**
         * Postfix increment.
         */
        Iterator operator++(int);

        /**
         * Prefix decrement.
         */
        Iterator &operator--();

        /**
         * Postfix decrement.
         */
        Iterator operator--(int);

        /**
         * Get reference to value.
         */
        DuckType &value();

        /**
         * Get reference to const value.
         */
        const DuckType &value() const;

    private:
        Iterator(); // Do not allow calling the default constructor

        IteratorImpl *pimpl_;
    };

} // namespace Ducxxling

#endif // include_ducxxling_iterator_h
