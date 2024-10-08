#pragma once

#include "uiPrerequisites.h"

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


struct FileExtensions
{

};
