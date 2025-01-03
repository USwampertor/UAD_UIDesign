#pragma once

#include "uiPrerequisites.h"

#include "uiAnimation.h"
#include "uiAudioClip.h"
#include "uiApp.h"
#include "uiAtlas.h"
#include "uiFileSystem.h"
#include "uiFont.h"
#include "uiIcon.h"
#include "uiJSON.h"
#include "uiLogger.h"
#include "uiModule.h"
#include "uiMusicClip.h"
#include "uiResource.h"
#include "uiShaderFile.h"
#include "uiScene.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include <iostream>


class ResourceManager : public Module<ResourceManager>
{
public:

  virtual void OnStartUp() override
  {
    // We should always have an error texture, error text, error sound, and etc.
    SharedPtr<Texture> missingTexture = CreateResource<Texture>("missing_texture");
    sf::Image missingImage;
    missingImage.create(32, 32, g_missingTex);
    missingTexture->loadFromImage(missingImage);


    // Editor icons and resources
    if (App::Instance().m_parser.HasFlag("editor"))
    {
    
      SharedPtr<Texture> camera_gizmo = ResourceManager::Instance().CreateResource<Texture>("editor_camera");
      sf::Image cameraImage;
      cameraImage.create(32, 32, g_cameraIcon);
      camera_gizmo->loadFromImage(cameraImage);

      SharedPtr<Texture> light_gizmo = ResourceManager::Instance().CreateResource<Texture>("editor_light");
      sf::Image lightImage;
      lightImage.create(32, 32, g_lightIcon);
      light_gizmo->loadFromImage(lightImage);

      SharedPtr<Texture> atlas_icon = ResourceManager::Instance().CreateResource<Texture>("editor_atlas");
      sf::Image atlasImage;
      atlasImage.create(32, 32, g_atlasIcon);
      atlas_icon->loadFromImage(atlasImage);

      SharedPtr<Texture> json_icon = ResourceManager::Instance().CreateResource<Texture>("editor_json");
      sf::Image jsonImage;
      jsonImage.create(32, 32, g_jsonIcon);
      json_icon->loadFromImage(jsonImage);

      // SharedPtr<Texture> json_icon = ResourceManager::Instance().CreateResource<Texture>("editor_json");
      // sf::Image jsonImage;
      // jsonImage.create(32, 32, g_jsonIcon);
      // json_icon->loadFromImage(jsonImage);

    }
  }



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
      REINTERPRETPOINTER(MusicClip, newResource)->m_filePath = path;
      REINTERPRETPOINTER(MusicClip, newResource)->openFromFile(path);
    }
    else if (eRESOURCETYPE::FONT == type)
    {
      REINTERPRETPOINTER(Font, newResource)->m_filePath = path;
      REINTERPRETPOINTER(Font, newResource)->loadFromFile(path);
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
    else if (eRESOURCETYPE::SHADER == type)
    {
      REINTERPRETPOINTER(ShaderFile, newResource)->LoadFromFile(path);
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

  struct QueueFrames
  {
    Vector<String> m_frames;
    SizeT hashID;
    eRESOURCETYPE type = eRESOURCETYPE::NONE;
  };

  void Deserialize(const JSONValue& resources)
  {
    Vector<QueueFrames*> queueResources;
// 
    for (auto& itr : resources.GetArray())
    {
      auto obj = itr.GetObject();
      
      static const char* kTypeNames[] =
      { "Null", "False", "True", "Object", "Array", "String", "Number" };
      for (auto& m : itr.GetObject())
      {
        printf("Type of member %s is %s\n",
               m.name.GetString(), 
               kTypeNames[m.value.GetType()]);
      }

      SizeT id = obj["id"].GetUint64();
      String name = obj["name"].GetString();
      int32 type = obj["type"].GetInt();

      eRESOURCETYPE resType = eRESOURCETYPE::_from_integral(type);
      if (resType == eRESOURCETYPE::TEXTURE)
      {
        // TODO: Fix texture loading as it needs a way to load raw pixel data
        SharedPtr<Texture> newResource = CreateResource<Texture>(name);
        Vector<uint8> data;
        for (auto& pixel : obj["data"].GetArray())
        {
          data.push_back(pixel.GetUint());
        }

        Vector2f imgSize;
        imgSize.x = obj["imgSize"].GetArray()[0].GetUint();
        imgSize.y = obj["imgSize"].GetArray()[1].GetUint();

        sf::Image i;
        i.create(imgSize.x, imgSize.y, data.data());
        // newResource->loadFromMemory(data.data(), data.size());
        newResource->loadFromImage(i);
      }
      else if (resType == eRESOURCETYPE::SOUND)
      {
        SharedPtr<AudioClip> newResource = CreateResource<AudioClip>(name);
        SizeT sampleCount = obj["sampleCount"].GetInt64();
        uint32 sampleRate = obj["sampleRate"].GetUint();
        uint32 channelCount = obj["channelCount"].GetUint();
        Vector<int16> data;
        for (auto& pixel : obj["data"].GetArray())
        {
          data.push_back(pixel.GetInt());
        }

        newResource->loadFromSamples(data.data(), sampleCount, channelCount, sampleRate);
      }
      else if (eRESOURCETYPE::MUSIC == resType) 
      {
        // TODO: Finish this
        SharedPtr<MusicClip> newResource = CreateResource<MusicClip>(name);
      }
      else if (eRESOURCETYPE::ANIMATION == type)
      {
        SharedPtr<Animation> newResource = CreateResource<Animation>(name);

        float animationTime = obj["animationTime"].GetFloat();
        bool loop = obj["loop"].GetBool();
        // Extract textures that conform animation
        newResource->m_loop = loop;
        newResource->m_animationTime = animationTime;

        QueueFrames* queue = new QueueFrames();
        queue->hashID = id;
        queue->type = resType;
        for (auto& frame : obj["data"].GetArray())
        {
          queue->m_frames.push_back(frame.GetString());
        }
        queueResources.push_back(queue);
      }
      else if (eRESOURCETYPE::ATLAS == type)
      {
        SharedPtr<Atlas> newResource = CreateResource<Atlas>(name);

        QueueFrames* queue = new QueueFrames();
        queue->hashID = id;
        queue->type = resType;
        for (auto& frame : obj["data"].GetArray())
        {
          queue->m_frames.push_back(frame.GetString());
        }
        queueResources.push_back(queue);
      }
      else if (eRESOURCETYPE::FONT == type)
      {
        // TODO: Finish this
        SharedPtr<Font> newResource = CreateResource<Font>(name);
      }
      else if (eRESOURCETYPE::SHADER == type)
      {
        // TODO: Finish this
        SharedPtr<ShaderFile> newResource = CreateResource<ShaderFile>(name);
        newResource->LoadFromString(obj["data"].GetString());
      }

    }
// 
    // Process resources that need previously loaded resources
    for (QueueFrames* queue : queueResources)
    {
      if (eRESOURCETYPE::ANIMATION == queue->type)
      {
        for (int i = 0; i < queue->m_frames.size(); ++i)
        {
          SharedPtr<Animation> a = REINTERPRETPOINTER(Animation, m_resources.at(queue->hashID));
          a->m_frames.push_back(GetResource<Texture>(queue->m_frames[i]));
        }
      }
      else if (eRESOURCETYPE::ATLAS == queue->type)
      {
        for (int i = 0; i < queue->m_frames.size(); ++i)
        {
          SharedPtr<Atlas> a = REINTERPRETPOINTER(Atlas, m_resources.at(queue->hashID));
          a->m_atlas.push_back(GetResource<Texture>(queue->m_frames[i]));
        }
      }
    }

  }

  JSONDocument Serialize()
  {
    JSONDocument document;
    document.SetArray();
    JSONDocument::AllocatorType& allocator = document.GetAllocator();

    for (const auto& resource : m_resources)
    {
      String toParseStr = Utils::Format("%s - %s", resource.second->m_resName.c_str(), resource.second->GetType()._to_string());
      Logger::Instance().ToDebugger(toParseStr);
      Logger::Instance().ToConsole(toParseStr);
      JSONValue obj(rapidjson::kObjectType);

      obj.AddMember("id", static_cast<uint64>(resource.first), allocator);
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
        obj.AddMember("width", imageSize.x, allocator);
        obj.AddMember("height", imageSize.y, allocator);

        Vector<uint8> data(pixelData, pixelData + dataSize);
        JSONValue jsonArray(rapidjson::kArrayType);
        
        for (int i = 0; i < data.size(); ++i)
        {
          jsonArray.PushBack(data[i], allocator);
        }

        obj.AddMember("data", jsonArray, allocator);
        JSONValue jsonSize(rapidjson::kArrayType);
        jsonSize.PushBack(img.getSize().x, allocator).PushBack(img.getSize().y, allocator);
        obj.AddMember("imgSize", jsonSize, allocator);
      }
      else if (eRESOURCETYPE::SOUND == type)
      {
        const int16* audioData = REINTERPRETPOINTER(AudioClip, resource.second)->getSamples();
        SizeT sampleCount = REINTERPRETPOINTER(AudioClip, resource.second)->getSampleCount();
        uint32 sampleRate = REINTERPRETPOINTER(AudioClip, resource.second)->getSampleRate();
        uint32 channelCount = REINTERPRETPOINTER(AudioClip, resource.second)->getChannelCount();

        obj.AddMember("sampleCount", sampleCount, allocator);
        obj.AddMember("sampleRate", sampleRate, allocator);
        obj.AddMember("channelCount", channelCount, allocator);

        Vector<int16> data(audioData, audioData + sampleCount);

        JSONValue jsonArray(rapidjson::kArrayType);
        for (int i = 0; i < data.size(); ++i)
        {
          jsonArray.PushBack(data[i], allocator);
        }
        obj.AddMember("data", jsonArray, allocator);
      }
      else if (eRESOURCETYPE::MUSIC == type)
      {
        String musicBuffer = FileSystem::GetAllStringFromFile(REINTERPRETPOINTER(MusicClip, resource.second)->m_filePath);
        obj.AddMember("data", musicBuffer, allocator);
      }
      else if (eRESOURCETYPE::ANIMATION == type)
      {
        obj.AddMember("animationTime", REINTERPRETPOINTER(Animation, resource.second)->m_animationTime, allocator);
        obj.AddMember("loop", REINTERPRETPOINTER(Animation, resource.second)->m_loop, allocator);
        JSONValue jsonArray(rapidjson::kArrayType);
        for (int i = 0; i < REINTERPRETPOINTER(Animation, resource.second)->m_frames.size(); ++i)
        {
          String str = REINTERPRETPOINTER(Animation, resource.second)->m_frames[i]->m_resName;
          JSONValue v(str, allocator);
          jsonArray.PushBack(v, allocator);
        }
        obj.AddMember("data", jsonArray, allocator);
      }
      else if (eRESOURCETYPE::ATLAS == type)
      {
        // TODO: Change how Atlases work. They should contain the whole sprite and create an array from it
        JSONValue jsonArray(rapidjson::kArrayType);
        for (int i = 0; i < REINTERPRETPOINTER(Atlas, resource.second)->m_atlas.size(); ++i)
        {
          String str = REINTERPRETPOINTER(Atlas, resource.second)->m_atlas[i]->m_resName;
          JSONValue v(str, allocator);
          jsonArray.PushBack(v, allocator);
        }
        obj.AddMember("data", jsonArray, allocator);
      }
      else if (eRESOURCETYPE::FONT == type)
      {
        String fontBuffer = FileSystem::GetAllStringFromFile(REINTERPRETPOINTER(Font, resource.second)->m_filePath);
        obj.AddMember("data", fontBuffer, allocator);
      }
      else if (eRESOURCETYPE::SHADER == type)
      {
        // TODO: Finish this
        String str = REINTERPRETPOINTER(ShaderFile, resource.second)->GetShader();
        obj.AddMember("data", str, allocator);
      }



      document.PushBack(obj, allocator);
    }
    return document;
  }

  Map<SizeT, SharedPtr<Resource>> m_resources;

  Vector<Callback<void, bool, String>> m_resourceLoadedCallbacks;

private:
  
  SharedPtr<Resource> MakeFromType(const String& name, const eRESOURCETYPE& type)
  {
    String realName = Utils::Format("%s_%s", type._to_string(), name.c_str());

    if (m_resources.find(Hash<String>()(realName)) != m_resources.end())
    {
      return  m_resources.at(Hash<String>()(realName));
    }

    // eRESOURCETYPE type = T::StaticType();
    SharedPtr<Resource> newResource;

    if (eRESOURCETYPE::TEXTURE == type)
    {
      newResource = MakeSharedObject<Texture>();
    }

    newResource->m_resName = name;
    m_resources.insert(Utils::MakePair(Hash<String>()(realName), newResource));
    return newResource;
  }


};

