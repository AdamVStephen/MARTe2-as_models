#ifndef CONFIGURATIONDATABASEUTILS_H_
#define CONFIGURATIONDATABASEUTILS_H_

#include "AnyObject.h"
#include "ConfigurationDatabase.h"

namespace MARTe {

  class DLL_API ConfigurationDatabaseViewer : public Object {
  public:
    CLASS_REGISTER_DECLARATION();
    
    ConfigurationDatabaseViewer();
    
    virtual ~ConfigurationDatabaseViewer();

    virtual uint32 GetNumberOfChildren();
  private:
    ReferenceT<ConfigurationDatabaseNode> rootNode;
    ReferenceT<ConfigurationDatabaseNode> currentNode;
  };
  
}
#endif
