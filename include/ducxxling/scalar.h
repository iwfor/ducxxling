/*
 * Copyright (c) 2011-2015 Isaac W. Foraker, all rights reserved.
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

#ifndef include_ducxxling_scalar_h
#define include_ducxxling_scalar_h

#include "ducxxling/base_type.h"

namespace Ducxxling {

    class Scalar : public BaseType {
        DTI_DECLARE_DYNAMIC_TYPE;
    public:
        Scalar();
        virtual ~Scalar();

        /**
         * Compare values.
         *
         * \param   value   Value to compare against.
         * \return  -1 if less than value;
         * \return  0 if equal;
         * \return  1 if greater than value.
         */
        virtual int compare(const BaseType &value) const = 0;

        /**
         * Convert this instance of BaseType to a string.
         */
        virtual string_type to_string() const = 0;

        /**
         * Convert this instance of BaseType to an integer type.
         */
        virtual integer_type to_integer() const = 0;

        /**
         * Convert this instance of BaseType to a floating point type.
         */
        virtual real_type to_real() const = 0;
    };

} // Ducxxling

#endif // include_ducxxling_scalar_h
