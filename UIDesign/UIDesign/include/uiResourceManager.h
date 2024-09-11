#pragma once

#include "uiPrerequisites.h"

#include "uiAnimation.h"
#include "uiAtlas.h"
#include "uiJSON.h"
#include "uiModule.h"
#include "uiResource.h"
#include "uiScene.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include <iostream>

class CODEC
{
  
};

class ResourceManager : public Module<ResourceManager>
{
public:
  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> CreateResource(const String& assetName)
  {
    String path = Utils::Format("%s/resources/%s", 
                                FileSystem::CurrentPath().string().c_str(), 
                                assetName.c_str());
    if (m_resources.find(Hash<String>()(path)) != m_resources.end()) 
    { 
      return  REINTERPRETPOINTER(T, m_resources.at(Hash<String>()(path))); 
    }
    T::GetType();
    eRESOURCETYPE type = T::GetType();
    SharedPtr<T> newResource = MakeSharedObject<T>();
    // newResource->Initialize();
    m_resources.insert(Utils::MakePair(Hash<String>()(path), newResource));
    return newResource;
  }

  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> LoadResource(const String& path)
  {
    eRESOURCETYPE type = T::GetType();
    SharedPtr<T> newResource = MakeSharedObject<T>();
    // newResource->Initialize();
    if (eRESOURCETYPE::SOUND == type)
    {

    }
    else if (eRESOURCETYPE::TEXTURE == type)
    {
      REINTERPRETPOINTER(Texture, newResource)->loadFromFile(path);
    }
    else if (eRESOURCETYPE::ANIMATION == type)
    {

    }
    else if (eRESOURCETYPE::ATLAS == type)
    {
      JSONDocument d;
      Path p = path;
      String str = FileSystem::GetAllStringFromFile(p);
      d.Parse(str.c_str());
      std::cout << d.HasMember("texture") << std::endl;
      String texPath = Utils::Format("%s/%s",p.parent_path().string().c_str(), d["texture"].GetString());
      const JSONValue& positions = d["positions"];
      for (int i = 0; i < positions.Size(); ++i)
      {
        String resourceNewName = Utils::Format("%s_atlas_%d", p.filename(), i);
        SharedPtr<Texture> t = CreateResource<Texture>(resourceNewName);
        const JSONValue& size = positions[i][0];
        const JSONValue& pos = positions[i][1];
        t->loadFromFile(texPath, 
                        sf::IntRect(pos[0].GetInt(), pos[1].GetInt(), size[0].GetInt(), size[1].GetInt()));
        REINTERPRETPOINTER(Atlas, newResource)->m_atlas.push_back(t);
      }
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
  SharedPtr<T> GetResource(const String& path)
  {
    return REINTERPRETPOINTER(T, m_resources[0]);
  }

  Map<std::size_t, SharedPtr<Resource>> m_resources;
};

