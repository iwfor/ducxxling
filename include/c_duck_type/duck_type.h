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
/*
 * This code is loosely based on the Boost::any class.
 */

#ifndef include_c_duck_type_type_h
#define include_c_duck_type_type_h

#include "c_duck_type/base_type.h"

namespace CDuckType {

    class DuckType {
    public:
        DuckType();
        DuckType(const DuckType &);
        DuckType(const BaseType &);
        DuckType(const char*);
        DuckType(integer_type);
        DuckType(real_type);
        DuckType(bool);
        virtual ~DuckType();

        /**
         *
         */
        DuckType &assign(const BaseType &);

        /**
         *
         */
        DuckType &swap(DuckType &);

        /**
         *
         */
        DuckType &operator=(const DuckType &);

        /**
         *
         */
        DuckType &operator=(const BaseType &);

        /**
         *
         */
        DuckType &operator=(const char*);

        /**
         *
         */
        DuckType &operator=(integer_type);

        /**
         *
         */
        DuckType &operator=(real_type);

        /**
         *
         */
        DuckType &operator=(bool);

        /**
         *
         */
        string_type to_string() const;

        /**
         *
         */
        integer_type to_integer() const;

        /**
         *
         */
        real_type to_real() const;

        /**
         *
         */
        template <typename T>
        bool is_a() const {
            return value_->is_a<T>();
        }

        /**
         *
         */
        bool is_a(const BaseType &value) const;

        /**
         *
         */
        bool is_a(const DuckType &value) const;
    protected:
        BaseType *value_;

        void free();
    };

} // CDuckType

#endif // include_c_duck_type_type_h
