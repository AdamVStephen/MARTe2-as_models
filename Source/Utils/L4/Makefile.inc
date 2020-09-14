OBJSX = ConfigurationDatabaseUtils.x

PACKAGE=Utils
ROOT_DIR=../../../
MAKEDEFAULTDIR=$(MARTe2_DIR)/MakeDefaults
include $(MAKEDEFAULTDIR)/MakeStdLibDefs.$(TARGET)

INCLUDES += -I.
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L0Types
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L1Portability
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L2Objects
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L3Streams
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L4Messages
INCLUDES += -I$(MARTe2_DIR)/Source/Core/BareMetal/L4Configuration

all : $(OBJS) $(SUBPROJ) \
    $(BUILD_DIR)/ConfigurationDatabaseUtils$(LIBEXT) \
    $(BUILD_DIR)/ConfigurationDatabaseUtils$(DLLEXT) \
        $(BUILD_DIR)/ConfigurationDatabaseUtils.def
	echo $(OBJS)

include depends.$(TARGET)

include $(MAKEDEFAULTDIR)/MakeStdLibRules.$(TARGET)
    