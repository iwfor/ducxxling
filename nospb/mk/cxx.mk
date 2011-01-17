# cxx.mk
# NOSPB (New Old School Project Builder)
# C++ Rules Module.
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

CFILES?=$(call __find_files,$(DIRS),,.cxx .cpp .c)

__cur_obj_dir=$(OBJDIR)/$(NAME)
__obj_dir=$(__debug_tr2)$(OBJDIR)/$2/$1/$(NAME)

#==============================================================================
# Convert LIBRARIES into LDFLAGS
ifeq ($(CXXVENDOR),GCC)
  LDFLAGS+=-L$(LIBDIR)
  LDLIBS+=$(foreach lib,$(LIBRARIES),-l$(lib))
endif
ifeq ($(CXXVENDOR),MS)
  LDFLAGS+=/LIBPATH:$(LIBDIR)
  LDLIBS+=$(foreach lib,$(LIBRARIES),$(lib)$(SUFLIB))
endif

#==============================================================================
define __cc_command
	$(__debug_tr4)
	@echo "### Compiling $(notdir $1)"
	$(MKDIR) $(dir $1)
	$(CC) $(CPPFLAGS) $3 $(CFLAGS) $4 -o $1 -c $2
endef
#==============================================================================
define __cxx_command
	$(__debug_tr4)
	@echo "### Compiling $(notdir $1)"
	$(MKDIR) $(dir $1)
	$(CXX) $(CPPFLAGS) $3 $(CXXFLAGS) $4 -o $1 -c $2
endef
#==============================================================================
# The __cxx_target macro generates a target to build a specific object file.
# TODO Now that each C++/Object pair is individually defined, this needs to
# dynamically load the header dependencies.
define __cxx_target
$1 : $2
	$(__debug_tr4)
	$(call $(if $(filter %.c,$2),__cc_command,__cxx_command),$1,$2,$3,$4)
endef
#==============================================================================
define __gen_obj_targets
  $(foreach cfile,$(CFILES), \
      $(foreach objdir,$1, \
          $(eval \
            $(call __cxx_target,$(objdir)/$(subst %.cpp,%$(SUFOBJ),$(subst %.c,%$(SUFOBJ),$(cfile:%.cxx=%$(SUFOBJ)))),$(cfile),$(LIBCPPFLAGS),$(LIBCXXFLAGS))
           ) \
        ) \
    )
endef

#==============================================================================
# Determine raw object names
__objects:=$(CFILES:%.cxx=%$(SUFOBJ))
__objects:=$(__objects:%.cpp=%$(SUFOBJ))
__objects:=$(__objects:%.c=%$(SUFOBJ))

#==============================================================================
ifneq (,$(filter lib,$(WHAT)))
  DEBUGLIBOUT=$(LIBDIR)/$(PRELIB)$(NAME)$(SUFSTATIC)$(SUFDEBUG)$(SUFLIB)
  RELEASELIBOUT=$(LIBDIR)/$(PRELIB)$(NAME)$(SUFSTATIC)$(SUFLIB)
  __debug_lib_obj_dir:=$(call __obj_dir,lib,debug)
  __release_lib_obj_dir:=$(call __obj_dir,lib,release)
  DEBUGLIBOBJECTS=$(foreach file,$(__objects),$(__debug_lib_obj_dir)/$(file))
  RELEASELIBOBJECTS=$(foreach file,$(__objects),$(__release_lib_obj_dir)/$(file))
  # Generate object file targets for each source file.
  $(call __gen_obj_targets,$(__debug_lib_obj_dir) $(__release_lib_obj_dir),$(LIBCPPFLAGS),$(LIBCXXFLAGS))
  __cxx_targets+=lib
  CLEANFILES+=$(DEBUGLIBOUT) $(RELEASELIBOUT) $(__debug_lib_obj_dir) $(__release_lib_obj_dir)
endif

#==============================================================================
ifneq (,$(filter shr,$(WHAT)))
  DEBUGSHROUT=$(SHRDIR)/$(PRESHR)$(NAME)$(SUFDEBUG)$(SUFSHR)
  RELEASESHROUT=$(SHRDIR)/$(PRESHR)$(NAME)$(SUFSHR)
  __debug_shr_obj_dir:=$(call __obj_dir,shr,debug)
  __release_shr_obj_dir:=$(call __obj_dir,shr,release)
  DEBUGSHROBJECTS=$(foreach file,$(__objects),$(__debug_shr_obj_dir)/$(file))
  RELEASESHROBJECTS=$(foreach file,$(__objects),$(__release_shr_obj_dir)/$(file))
  # Generate object file targets for each source file.
  $(call __gen_obj_targets,$(__debug_shr_obj_dir) $(__release_shr_obj_dir),$(SHRCPPFLAGS),$(SHRCXXFLAGS))
  __cxx_targets+=shr
  CLEANFILES+=$(DEBUGSHROUT) $(RELEASESHROUT) $(__debug_shr_obj_dir) $(__release_shr_obj_dir)
endif

#==============================================================================
ifneq (,$(filter bin,$(WHAT)))
  ifneq (,$(filter test,$(WHAT)))
    $(error The 'test' target is incompatible with the 'bin' target.  Use with 'lib' or 'shr' instead.)
  endif
  DEBUGBINOUT=$(BINDIR)/$(PREBIN)$(NAME)$(SUFDEBUG)$(SUFBIN)
  RELEASEBINOUT=$(BINDIR)/$(PREBIN)$(NAME)$(SUFBIN)
  __debug_bin_obj_dir:=$(call __obj_dir,bin,debug)
  __release_bin_obj_dir:=$(call __obj_dir,bin,release)
  DEBUGBINOBJECTS=$(foreach file,$(__objects),$(__debug_bin_obj_dir)/$(file))
  RELEASEBINOBJECTS=$(foreach file,$(__objects),$(__release_bin_obj_dir)/$(file))
  # Generate object file targets for each source file.
  $(call __gen_obj_targets,$(__debug_bin_obj_dir) $(__release_bin_obj_dir),,)
  __cxx_targets+=bin
  CLEANFILES+=$(DEBUGBINOUT) $(RELEASEBINOUT) $(__debug_bin_obj_dir) $(__release_bin_obj_dir)
