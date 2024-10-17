#pragma once

#include "uiPrerequisites.h"
#include "uiEntity.h"

struct ClassRegisters
{
public:

  using EntityFactoryFunc = std::function<SharedPtr<Entity>()>;

  static void RegisterEntity(const String& entityClassName, EntityFactoryFunc creator)
  {
    GetEntityRegistry()[entityClassName] = creator;
  }

  template<class... Args> 
  static SharedPtr<Entity> CreateEntity(const String& entityClassName, Args&& ...args)
  {
    auto it = GetEntityRegistry().find(entityClassName);
    if (it != GetEntityRegistry().end()) {
      return it->second(forward<Args>(args)...);
    }
  }


  static std::unordered_map<String, EntityFactoryFunc>& GetEntityRegistry()
  {
    static std::unordered_map<String, EntityFactoryFunc> entityRegistry;
    return entityRegistry;
  }

};

#define REGISTER_CLASS(entityClassName) \
    namespace { \
        const bool registered_##entityClassName = (ClassRegisters::RegisterEntity(#entityClassName, []() -> SharedPtr<Entity> { return  MakeSharedObject<Entity>(); }), true); \
    }
