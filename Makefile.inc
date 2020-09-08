###################################################################
# LICENSE
#
# Copyright 2020 United Kingdom Atomic Energy Authority
#
# Licensing terms of this software have yet to be approved.
###################################################################


SPB = Source/As_models/GAMs.x
SPB += Test/As_models/GAMs.x
SPB += Test/GTest.x

MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults

ROOT_DIR=.
include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

all: $(OBJS) $(SUBPROJ) check-env
	echo  $(OBJS)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)

check-env:
ifndef MARTe2_DIR
    $(error MARTe2_DIR is undefined)
endif

