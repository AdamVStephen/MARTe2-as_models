#define DLL_API

#include "ConfigurationDatabaseUtils.h"

namespace MARTe {

  ConfigurationDatabaseViewer::ConfigurationDatabaseViewer() :
    Object() {
    ReferenceT<ConfigurationDatabaseNode> rootContainer(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    rootNode = rootContainer;
    currentNode = rootNode;
  }
  
  ConfigurationDatabaseViewer::~ConfigurationDatabaseViewer() {}

  uint32 ConfigurationDatabaseViewer::GetNumberOfChildren() {
    uint32 size = 0u;
    if (currentNode.IsValid()) {
      size = currentNode->Size();
    }
    return size;
  }

  
  CLASS_REGISTER(ConfigurationDatabaseViewer, "1.0")
}
