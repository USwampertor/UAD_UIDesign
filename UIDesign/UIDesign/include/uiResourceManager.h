#pragma once

#include "uiModule.h"
#include "uiResource.h"
#include "uiUtilities.h"


class ResourceManager : public Module<ResourceManager>
{



  Map<uint32, SharedPtr<Resource>> m_resources;
};

