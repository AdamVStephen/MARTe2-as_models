/**
 * @file LorenzAttractor.cpp
 * @brief Source file for class LorenzAttractor
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
 * the class LorenzAttractor(public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 *
 * The Lorenz system is a classic demonstration of chaotic solution structure in
 * a simple set of coupled non-linear ODEs.
 *
 * For some interesting parameter values and initial conditions, see for example
 * http://web.math.ucsb.edu/~jhateley/paper/lorenz.pdf
 *
 * For MARTe2 it makes a nice demonstration of rendering time series visualisations
 * of the exported data over HTTP, and of using a message interface to reset the
 * integration and modify the main equation parameters.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "AdvancedErrorManagement.h"
#include "CLASSMETHODREGISTER.h"
#include "RegisteredMethodsMessageFilter.h"
#include "LorenzAttractor.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

namespace MARTe {

  LorenzAttractor::LorenzAttractor() :
    GAM(), MessageI() {
    
    Rho = 28.0;
    Sigma = 10.0;
    Beta = 8.0/3.0;

    model_timestep = 0.001;
    steps = 0;
    x0 = y0 = z0 = x1 = y1 = z1 = dx = dy = dz = 0.0;

 
    for(int i = 0; i < 3; i++) {
      inputSignal[i] = NULL_PTR(MARTe::float32 *);
    }
    for(int i = 0; i < 6; i++) {
      outputSignal[i] = NULL_PTR(MARTe::float32 *);
    }

  }
  
  LorenzAttractor::~LorenzAttractor() {
    
  }

  bool LorenzAttractor::Initialise(MARTe::StructuredDataI & data) {
    using namespace MARTe;
    bool ok = GAM::Initialise(data);
    if (!ok) {
      REPORT_ERROR(ErrorManagement::ParametersError, "Could not Initialise the GAM");
    }

    // Rho
    
    if (ok) {
      ok = data.Read("Rho", Rho);
      if (!ok) {
	REPORT_ERROR(ErrorManagement::ParametersError, "The parameter Rho shall be left as default %f", Rho);
      }
    }
    
    if (ok) {
      REPORT_ERROR(ErrorManagement::Information, "Parameter Rho set to %f", Rho);
    }

    // Sigma
    
    if (ok) {
      ok = data.Read("Sigma", Sigma);
      if (!ok) {
	REPORT_ERROR(ErrorManagement::ParametersError, "The parameter Sigma shall be left as default %f", Sigma);
      }
    }
    
    if (ok) {
      REPORT_ERROR(ErrorManagement::Information, "Parameter Sigma set to %f", Rho);
    }

    // Beta
    
    if (ok) {
      ok = data.Read("Beta", Beta);
      if (!ok) {
	REPORT_ERROR(ErrorManagement::ParametersError, "The parameter Beta shall be left as default %f", Beta);
      }
    }
    
    if (ok) {
      REPORT_ERROR(ErrorManagement::Information, "Parameter Beta set to %f", Beta);
    }

    return ok;
  }
  
  /**
   * Version 1 : work with explicit array of x,y,z
   */
  