endif

#==============================================================================
ifneq (,$(filter test,$(WHAT)))
  TESTNAME?=test_$(NAME)
  __test_source_dir=$(GENSOURCEDIR)/$(TESTNAME)
  __test_source=$(__test_source_dir)/$(TESTNAME).cxx
  TESTFILES=$(wildcard test_*.h)
  DEBUGTESTOUT=$(TESTDIR)/$(TESTNAME)$(SUFDEBUG)$(SUFBIN)
  RELEASETESTOUT=$(TESTDIR)/$(TESTNAME)$(SUFBIN)
  __test_source_file=$(notdir $(__test_source))
  __debug_test_object_dir:=$(call __obj_dir,test,debug)
  __release_test_object_dir:=$(call __obj_dir,test,debug)
  __debug_test_object=$(__test_source_file:%.cxx=$(__debug_test_object_dir)/%$(SUFOBJ))
  __release_test_object=$(__test_source_file:%.cxx=$(__release_test_object_dir)/%$(SUFOBJ))
  DEBUGTESTOBJECTS+=$(if $(filter lib,$(WHAT)),$(DEBUGLIBOBJECTS),$(DEBUGSHROBJECTS))
  DEBUGTESTOBJECTS+=$(__debug_test_object)
  RELEASETESTOBJECTS+=$(if $(filter lib,$(WHAT)),$(RELEASELIBOBJECTS),$(RELEASESHROBJECTS))
  RELEASETESTOBJECTS+=$(__release_test_object)
  __cxx_targets+=maketest
  CLEANFILES+=$(__test_source) $(DEBUGTESTOUT) $(RELEASETESTOUT) $(call __obj_dir,test,debug) $(call __obj_dir,test,release)
endif

#==============================================================================
ifneq (,$(filter lib,$(__cxx_targets)))
lib: $(if $(DEBUG),$(DEBUGLIBOUT),) $(if $(RELEASE),$(RELEASELIBOUT),)

$(DEBUGLIBOUT): $(DEBUGLIBOBJECTS)
	$(MKDIR) $(dir $@)
	$(AR) $(ARFLAGS) $(AROUT)$@ $^ $(LDLIBS)

$(RELEASELIBOUT): $(RELEASELIBOBJECTS)
	$(MKDIR) $(dir $@)
	$(AR) $(ARFLAGS) $(AROUT)$@ $^ $(LDLIBS)
endif

#==============================================================================
ifneq (,$(filter shr,$(__cxx_targets)))
shr: $(if $(DEBUG),$(DEBUGSHROUT),) $(if $(RELEASE),$(RELEASESHROUT),)
$(DEBUGSHROUT): $(DEBUGSHROBJECTS)
	$(MKDIR) $(dir $@)
# TODO: Probably varies based on platform
$(RELEASESHROUT): $(RELEASESHROBJECTS)
	$(MKDIR) $(dir $@)
# TODO: Probably varies based on platform
endif

#==============================================================================
ifneq (,$(filter bin,$(__cxx_targets)))
bin: $(if $(DEBUG),$(DEBUGBINOUT),) $(if $(RELEASE),$(RELEASEBINOUT),)
$(DEBUGBINOUT): $(DEBUGBINOBJECTS)
	$(MKDIR) $(dir $@)
	$(LD) $(LDOUT)$@ $(LDFLAGS) $^ $(LDLIBS)
$(RELEASEBINOUT): $(RELEASEBINOBJECTS)
	$(MKDIR) $(dir $@)
	$(LD) $(LDOUT)$@ $(LDFLAGS) $^ $(LDLIBS)
endif

#==============================================================================
ifneq (,$(filter maketest,$(__cxx_targets)))
.PHONY: maketest

maketest:: $(DEBUGTESTOUT) $(RELEASETESTOUT)

test:: maketest
	@echo "### Running unit tests"
	$(DEBUGTESTOUT)
	$(RELEASETESTOUT)

$(__test_source): $(TESTFILES)
	$(MKDIR) $(dir $@)
	$(CXXTESTGEN) --error-printer -o $@ $^

$(DEBUGTESTOUT): $(DEBUGTESTOBJECTS)
	$(info ### Linking $(notdir $@))
	$(MKDIR) $(dir $@)
	$(LD) $(LDOUT)$@ $(LDFLAGS) $^ $(LDLIBS)

$(RELEASETESTOUT): $(RELEASETESTOBJECTS)
	$(info ### Linking $(notdir $@))
	$(MKDIR) $(dir $@)
	$(LD) $(LDOUT)$@ $(LDFLAGS) $^ $(LDLIBS)

endif

#==============================================================================
default:: $(__cxx_targets)

#==============================================================================
# Test objects
$(__debug_test_object_dir)/%$(SUFOBJ) : $(__test_source_dir)/%.cxx
	$(call __cxx_command,$@,$<,$(TESTCPPFLAGS),$(TESTCXXFLAGS))

$(__release_test_object_dir)/%$(SUFOBJ) : $(__test_source_dir)/%.cxx
	$(call __cxx_command,$@,$<,$(TESTCPPFLAGS),$(TESTCXXFLAGS))
