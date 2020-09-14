/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "AnyObject.h"
#include "ErrorType.h"
#include "ConfigurationDatabase.h"
#include "StreamString.h"
#include "ConfigurationDatabaseUtils.h"
#include "ConfigurationDatabaseUtilsTest.h"

//#include "IntrospectionTestHelper.h"
//#include "Matrix.h"
//#include "ObjectRegistryDatabase.h"
//#include "StandardParser.h"
//#include "Vector.h"

using namespace MARTe;

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

bool ConfigurationDatabaseUtilsTest::TestDefaultConstructor() {
  ConfigurationDatabase cdb;
  bool ok = cdb.Lock(TTInfiniteWait);
  cdb.Unlock();
  return ok;
}

bool ConfigurationDatabaseUtilsTest::TestInlineConfiguration() {
  bool ok = true;
  ConfigurationDatabase cdb;
  StreamString configString = "+LorenzModel = {\n"
"             Class = LorenzAttractor \n"
"             Rho = 1.0 \n"
" 	    Sigma = 2.0 \n"
" 	    Beta = 3.0 \n"
"             InputSignals = { \n"
"                 X0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
" 		    InitialCondition = 0.1 \n"
"                 } \n"
"                 Y0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
" 		    InitialCondition = 0.1	 \n"
"                 } \n"
"                 Z0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
" 		    InitialCondition = 0.1	 \n"
"                 } \n"
"             }  \n"
"             OutputSignals = { \n"
" 	    	X0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"                 Y0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"                 Z0 = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"                 DX = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"                 DY = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"                 DZ = { \n"
"                     DataSource = DDB1 \n"
"                     Type = float32 \n"
"                 } \n"
"             } \n"
"        }";

  return ok;
}
