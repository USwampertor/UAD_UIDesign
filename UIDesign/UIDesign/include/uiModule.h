#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"

template <class T>
class Module
{
public:

  /**
   * Returns a reference to the instance
   */
  static T&
  Instance() 
  {
    if (!IsStartedUp()) 
    {
      Utils::ThrowException("Trying to access a module but it hasn't been started.");
    }

    if (IsDestroyed()) 
    {
      Utils::ThrowException("Trying to access a destroyed module.");
    }

    return *_instance();
  }

  /**
   * Returns a pointer to the instance
   */
  static T*
  InstancePtr() 
  {
    if (!IsStartedUp())
    {
      Utils::ThrowException("Trying to access a module but it hasn't been started.");
    }

    if (IsDestroyed()) 
    {
      Utils::ThrowException("Trying to access a destroyed module.");
    }

    return _instance();
  }


  template<class... Args>
  static void
  StartUp(Args&& ...args) 
  {
    if (IsStartedUp()) 
    {
      Utils::ThrowException("Trying to start an already started module.");
    }

    _instance() = Ui_new<T>(std::forward<Args>(args)...);
    IsStartedUp() = true;

    static_cast<Module*>(_instance())->OnStartUp();
  }

  template<class SubType, class... Args>
  static void
  StartUp(Args&& ...args) 
  {
    static_assert(std::is_base_of<T, SubType>::value,
      "Provided type isn't derived from type the Module is initialized with.");

    if (IsStartedUp()) 
    {
      Utils::ThrowException("Trying to start an already started module.");
    }

    _instance() = Ui_new<SubType>(std::forward<Args>(args)...);
    if (nullptr == _instance()) 
    {
      Utils::ThrowException("Instance failed to initialize");
    }
    IsStartedUp() = true;

    static_cast<Module*>(_instance())->OnStartUp();
  }

  static void
  ShutDown() 
  {
    if (IsDestroyed()) 
    {
      Utils::ThrowException("Trying to shut down an already shut down module.");
    }

    if (!IsStartedUp()) 
    {
      Utils::ThrowException("Trying to shut down a module which was never started.");
    }

    static_cast<Module*>(_instance())->OnShutDown();

    Ui_delete(_instance());
    IsDestroyed() = true;
  }

  static bool
  IsStarted() 
  {
    return IsStartedUp() && !IsDestroyed();
  }

  static void
  SetModule(T* obj) 
  {
    _instance() = obj;
    if (nullptr == _instance()) 
    {
      Utils::ThrowException("Instance failed to be set");
    }
    IsStartedUp() = true;
  }

protected:

  /**
    * Default constructor
    */
  Module() = default;

  /**
    * Virtual destructor
    */
  virtual
  ~Module() = default;

  Module(Module&&) = delete;

  Module(const Module&) = delete;

  Module&
  operator=(Module&&) = delete;

  Module&
  operator=(const Module&) = delete;

  virtual void
  OnStartUp() {}

  virtual void
  OnShutDown() {}

  static T*&
  _instance() 
  {
    static T* inst = nullptr;
    return inst;
  }

  static bool&
  IsDestroyed() 
  {
    static bool inst = false;
    return inst;
  }

  static bool&
  IsStartedUp() 
  {
    static bool inst = false;
    return inst;
  }
};

