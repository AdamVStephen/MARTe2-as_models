/**
 * @file LorenzAttractor.h
 * @brief Header file for class LorenzAttractor

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
 * @details This header file contains the declaration of the class 
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

// COOKIECUTTER TODO : MANAGE THE IDEMPOTENT GUARD GENERATION

#ifndef AS_MODELS_H_
#define AS_MODELS_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GAM.h"
#include "MessageI.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief GAM which provides constant output signals. 
 * @details This GAM provides constant output signals, the value of which is defined through configuration, and
 * may be asynchronously altered using MARTe messages sent e.g. from a StateMachine.
 *
 * The configuration syntax is (names and signal quantity are only given as an example):
 *
 * <pre>
 * +Constants = {
 *     Class = LorenzAttractor
 *     OutputSignals = {
 *         Signal1 = {
 *             DataSource = "DDB"
 *             Type = uint32
 *             Default = 0
 *         }
 *         Signal2 = {
 *             DataSource = "DDB"
 *             Type = int32
 *             Default = 100
 *         }
 *         Signal3 = {
 *             DataSource = "DDB"
 *             Type = int8
 *             NumberOfDimensions = 1
 *             NumberOfElements = 8
 *             Default = {1 2 3 4 5 6 7 8}
 *         }
 *     }
 * }
 * </pre>
 *
 * The GAM registers a messageable 'SetOutput' method which allows to update signals through messages:
 *
 * <pre>
 * +Message = {
 *     Class = Message
 *     Destination = "Functions.Constants"
 *     Function = "SetOutput"
 *     +Parameters = {
 *         Class = ConfigurationDatabase
 *         SignalName = "Signal1" // The name of the signal to modify, or
 *         SignalIndex = 0 // Alternatively, the index of the signal.
 *         SignalValue = 10
 *     }
 * }
 * </pre>
 */
class LorenzAttractor: public GAM, public MessageI {
public:
    CLASS_REGISTER_DECLARATION()

    /**
     * @brief Constructor. NOOP.
     */
    LorenzAttractor();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~LorenzAttractor();

    /**
     * @brief Initialises the output signal memory with default values provided through configuration.
     * @return true if the pre-conditions are met.
     * @pre
     *   SetConfiguredDatabase() && GetNumberOfInputSignals() == 0 &&
     *   for each signal i: The default value provided corresponds to the expected type and dimensionality.
     */
    virtual bool Setup();

    /**
     * @brief Execute method. NOOP.
     * @return true.
     */
    virtual bool Execute();

    /**
     * @brief SetOutput method.
     * @details The method is registered as a messageable function. It assumes the ReferenceContainer
     * includes a reference to a StructuredDataI instance which contains a valid 'SignalName' attribute, 
     * or alternatively, a valid 'SignalIndex' from which the output signal can be identified. 
     * The 'SignalValue' attribute must match the expected type and dimensionality of the output signal.
     * @return ErrorManagement::NoError if the pre-conditions are met, ErrorManagement::ParametersError
     * otherwise.
     * @pre
     *   'SignalIndex' < GetNumberOfOutputSignals() &&
     *   The 'SignalValue' provided corresponds to the expected type and dimensionality.
     */
    ErrorManagement::ErrorType SetOutput(ReferenceContainer& message);
};

}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /*  AS_MODELS_H_ */

