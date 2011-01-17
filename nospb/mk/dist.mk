# dist.mk
# NOSPB (New Old School Project Builder)
# File distribution rules.
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

# $var DISTDIR
#   Directory to receive files for $DISTFILES and $DISTFLATTENFILES.
# $var DISTTO
#   Subdirectory of $DISTDIR to receive files.
ifdef DISTTO
  __dist_dir=$(DISTDIR)/$(DISTTO)
else
  __dist_dir=$(DISTDIR)
endif

# $var DISTFILES
#   List of files to copy to $DISTDIR/$DISTTO, preserving directory structure.
ifdef DISTFILES
    __dist_out_files=$(DISTFILES:%=$(__dist_dir)/%)
endif

# $var DISTFLATTENFILES
#   List of files to copy to $DISTDIR/$DISTTO, flattening directory structure.
ifdef DISTFLATTENFILES
    # Get the directories of all the source files.
    __dist_flatten_source_dirs=$(sort $(foreach f,$(DISTFLATTENFILES),$(dir $(f))))
    # Add the source directories to the vpath.
    vpath % $(__dist_flatten_source_dirs)
    # Build a list of the destiation files.
    __dist_flatten_target_files=$(foreach f,$(DISTFLATTENFILES),$(notdir $(f)))
endif

CLEANFILES+=$(__dist_out_files) $(__dist_flatten_target_files)

dist:: $(__dist_out_files) $(__dist_flatten_target_files)

$(__dist_dir)/% : %
	$(MKDIR) $(dir $@)
	$(CP) $< $@

default:: dist
