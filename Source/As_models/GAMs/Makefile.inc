###################################################################
# LICENSE
#
# Copyright 2020 United Kingdom Atomic Energy Authority
#
# Licensing terms of this software have yet to be approved.
###################################################################

OBJSX= 

SPB = LorenzAttractor.x

PACKAGE=As_models
ROOT_DIR=../../..
MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

LIBRARIES_STATIC = $(BUILD_DIR)/LorenzAttractor/LorenzAttractor$(LIBEXT)

all: $(OBJS)  $(SUBPROJ)  \
    $(BUILD_DIR)/GAMs$(LIBEXT) \
    $(BUILD_DIR)/GAMs$(DLLEXT)
	echo  $(OBJS)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
