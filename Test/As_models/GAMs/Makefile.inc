###################################################################
# LICENSE
#
# Copyright 2020 United Kingdom Atomic Energy Authority
#
# Licensing terms of this software have yet to be approved.
###################################################################

SPB = LorenzAttractor.x

ifdef EFDA_MARTe_DIR
SPB += BaseLib2GAM.x
endif

PACKAGE=As_models
ROOT_DIR=../../..
MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults

include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

LIBRARIES_STATIC += $(BUILD_DIR)/LorenzAttractor/LorenzAttractorTest$(LIBEXT)

ifdef EFDA_MARTe_DIR)
LIBRARIES_STATIC+=$(BUILD_DIR)/BaseLib2GAM/BaseLib2GAMTest$(LIBEXT)
endif

all: $(OBJS) $(SUBPROJ) \
    $(BUILD_DIR)/GAMsTests$(LIBEXT)
	echo  $(OBJS)

include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
