#pragma once

#include "uiPrerequisites.h"

#include "uiAnimation.h"
#include "uiAudioClip.h"
#include "uiAtlas.h"
#include "uiFileSystem.h"
#include "uiJSON.h"
#include "uiModule.h"
#include "uiMusicClip.h"
#include "uiResource.h"
#include "uiScene.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include <iostream>


class ResourceManager : public Module<ResourceManager>
{
public:
  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> CreateResource(const String& assetName)
  {
    String realName = Utils::Format("%s_%s", T::GetType()._to_string(), assetName.c_str());
    // String path = Utils::Format("%s/resources/%s", 
    //                             FileSystem::CurrentPath().string().c_str(), 
    //                             realName.c_str());
    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    { 
      return  REINTERPRETPOINTER(T, m_resources.at(Hash<String>()(realName)));
    }
    T::GetType();
    // eRESOURCETYPE type = T::GetType();
    SharedPtr<T> newResource = MakeSharedObject<T>();
    // newResource->Initialize();
    m_resources.insert(Utils::MakePair(Hash<String>()(realName), newResource));
    return newResource;
  }

  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> LoadResource(const String& path)
  {
    Path p = path;
    
    String realName = Utils::Format("%s_%s", T::GetType()._to_string(), p.stem().string().c_str());

    

    eRESOURCETYPE type = T::GetType();
    SharedPtr<T> newResource = CreateResource<T>(p.stem().string().c_str());
    // newResource->Initialize();
    if (eRESOURCETYPE::SOUND == type)
    {
      REINTERPRETPOINTER(AudioClip, newResource)->loadFromFile(path);
    }
    else if (eRESOURCETYPE::MUSIC == type)
    {
      REINTERPRETPOINTER(MusicClip, newResource)->openFromFile(path);
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
      // std::cout << d.HasMember("texture") << std::endl;
      String texPath = Utils::Format("%s/%s",p.parent_path().string().c_str(), d["texture"].GetString());
      const JSONValue& positions = d["positions"];
      for (uint32 i = 0; i < positions.Size(); ++i)
      {
        // String resourceNewName = Utils::Format("%s_atlas_%d", p.filename(), i);
        String newTextureName = Utils::Format("%s_%d", p.stem().string().c_str(), i);
        SharedPtr<Texture> t = CreateResource<Texture>(newTextureName);
        const JSONValue& size = positions[i][0];
        const JSONValue& pos = positions[i][1];
        t->loadFromFile(texPath, 
                        sf::IntRect(pos[0].GetInt(), pos[1].GetInt(), size[0].GetInt(), size[1].GetInt()));
        REINTERPRETPOINTER(Atlas, newResource)->m_atlas.push_back(t);
      }
    }
    return newResource;
  }



  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> GetResource(const String& path)
  {
    String realName = Utils::Format("%s_%s", T::GetType()._to_string(), path.c_str());
    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    {
      return  REINTERPRETPOINTER(T, m_resources.at(Hash<String>()(realName)));
    }
    return {};
  }

  JSONDocument Serialize()
  {
    JSONDocument document;
    document.SetArray();
    JSONDocument::AllocatorType& allocator = document.GetAllocator();

    for (auto& resource : m_resources)
    {
      JSONValue obj(rapidjson::kObjectType);
      JSONValue data;

      obj.AddMember("id", resource.first, allocator);
      eRESOURCETYPE type = resource.second->GetType();
      // String typeStr = type._to_string();
      obj.AddMember("type",type._to_integral(), allocator);
      
      if (eRESOURCETYPE::ATLAS == type)
      {
        data.SetArray();
        for (int i = 0; i < REINTERPRETPOINTER(Atlas, resource.second)->m_atlas.size(); ++i)
        {
          for (auto& findingTexture : m_resources)
          {
            if (findingTexture.second == REINTERPRETPOINTER(Atlas, resource.second)->m_atlas[i])
            {
              data.PushBack(findingTexture.first, allocator);
              break;
            }
          }
        }
      }

      obj.AddMember("data", data, allocator);

      document.PushBack(obj, allocator);
    }
    return document;
  }

  Map<std::size_t, SharedPtr<Resource>> m_resources;

  Vector<Callback<void, bool, String>> m_resourceLoadedCallbacks;

};

