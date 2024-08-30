#pragma once

#include "uiModule.h"
#include "uiResource.h"
#include "uiUtilities.h"
#include "uiTexture.h"
#include "uiAnimation.h"

class CODEC
{
  
};



class ResourceManager : public Module<ResourceManager>
{
  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> CreateResource(const String& assetName)
  {
    String path = Utils::Format("%s/resources/%s", 
                                FileSystem::CurrentPath().string().c_str(), 
                                assetName.c_str());
    if (m_resources.find(Hash<String>()(path)) != m_resources.end()) { return nullptr; }
    T::GetType();
    eRESOURCETYPE type = T::GetType();
    SharedPtr<Resource> newResource;
    if (eRESOURCETYPE::SOUND == type)
    {

    }
    else if (eRESOURCETYPE::TEXTURE == type)
    {
      newResource = MakeSharedObject<Texture>();
    }
    else if (eRESOURCETYPE::ANIMATION == type)
    {
      newResource = MakeSharedObject<Animation>();
    }
    m_resources.insert(Utils::MakePair(Hash<String>()(path), newResource));

  }

  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> LoadResource(const String& path)
  {
    eRESOURCETYPE type = T::GetType();
    SharedPtr newResource = nullptr;
    if (eRESOURCETYPE::SOUND == type)
    {

    }
    else if (eRESOURCETYPE::TEXTURE == type)
    {
      newResource = MakeSharedObject<Texture>();
      newResource->loadFromFile(path);
    }
    else if (eRESOURCETYPE::ANIMATION == type)
    {
      newResource = MakeSharedObject<Animation>();
    }

    if (newResource)
    {
      m_resources.insert(Utils::MakePair(Hash<String>()(path), newResource));
    }

    // if (newResource != nullptr)
    // {
    //   // m_resources.insert(Utils::MakePair(1, newResource));
    // }

    return newResource;
  }

  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> GetResource()
  {

  }


  Map<std::size_t, SharedPtr<Resource>> m_resources;
};

