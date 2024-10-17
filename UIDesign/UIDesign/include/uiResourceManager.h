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
    String realName = Utils::Format("%s_%s", T::StaticType()._to_string(), assetName.c_str());

    // String path = Utils::Format("%s/resources/%s", 
    //                             FileSystem::CurrentPath().string().c_str(), 
    //                             realName.c_str());
    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    { 
      return  REINTERPRETPOINTER(T, m_resources.at(Hash<String>()(realName)));
    }
    T::StaticType();
    // eRESOURCETYPE type = T::StaticType();
    SharedPtr<T> newResource = MakeSharedObject<T>();
    newResource->m_resName = assetName;
    // newResource->Initialize();
    m_resources.insert(Utils::MakePair(Hash<String>()(realName), newResource));
    return newResource;
  }

  template<typename T, typename = std::enable_if_t<std::is_base_of<Resource, T>::value>>
  SharedPtr<T> LoadResource(const String& path)
  {
    Path p = path;
    
    String realName = Utils::Format("%s_%s", T::StaticType()._to_string(), p.stem().string().c_str());

    

    eRESOURCETYPE type = T::StaticType();
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
    String realName = Utils::Format("%s_%s", T::StaticType()._to_string(), path.c_str());
    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    {
      return  REINTERPRETPOINTER(T, m_resources.at(Hash<String>()(realName)));
    }
    return {};
  }

  SharedPtr<Resource> GetResourceOf(const String& path, const eRESOURCETYPE& type)
  {
    String realName = Utils::Format("%s_%s", type._to_string(), path.c_str());
    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    {
      return  m_resources.at(Hash<String>()(realName));
    }
    return {};
  }

  JSONDocument Serialize()
  {
    JSONDocument document;
    document.SetArray();
    JSONDocument::AllocatorType& allocator = document.GetAllocator();

    for (const auto& resource : m_resources)
    {
      JSONValue obj(rapidjson::kObjectType);

      obj.AddMember("id", resource.first, allocator);
      obj.AddMember("name", resource.second->m_resName, allocator);

      eRESOURCETYPE type = resource.second->GetType();
      obj.AddMember("type", type._to_integral(), allocator);
      
      if (eRESOURCETYPE::TEXTURE == type)
      {
        // void* data = reinterpret_cast<void*>(REINTERPRETPOINTER(Texture, resource.second)->copyToImage().getPixelsPtr());
        sf::Image img = REINTERPRETPOINTER(Texture, resource.second)->copyToImage();
        const uint8* pixelData = img.getPixelsPtr();
        Vector2u imageSize = img.getSize();
        SizeT dataSize = imageSize.x * imageSize.y * 4;
        Vector<uint8> data(pixelData, pixelData + dataSize);
        obj.AddMember("width", imageSize.x, allocator);
        obj.AddMember("height", imageSize.y, allocator);
        JSONValue jsonArray(rapidjson::kArrayType);
        
        for (int i = 0; i < data.size(); ++i)
        {
          jsonArray.PushBack(data[i], allocator);
        }

        obj.AddMember("data", jsonArray, allocator);
      }
      else if (eRESOURCETYPE::SOUND == type)
      {
        const int16* audioData = REINTERPRETPOINTER(AudioClip, resource.second)->getSamples();

      }
      else if (eRESOURCETYPE::MUSIC == type)
      {

      }
      else if (eRESOURCETYPE::ANIMATION == type)
      {

      }
      else if (eRESOURCETYPE::ATLAS == type)
      {

      }
      else if (eRESOURCETYPE::FONT == type)
      {

      }
      document.PushBack(obj, allocator);
    }
    return document;
  }

  Map<SizeT, SharedPtr<Resource>> m_resources;

  Vector<Callback<void, bool, String>> m_resourceLoadedCallbacks;

};

