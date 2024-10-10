#pragma once

#include "uiPrerequisites.h"
#include "uiEntity.h"

struct ClassRegisters
{
public:

  using FactoryFunc = std::function<SharedPtr<Entity>()>;

  static void RegisterClass(const String& className, FactoryFunc creator)
  {
    GetRegistry()[className] = creator;
  }

  template<class... Args> 
  static SharedPtr<Entity> CreateEntity(const String& className, Args&& ...args)
  {
    auto it = GetRegistry().find(className);
    if (it != GetRegistry().end()) {
      return it->second(forward<Args>(args)...);
    }
  }


  static std::unordered_map<String, FactoryFunc>& GetRegistry()
  {
    static std::unordered_map<String, FactoryFunc> registry;
    return registry;
  }

};

#define REGISTER_CLASS(className) \
    namespace { \
        const bool registered_##className = (ClassRegisters::RegisterClass(#className, []() -> SharedPtr<Entity> { return  MakeSharedObject<Entity>(); }), true); \
    }
