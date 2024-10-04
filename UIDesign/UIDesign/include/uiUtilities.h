#pragma once

#include "uiPrerequisites.h"

// FUNCTIONS

template <typename T, typename... Args>
UniquePtr<T> MakeUniqueObject(Args ... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
SharedPtr<T> MakeSharedObject(Args ... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

#define MAKEUNIQUEOBJECT(T, ...) std::make_unique<T>(__VA_ARGS__)

#define MAKESHAREDOBJECT(T, ...) std::make_shared<T>(__VA_ARGS__)

#define REINTERPRETPOINTER(T, ...) std::reinterpret_pointer_cast<T>(__VA_ARGS__)

#define STATICPOINTER(T, ...) std::static_pointer_cast<T>(__VA_ARGS__)

#define STATICCAST(T, ...) std::static_cast<T>(__VA_ARGS__)

// UTILITIES

struct FileSystem
{
  static const Path CurrentPath() { return std::filesystem::current_path(); }
  static void SetCurrentPath(const Path& p) { return std::filesystem::current_path(p); }
  static String GetAllStringFromFile(const Path& p) 
  {
    IFStream f;
    f.open(p.string().c_str());
    if (!f.is_open())
    {
      return "";
    }
    SStream buffer;
    buffer << f.rdbuf();
    return buffer.str();
  }

  template<typename T>
  static bool ToFile(const T& data, const String& path)
  {
    OFStream file(path, std::ios::binary);
    if (file.is_open())
    {
      file.write(reinterpret_cast<const char*>(&data), sizeof(T));
      file.close();
    }
    else
    {
      // Throw error
      return false;
    }
    return true;
  }

  template<typename T>
  static T FromFile(const String& path)
  {
    T data{};
    IFStream file(path, std::ios::binary);
    if (file.is_open())
    {
      file.read(reinterpret_cast<char*>(&data), sizeof(T));
      file.close();
    }
    else
    {
      // Throw error
    }
    return data;
  }

};

struct Utils
{
  static String IntToHex(const int32& toValue, bool optionalPrefix = false, char toFillWith = '\0')
  {
    SStream stream;
    stream << std::hex 
           << std::uppercase // Convert to hex and uppercase
           << toValue;
    String prefix = (optionalPrefix ? "0x" : "");
    if (toFillWith != '\0')
    {
      SizeT size = static_cast<SizeT>(6 - stream.str().size());
      String middle(size, toFillWith);
      return prefix + middle + stream.str();
    }
    return prefix + stream.str();
  }

  static void
  runCommand(const String& commandLine) {
    system(commandLine.c_str());
  }

  template<typename ... Args>
  static String Format(const String& format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { ThrowRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  template<typename T>
  static String 
  ToString(const T& number) {
    return std::to_string(number);
  }

  static void 
  ThrowException(const String& message) {
    throw::std::exception(message.c_str());
  }

  static void 
  ThrowRuntimeError(const String& message) {
    throw::std::runtime_error(message.c_str());
  }

  static const String BLANK;

  static WString
  ToWide(String str) {
    WString stemp = WString(str.begin(), str.end());
    return stemp;

  }

  template<typename T, typename A>
  static Pair<T, A>
  MakePair(T value1, A value2) {
    return std::make_pair(value1, value2);
  }
};


