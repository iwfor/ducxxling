TOP=.
SUBDIRS=src
include $(TOP)/nospb/mk/rules.mk

cscope:
	cscope -bUv src/*.cxx include/ducxxling/*.h

ctags:
	ctags --totals src/*.cxx include/ducxxling/*.h
