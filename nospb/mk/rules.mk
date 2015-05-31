# rules.mk
# NOSPB (New Old School Project Builder)
# Primary ruleset (include this in project).
#==============================================================================
# Copyright (c) 2007-2015 Isaac W. Foraker
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the NOSPB nor the names of its contributors may be
#       used to endorse or promote products derived from this software without
#       specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#==============================================================================
ifndef .FEATURES
    $(error Must use GNU Make 3.81 or later)
endif
#==============================================================================
ifndef TOP
  $(error TOP not defined)
endif
#==============================================================================
# Get the nospb include dir.
__nospb_dir:=$(patsubst %rules.mk,%,$(lastword $(MAKEFILE_LIST)))
#==============================================================================
# Load project specific configuration, generated from project.config
-include $(TOP)/config.mk
#==============================================================================
# Set NAME if not specified.
NAME?=$(not-dir $(CURDIR))
#==============================================================================
# Process build variant information
ifndef VARIANTS
    ifdef DEBUG
        VARIANTS+=debug
    endif
    ifdef RELEASE
        VARIANTS+=release
    endif
    ifndef VARIANTS
        VARIANTS=release
    endif
endif
ifneq (,$(filter release,$(VARIANTS)))
    RELEASE=1
endif
ifneq (,$(filter debug,$(VARIANTS)))
    DEBUG=1
endif
#==============================================================================
include $(__nospb_dir)debug.mk
include $(__nospb_dir)funcs.mk
include $(__nospb_dir)os.mk
include $(__nospb_dir)cxxvars.mk
#==============================================================================
# The DIRS is a user specified list of directories containing source code.
DIRS?=.
# The WORKDIR is the root of all output files.
WORKDIR?=$(TOP)/work
# The OBJDIR contains C/C++ object files.
OBJDIR?=$(WORKDIR)/obj
# The GENDIR contains all generated files.
GENDIR?=$(WORKDIR)/gen
# The GENSOURCEDIR contains all generated source files.
GENSOURCEDIR?=$(GENDIR)/src
# The TESTDIR contains executables for C++ unit tests.
TESTDIR?=$(WORKDIR)/test
# This DISTDIR contains the final distribution image.  Just about everything
# except intermediate objects and test files will go somewhere under DISTDIR.
DISTDIR?=$(TOP)/dist
# The LIBDIR contains all build library files.
LIBDIR?=$(DISTDIR)/lib
# The BINDIR contains all built binary executable files.
BINDIR?=$(DISTDIR)/bin
# The SHRDIR contains all built shared libraries.  Note that the SHRDIR is
# different between Windows and non-Windows platforms.
SHRDIR?=$(if $(ISWINDOWS),$(BINDIR),$(LIBDIR))
# The DOCDIR contains all 
DOCDIR?=$(DISTDIR)/share/doc

# Common tools.
MKDIR=mkdir -p
RM=rm -rf
CP=cp

#==============================================================================
-include $(TOP)/project.mk
#==============================================================================
.PHONY: default all test clean

default::

all:: default test

test::

#==============================================================================
ifdef SUBDIRS
  include $(__nospb_dir)subdirs.mk
endif
#==============================================================================
ifdef DISTFILES
  include $(__nospb_dir)dist.mk
endif
#==============================================================================
ifneq (,$(filter lib bin shr test,$(WHAT)))
  include $(__nospb_dir)cxx.mk
endif
#==============================================================================
# The clean target goes after all includes.
clean::
ifdef CLEANFILES
	$(RM) $(CLEANFILES)
endif
