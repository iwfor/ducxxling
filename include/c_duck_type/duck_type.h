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
    // Forward declarations
    class Iterator;

    /**
     * A DuckType is a container for any BaseType object.
     */
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
         * Get the BaseType of this object.
         */
        BaseType &value();

        /**
         * Get the const BaseType of this object.
         */
        const BaseType &value() const;

        /**
         * Swap the BaseTypes of this and the given DuckType.
         *
         * \param   val     DuckType with whose value to swap.
         */
        DuckType &swap(DuckType &);

        /**
         * Assign a new DuckType value.
         *
         * \param   val     DuckType whose value to copy.
         */
        DuckType &operator=(const DuckType &val);

        /**
         * Assign a new BaseType value.
         *
         * \param   val     BaseType whose value to copy.
         */
        DuckType &operator=(const BaseType &val);

        /**
         * Assign a new String value from a C string.
         *
         * \param   val     C string whose value to copy.
         */
        DuckType &operator=(const char *val);

        /**
         * Assign a new String value from a standard string.
         *
         * \param   val     Standard string whose value to copy.
         */
        DuckType &operator=(const string_type &val);

        /**
         * Assign a new Integer value.
         *
         * \param   val     New integer value.
         */
        DuckType &operator=(integer_type);

        /**
         * Assign a new Real value.
         *
         * \param   val     New real value.
         */
        DuckType &operator=(real_type);

        /**
         * Assign a new Boolean value.
         *
         * \param   val     New bool value.
         */
        DuckType &operator=(bool);

        /**
         * If this is a Scalar type, return its value as a standard string.
         *
         * \throw   DuckTypeError
         */
        string_type to_string() const;

        /**
         * If this is a Scalar type, return its value as an integer.
         *
         * \throw   DuckTypeError
         */
        integer_type to_integer() const;

        /**
         * If this is a Scalar type, return its value as a double.
         *
         * \throw   DuckTypeError
         */
        real_type to_real() const;

        /**
         * If this is a String type, return a reference to its standard string.
         *
         * \throw   DuckTypeError
         */
        string_type &string();

        /**
         * If this is a String type, return a constant reference to its standard string.
         *
         * \throw   DuckTypeError
         */
        const string_type &string() const;

        /**
         * Check whether this object is of the requested type.
         *
         * \return  true if this object is of given type; false otherwise.
         * \code
         *     if (dt.is_a<String>())
         *         dt.string()[0]; // get first character in string
         * \endcode
         */
        template <typename T>
        bool is_a() const {
            return value_->is_a<T>();
        }

        /**
         * Check whether this object shares the same type as the given BaseType.
         *
         * \return  true if this object is of given type; false otherwise.
         */
        bool is_a(const BaseType &) const;

        /**
         * Check whether this object shares the same type as the given DuckType.
         *
         * \return  true if this object is of given type; false otherwise.
         */
        bool is_a(const DuckType &) const;

        /**
         * Get the first element of a Pair.
         * \throw   DuckTypeError
         */
        DuckType &first();

        /**
         * Get the constant first element of a Pair.
         * \throw   DuckTypeError
         */
        const DuckType &first() const;

        /**
         * Get the second element of a Pair.
         * \throw   DuckTypeError
         */
        DuckType &second();

        /**
         * Get the constant second element of a Pair.
         * \throw   DuckTypeError
         */
        const DuckType &second() const;

        /**
         * Get the Iterator held in this DuckType.
         *
         * \throw   DuckTypeError   Throws error when not an Iterator.
         */
        Iterator &iterator();

        /**
         * Get the constant Iterator held in this DuckType.
         *
         * \throw   DuckTypeError   Throws error when not an Iterator.
         */
        const Iterator &iterator() const;

    protected:
        BaseType *value_;

        void free();
    };

    extern DuckType terminator;

} // CDuckType

#endif // include_c_duck_type_type_h
