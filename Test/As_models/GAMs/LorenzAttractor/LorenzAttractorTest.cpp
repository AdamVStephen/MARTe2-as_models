/**
 * @file LorenzAttractorTest.cpp
 * @brief Source file for class LorenzAttractorTest
 * @date 2020-09-08T14:54:57.061624
 * @author Adam V Stephen
 */
/*
 * @copyright United Kingdom Atomic Energy Authority
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.
 */

/*
 * @details This source file contains the definition of all the methods for
 * the class ConstantGAM (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "AdvancedErrorManagement.h"
#include "ConfigurationDatabase.h"
#include "ErrorInformation.h"
#include "ErrorManagement.h"
#include "FastMath.h"
#include "GAM.h"
#include "GlobalObjectsDatabase.h"
#include "ObjectRegistryDatabase.h"
#include "RealTimeApplication.h"
#include "StandardParser.h"
#include "LorenzAttractor.h"
#include "LorenzAttractorTest.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

class LorenzAttractorHelper: public MARTe::LorenzAttractor {
public:
    CLASS_REGISTER_DECLARATION()

    LorenzAttractorHelper() : MARTe::LorenzAttractor() {};
    virtual ~LorenzAttractorHelper() {};
    template <typename Type> bool GetOutput (MARTe::uint32 index, Type& value, MARTe::uint32 offset = 0u);
};

template<typename Type> bool LorenzAttractorHelper::GetOutput(MARTe::uint32 signalIndex, Type& value, MARTe::uint32 index) {

    using namespace MARTe;

    bool ret = (GetNumberOfOutputSignals() > signalIndex);

    if (!ret) {
        REPORT_ERROR_PARAMETERS(ErrorManagement::InitialisationError, "GetNumberOfOutputSignals() <= %u", signalIndex);
    }

    StreamString signalName;

    if (ret) {
        ret = GetSignalName(OutputSignals, signalIndex, signalName);
    }

    TypeDescriptor signalType = InvalidType;

    if (ret) {
        signalType = GetSignalType(OutputSignals, signalIndex);
        ret = (signalType != InvalidType);
    }

    /* Should test the signal type */

    if (ret) {
        Type* ref = static_cast<Type*>(GetOutputSignalMemory(signalIndex));
        value = ref[index];
        //ret = MemoryOperationsHelper::Copy(&value, static_cast<void*>(static_cast<Type*>(GetOutputSignalMemory(signalIndex)) + offset), sizeof(Type));
    }

    if (ret) {
        REPORT_ERROR_PARAMETERS(ErrorManagement::Information, "LorenzAttractorHelper::GetOutput - '%s' at offset '%u' '%!'", signalName.Buffer(), index, value);
    }

    return ret;
}


CLASS_REGISTER(LorenzAttractorHelper, "1.0")

/**
 * Starts a MARTe application that uses this driver instance.
 */

namespace LorenzAttractorTestHelper {

bool ConfigureApplication(const MARTe::char8 * const config) {

    using namespace MARTe;

    ConfigurationDatabase cdb;
    StreamString configStream = config;
    StreamString err;
    configStream.Seek(0);
    StandardParser parser(configStream, cdb, &err);

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();

    bool ok = parser.Parse();

    if (ok) {
        god->Purge();
        ok = god->Initialise(cdb);
    }
    else {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "StandardParser::Parse failed");
    }

    ReferenceT<RealTimeApplication> application;

    if (ok) {
        application = god->Find("Test");
        ok = application.IsValid();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->ConfigureApplication();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::ConfigureApplication failed");
    }

    return ok;

}

static inline bool StartApplication(const MARTe::char8 * const state = "Running") {

    using namespace MARTe;

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");

    bool ok = application.IsValid();

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->PrepareNextState(state);
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::PrepareNextState failed");
    }
    else {
        ok = application->StartNextStateExecution();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::StartNextStateExecution failed");
    }
    return ok;

}

static inline bool StopApplication() {

    using namespace MARTe;

    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");

    bool ok = application.IsValid();

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::IsValid failed");
    }
    else {
        ok = application->StopCurrentStateExecution();
    }

    if (!ok) {
        REPORT_ERROR_STATIC(ErrorManagement::InternalSetupError, "RealTimeApplication::StopCurrentStateExecution failed");
    }

    god->Purge();

    return ok;

}

} /* namespace LorenzAttractorTestHelper */

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

LorenzAttractorTest::LorenzAttractorTest() {
}

LorenzAttractorTest::~LorenzAttractorTest() {
}

bool LorenzAttractorTest::TestConstructor() {
    using namespace MARTe;
    LorenzAttractor gam;

    bool ok = (gam.GetNumberOfInputSignals() == 0u) && (gam.GetNumberOfOutputSignals() == 0u);

    return ok;
}

bool LorenzAttractorTest::TestExecute() {
    using namespace MARTe;
    LorenzAttractor gam;

    bool ok = gam.Execute();

    return ok;
}

bool LorenzAttractorTest::TestSetup() {
    const MARTe::char8 * const config = ""
      "$Test = {"
      "    Class = RealTimeApplication"
      "    +Functions = {"
      "        Class = ReferenceContainer"
      "        +LorenzAttractor = {"
      "            Class = LorenzAttractor"
      "            Gain = 2"
      "            InputSignals = {"
      "                Signal1 = {"
      "                    DataSource = DDB"
      "                    Type = float64"
      "                }"
      "            }"
      "            OutputSignals = {"
      "                Signal1 = {"
      "                    DataSource = DDB"
      "                    Type = float64"
      "                }"
      "            }"
      "        }"
      "    }"
      "    +Data = {"
      "        Class = ReferenceContainer"
      "        DefaultDataSource = DDB"
      "        +DDB = {"
      "            Class = GAMDataSource"
      "        }"
      "        +Timings = {"
      "            Class = TimingDataSource"
      "        }"
      "    }"
      "    +States = {"
      "        Class = ReferenceContainer"
      "        +Running = {"
      "            Class = RealTimeState"
      "            +Threads = {"
      "                Class = ReferenceContainer"
      "                +Thread = {"
      "                    Class = RealTimeThread"
      "                    Functions = { LorenzAttractor }"
      "                }"
      "            }"
      "        }"
      "    }"
      "    +Scheduler = {"
      "        Class = GAMScheduler"
      "        TimingDataSource = Timings"
      "    }"
      "}";
    
    bool ok = LorenzAttractorTestHelper::ConfigureApplication(config);

    using namespace MARTe;
    
    ObjectRegistryDatabase *god = ObjectRegistryDatabase::Instance();
    ReferenceT<RealTimeApplication> application = god->Find("Test");
    ReferenceT<LorenzAttractor> gam = application->Find("Functions.LorenzAttractor");

    if (ok) {
        ok = gam.IsValid();
    }

    return ok;
}