#define LORENZ_ATTRACTOR_N_OF_INPUTSIGNALS 3u
#define LORENZ_ATTRACTOR_N_OF_OUTPUTSIGNALS 6u

  bool LorenzAttractor::Setup() {

    // --------------------------------------------------------------------------------------
    // Input Signals
    // --------------------------------------------------------------------------------------
    
    bool ok = (GetNumberOfInputSignals() == LORENZ_ATTRACTOR_N_OF_INPUTSIGNALS);
    
    if (!ok) {
      REPORT_ERROR(ErrorManagement::InitialisationError, "GetNumberOfInputSignals() != 3u");
    }

    if (ok) {
      for(uint i = 0; i < LORENZ_ATTRACTOR_N_OF_INPUTSIGNALS; i++) {

	// CHECK Type
	
	TypeDescriptor inputSignalType = GetSignalType(InputSignals, i);
	ok = (inputSignalType == Float32Bit);

	if (!ok) {
	  const char8 * const inputSignalTypeStr = TypeDescriptor::GetTypeNameFromTypeDescriptor(inputSignalType);
	  REPORT_ERROR(ErrorManagement::ParametersError,
		       "The type of the input signals shall be float32. inputSignalType[%d] = %s",
		       i, inputSignalTypeStr);
	}

	// CHECK Samples
	
	uint32 numberOfInputSamples = 0u;

	ok = GetSignalNumberOfSamples(InputSignals, i, numberOfInputSamples);
	if (ok) {
	  ok = (numberOfInputSamples == 1u);
	}
	if (!ok) {
	  REPORT_ERROR(ErrorManagement::ParametersError,
		       "The number of input signals samples shall be equal to 1. numberOfInputSamples[%d] = %d",
		       i, numberOfInputSamples);
		      
	}

	// CHECK Elements

	if (ok) {
	  uint32 numberOfInputElements = 0u;
	  ok = GetSignalNumberOfElements(InputSignals, i, numberOfInputElements);
	  if (ok) {
	    ok = (numberOfInputElements == 1u);
	  }
	  if (!ok) {
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "The number of input signals elements shall be equal to 1. numberOfInputElements[%d] = %d",
			 i, numberOfInputElements);
	  }
	  
	}

	if (ok) {
	  inputSignal[i] = reinterpret_cast<float32 *>(GetInputSignalMemory(i));
	}
	
      }

      	// Parse Default if provided for input signals
      
      if (ok) {
	ok = MoveToSignalIndex(InputSignals, 0u);
	if (ok) {
	  ok = configuredDatabase.Read("Default", x0);
	  if (!ok) {
	    *inputSignal[0] = 1.0;
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "No initial condition provided for X, setting to %f", *inputSignal[0]);

	    ok = true;
	  }
	}
	ok = MoveToSignalIndex(InputSignals, 1u);
	if (ok) {
	  ok = configuredDatabase.Read("Default", y0);
	  if (!ok) {
	    *inputSignal[1] = 2.0;
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "No initial condition provided for Y, setting to %f", *inputSignal[1]);
		    
	    ok = true;
	  }
	}
	ok = MoveToSignalIndex(InputSignals, 2u);
	if (ok) {
	  ok = configuredDatabase.Read("Default", z0);
	  if (!ok) {
	    *inputSignal[2] = -4.0;
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "No initial condition provided for Z, setting to %f", *inputSignal[2]);
	    
	    ok = true;
	  }
	}
      }

      
      // --------------------------------------------------------------------------------------
      // Output Signals
      // --------------------------------------------------------------------------------------
    
      ok = (GetNumberOfOutputSignals() == LORENZ_ATTRACTOR_N_OF_OUTPUTSIGNALS);
    
      if (!ok) {
	REPORT_ERROR(ErrorManagement::InitialisationError, "GetNumberOfOutputSignals() != 3u");
      }

      if (ok) {
	for(uint i = 0; i < LORENZ_ATTRACTOR_N_OF_OUTPUTSIGNALS; i++) {

	  // CHECK Type
	
	  TypeDescriptor outputSignalType = GetSignalType(OutputSignals, i);
	  ok = (outputSignalType == Float32Bit);

	  if (!ok) {
	    const char8 * const outputSignalTypeStr = TypeDescriptor::GetTypeNameFromTypeDescriptor(outputSignalType);
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "The type of the output signals shall be float32. outputSignalType[%d] = %s",
			 i, outputSignalTypeStr);
	  }

	  // CHECK Samples
	
	  uint32 numberOfOutputSamples = 0u;

	  ok = GetSignalNumberOfSamples(OutputSignals, i, numberOfOutputSamples);
	  if (ok) {
	    ok = (numberOfOutputSamples == 1u);
	  }
	  if (!ok) {
	    REPORT_ERROR(ErrorManagement::ParametersError,
			 "The number of output signals samples shall be equal to 1. numberOfOutputSamples[%d] = %d",
			 i, numberOfOutputSamples);
		      
	  }

	  // CHECK Elements

	  if (ok) {
	    uint32 numberOfOutputElements = 0u;
	    ok = GetSignalNumberOfElements(OutputSignals, i, numberOfOutputElements);
	    if (ok) {
	      ok = (numberOfOutputElements == 1u);
	    }
	    if (!ok) {
	      REPORT_ERROR(ErrorManagement::ParametersError,
			   "The number of output signals elements shall be equal to 1. numberOfOutputElements[%d] = %d",
			   i, numberOfOutputElements);
	    }
	  
	  }

	  if (ok) {
	    outputSignal[i] = reinterpret_cast<float32 *>(GetOutputSignalMemory(i));
	  }
	
	}
      }
    }

    REPORT_ERROR(ErrorManagement::Information,
		 "\nInputs 0x%p 0x%p 0x%p\nOutputs 0x%p 0x%p 0x%p",
		 inputSignal[0], inputSignal[1], inputSignal[2],
		 outputSignal[0], outputSignal[1], outputSignal[2]);
		 

    // Install message filter
    ReferenceT<RegisteredMethodsMessageFilter> registeredMethodsMessageFilter("RegisteredMethodsMessageFilter");

    if (ok) {
      ok = registeredMethodsMessageFilter.IsValid();
    }

    if (ok) {
      registeredMethodsMessageFilter->SetDestination(this);
      ok = InstallMessageFilter(registeredMethodsMessageFilter);
    }

    return ok;

  }

  bool LorenzAttractor::Execute() {

    //float32 dx,dy,dz;
    //float32 x0,y0,z0;
    //float32 x1,y1,z1;

    steps += 1;
    model_time = model_timestep*steps;
  
    x0 = *inputSignal[0u];
    y0 = *inputSignal[1u];
    z0 = *inputSignal[2u];

    REPORT_ERROR(ErrorManagement::Information, "Inputs %f %f %f", x0, y0, z0);
    REPORT_ERROR(ErrorManagement::Information, "PRE Inputs %f %f %f", *inputSignal[0], *inputSignal[1], *inputSignal[2]);

    if (steps == 5) {
      x0 = 0.2;
      y0 = 0.2;
      z0 = 0.2;
      REPORT_ERROR(ErrorManagement::Information, "Reset IC to 0.2");
    }

    dx = Sigma * (y0 - x0);
    dy = x0 * (Rho - z0) - y0;
    dz = x0 * y0 - Beta * z0;

    x1 = x0 + (dx * model_timestep);
    y1 = y0 + (dy * model_timestep);
    z1 = z0 + (dz * model_timestep);

    *outputSignal[0u] = x1;
    *outputSignal[1u] = y1;
    *outputSignal[2u] = z1;
    *outputSignal[3u] = dx;
    *outputSignal[4u] = dy;
    *outputSignal[5u] = dz;

    REPORT_ERROR(ErrorManagement::Information,
		 "\nInputs 0x%p 0x%p 0x%p\nOutputs 0x%p 0x%p 0x%p",
		 inputSignal[0], inputSignal[1], inputSignal[2],
		 outputSignal[0], outputSignal[1], outputSignal[2]);


    REPORT_ERROR(ErrorManagement::Information, "POST Inputs %f %f %f", *inputSignal[0], *inputSignal[1], *inputSignal[2]);
    
    return true;
  }

  bool LorenzAttractor::ExportData(MARTe::StructuredDataI & data) {
    using namespace MARTe;
    bool ok = GAM::ExportData(data);
    if (ok) {
      ok = data.CreateRelative("Parameters");
    }
    if (ok) {
      ok = data.Write("Rho", Rho);
    }
    if (ok) {
      ok = data.Write("Sigma", Sigma);
    }
    if (ok) {
      ok = data.Write("Beta", Beta);
    }
    if (ok) {
      ok = data.MoveToAncestor(1u);
    }
    if (ok) {
      ok = data.CreateRelative("Position");
    }
    if (ok) {
      ok = data.Write("x", x0);
    }
    if (ok) {
      ok = data.Write("y", y0);
    }
    if (ok) {
      ok = data.Write("z", z0);
    }
    if (ok) {
      ok = data.MoveToAncestor(1u);
    }
    if (ok) {
      ok = data.CreateRelative("Velocity");
    }
    if (ok) {
      ok = data.Write("dx", dx);
    }
    if (ok) {
      ok = data.Write("dy", dy);
    }
    if (ok) {
      ok = data.Write("dz", dz);
    }
    if (ok) {
      ok = data.MoveToAncestor(1u);
    }
    return ok;
  }

  ErrorManagement::ErrorType LorenzAttractor::SetOutput(ReferenceContainer& message) {

    ErrorManagement::ErrorType ret = ErrorManagement::NoError;

    // Assume one ReferenceT<StructuredDataI> contained in the message

    bool ok = (message.Size() == 1u);
    ReferenceT<StructuredDataI> data = message.Get(0u);

    if (ok) {
      ok = data.IsValid();
    }

    if (!ok) {
      ret = ErrorManagement::ParametersError;
      REPORT_ERROR(ret, "Message does not contain a ReferenceT<StructuredDataI>");
    }

    StreamString signalName;
    uint32 signalIndex = 0u;

    if (ok) {
      if (data->Read("SignalName", signalName)) {
	ok = GetSignalIndex(OutputSignals, signalIndex, signalName.Buffer());
      }
      else {
	ok = data->Read("SignalIndex", signalIndex);
      }
    }

    if (ok) {
      ok = (signalIndex < GetNumberOfOutputSignals());
    }

    if (!ok) {
      ret = ErrorManagement::ParametersError;
      REPORT_ERROR(ret, "No valid signal name or index provided");
    }

    TypeDescriptor signalType = InvalidType;

    if (ok) {
      signalType = GetSignalType(OutputSignals, signalIndex);
      ok = (signalType != InvalidType);
    }

    if (ok) {

      // Signal index and type are tested and valid ... go ahead with AnyType instantiation

      // Use the default value type to query the signal properties (dimensions, ...)
      /*lint -e{534}  [MISRA C++ Rule 0-1-7], [MISRA C++ Rule 0-3-2]. Justification: SignalIndex is tested valid prio to this part of the code.*/
      MoveToSignalIndex(OutputSignals, signalIndex);
      AnyType signalDefType = configuredDatabase.GetType("Default");
      AnyType signalNewValue(signalType, 0u, GetOutputSignalMemory(signalIndex));

      uint8 signalNumberOfDimensions = signalDefType.GetNumberOfDimensions();
      signalNewValue.SetNumberOfDimensions(signalNumberOfDimensions);

      uint32 dimensionIndex;

      for (dimensionIndex = 0u; dimensionIndex < signalNumberOfDimensions; dimensionIndex++) {
	uint32 dimensionNumberOfElements = signalDefType.GetNumberOfElements(static_cast<uint32>(dimensionIndex));
	signalNewValue.SetNumberOfElements(static_cast<uint32>(dimensionIndex), dimensionNumberOfElements);
      }

      if (data->Read("SignalValue", signalNewValue)) {
	REPORT_ERROR(ErrorManagement::Information, "Signal '%!' new value '%!'", signalName.Buffer(), signalNewValue);
      }
      else {
	ret = ErrorManagement::ParametersError;
	REPORT_ERROR(ret, "Failed to read and apply new signal value");
      }

    }

    return ret;
  }

  CLASS_REGISTER(LorenzAttractor, "1.0")

  /*lint -e{1023} Justification: Macro provided by the Core.*/
  //CLASS_METHOD_REGISTER(LorenzAttractor, SetOutput)

} /* namespace MARTe */

