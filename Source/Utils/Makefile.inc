###################################################################
# LICENSE
#
# Copyright 2020 United Kingdom Atomic Energy Authority
#
# Licensing terms of this software have yet to be approved.
###################################################################

OBJSX= 

SPB = L4.x

PACKAGE=.
ROOT_DIR=../..
MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

LIBRARIES_STATIC = $(BUILD_DIR)/L4/ConfigurationDatabaseUtils$(LIBEXT)

all: $(OBJS)  $(SUBPROJ)  \
    $(BUILD_DIR)/Utils$(LIBEXT) \
    $(BUILD_DIR)/Utils$(DLLEXT)
	echo  $(OBJS)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
