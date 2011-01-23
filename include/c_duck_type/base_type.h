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

#ifndef include_c_duck_type_base_h
#define include_c_duck_type_base_h

#include "c_duck_type/dti.h"
#include "c_duck_type/except.h"

namespace CDuckType {

    class BaseType {
        DTI_DECLARE_DYNAMIC_TYPE;
    public:
        BaseType();
        virtual ~BaseType();

        /**
         * Create a copy of the this object and return a pointer.
         */
        virtual BaseType *dup() const = 0;

        /**
         * Check whether the current object is the same type as the given object.
         *
         * \param   base    Object to compare against.
         * \return  true if object and base share a type; false if not.
         */
        bool is_a(const BaseType &base) const;

        template<class T>
        bool is_a() const
        {
            return get_dti_type().is_a(&T::type_);
        }

        /**
         * Test equality.
         */
        virtual bool equals(const BaseType &value) const = 0;

        /**
         * Perform assignment.
         */
        virtual BaseType &assign(const BaseType &) = 0;

        /**
         * Prevent this instance from being updated.
         */
        void freeze();

    protected:
        /*
         * Frozen objects should not be alterable.
         */
        bool frozen_;
    };

} // CDuckType

#endif // include_c_duck_type_base_h
