# os.mk
# NOSPB (New Old School Project Builder)
# OS Determination.
#==============================================================================
# Copyright (c) 2007-2008 Isaac W. Foraker
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#     * Redistributions of source code must retain the above copyright notice,
#	    this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#  		notice, this list of conditions and the following disclaimer in the
# 		documentation and/or other materials provided with the distribution.
#     * Neither the name of the NOSPB nor the names of its contributors may be
#		used to endorse or promote products derived from this software without
#		specific prior written permission.
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

# Try to determine OS name without shelling out to uname if possible.
ifndef __uname
  export __uname:=$(OSNAME)
endif
ifndef __uname
  export __uname:=$(OSTYPE)
endif
ifndef __uname
  # Assume we're running MinGW if not Cygwin.
  export __uname:=$(if $(COMSPEC),mingw,)
endif
ifndef __uname
  # Ran out of environment tricks, so just run uname.
  export __uname:=$(shell uname)
endif

ifeq ($(__uname),cygwin)
  PLATFORM_CYGWIN=1
  ISWINDOWS=1
endif
ifeq ($(__uname),mingw)
  PLATFORM_MINGW=1
  ISWINDOWS=1
endif
ifeq ($(__uname),Darwin)
  PLATFORM_DARWIN=1
  ISBSD=1
  ISUNIX=1
endif
ifeq ($(__uname),FreeBSD)
  PLATFORM_FREEBSD=1
  ISBSD=1
  ISUNIX=1
endif
ifeq ($(__uname),Linux)
  PLATFORM_LINUX=1
  ISUNIX=1
endif
