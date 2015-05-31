# cxxvars.mk
# NOSPB (New Old School Project Builder)
# C++ Initialization Module.
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

# Supported Vendors: GCC, MS
CXXVENDOR?=GCC

SUFDEBUG=_gd
SUFSTATIC?=_s

SUFOBJ=.o
SUFLIB=.a

ifdef ISUNIX
  PRELIB=lib
  ifdef PLATFORM_DARWIN
    SUFSHR=.dylib
  else
    SUFSHR=.so
  endif
endif
ifdef ISWINDOWS
  ifeq ($(CXXVENDOR),MS)
    SUFLIB:=.lib
    SUFOBJ:=.obj
  endif
  SUFBIN=.exe
  SUFSHR=.dll
endif

ifeq ($(CXXVENDOR),GCC)
  CC=gcc
  CXX=g++
  AR=ar
  SAR=g++
  LD=g++
  CXXFLAGS+=-Wall
  CFLAGS+=-Wall
  ARFLAGS=r
  # Note: There is a purposeful space after -o
  LDOUT=-o 
  DEBUGCXXFLAGS=-g
  DEBUGCFLAGS=-g
  RELEASECXXFLAGS=-O2
  RELEASECFLAGS=-O2
endif
ifeq ($(CXXVENDOR),CLANG)
  CC=clang
  CXX=clang++
  AR=ar
  SAR=clang++
  LD=clang++
  CXXFLAGS+=-Wall
  CFLAGS+=-Wall
  ARFLAGS=r
  # Note: There is a purposeful space after -o
  LDOUT=-o 
  DEBUGCXXFLAGS=-g
  DEBUGCFLAGS=-g
  RELEASECXXFLAGS=-O2
  RELEASECFLAGS=-O2
endif
ifeq ($(CXXVENDOR),MS)
  CC=cl /nologo
  CXX=cl /nologo
  AR=link /nologo /lib
  SAR=link /nologo /dll
  LIB=link /nologo
  CXXFLAGS+=-EHsc -W3 -Wp64
  CFLAGS+=-W3 -Wp64
  AROUT=/out:
  LDOUT=/out:
  DEBUGCPPFLAGS+=-DDEBUG
  DEBUGCXXFLAGS+=-Od -Z7
  DEBUGCFLAGS+=-Od -Z7
  DEBUGLDFLAGS+=/debug
  DEBUGSARFLAGS+=/debug
  RELEASECPPFLAGS+=-DNDEBUG
  RELEASECXXFLAGS+=-Ox
  RELEASECFLAGS+=-Ox
endif

#==============================================================================
# CxxTest variables
CXXTEST=$(__nospb_dir)../vendor/cxxtest
CXXTESTGEN=$(CXXTEST)/cxxtestgen.pl
TESTCPPFLAGS+=-I$(CXXTEST) -I.
