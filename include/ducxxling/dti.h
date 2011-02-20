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
 * The Dynamic Type Information class is based on an example provided by Scott
 * Wakeling in Game Programming Gems, Volume 2.  This version has been modified
 * to fit the requirements of the Ducxxling project.
 */

#ifndef include_ducxxling_dti_h
#define include_ducxxling_dti_h

#include "ducxxling/config.h"
#include <string>

namespace Ducxxling {
    /**
     * The DTI class defines Dynamic Type Information for a class that contains
     * it as a static member.  This allows a class to perform a certain level
     * of introspection with out having to enable RTTI.
     *
     * The subscribing class should include the DTI_DECLARE_DYNAMIC_TYPE macro
     * in its declaration, and either the DTI_DEFINE_TYPE or
     * DTI_DEFINE_TOP_TYPE in its definition file.
     */
    class DTI {
    public:
        /**
         * Constructor that specifies the current type as a top level type.
         *
         * \param   name        String name representing type.
         */
        DTI(const std::string &name);

        /**
         * Constructor that specifies the current type as a child of
         * another type.
         *
         * \param   name        String name representing type.
         * \param   parent      Pointer to the dynamic type information
         *                      of the parent of this class.
         */
        DTI(const std::string &name, const DTI *parent);

        /**
         * Virtual destructor.
         */
        virtual ~DTI();

        /**
         * Get the string name of the type.
         */
        const std::string &get_name() const;

        /**
         * Get a pointer to the parent DTI information, or null if this is
         * a top level type.
         */
        const DTI *get_parent() const;

        /**
         * Determine if a type is a member of a type chain.
         */
        bool is_a(const DTI *type) const;

    private:
        /**
         * The parameterless version of the DTI constructor may not be called.
         */
        DTI();

        /**
         * The string name representing the type.
         */
        std::string name_;

        /**
         * A pointer to the parent of this type, or null if this is a top
         * level type.
         */
        const DTI *parent_;
    };
} // Ducxxling

/**
 * The DTI_DECLARE_DYNAMIC_TYPE macro declares the Dynamic Type Information
 * member and required methods.  The virtual get_dti_type_name() and
 * get_dti_type() methods are required to access the type_ member so that types
 * are correctly identified in an inheritance chain.
 */
#define DTI_DECLARE_DYNAMIC_TYPE \
    public: \
        static Ducxxling::DTI type_; \
        virtual const Ducxxling::DTI &get_dti_type() const; \
        virtual const std::string &get_dti_type_name() const;

#define DTI_DEFINE_ACCESSOR_FUNCTIONS(class_name) \
    const Ducxxling::DTI &class_name::get_dti_type() const { return type_; } \
    const std::string &class_name::get_dti_type_name() const { return type_.get_name(); }

#define DTI_DEFINE_TOP_TYPE(class_name) \
    Ducxxling::DTI class_name::type_(#class_name); \
    DTI_DEFINE_ACCESSOR_FUNCTIONS(class_name)

#define DTI_DEFINE_TYPE(class_name, parent) \
    Ducxxling::DTI class_name::type_(#class_name, &parent::type_); \
    DTI_DEFINE_ACCESSOR_FUNCTIONS(class_name)

#endif // include_ducxxling_dti_h
