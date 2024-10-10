#pragma once

#include "uiPrerequisites.h"

#include <filesystem>


using Path = std::filesystem::path;
using DirectoryEntry = std::filesystem::directory_entry;
using FileStatus = std::filesystem::file_status;
using FileType = std::filesystem::file_type;

struct FileSystem
{
  static const Path ExePath()
  {
    return Path(m_exePath);
  }
  static const Path CurrentPath() { return std::filesystem::current_path(); }
  static const String CurrentPathString() { return std::filesystem::current_path().string(); }
  static const Path AbsolutePath(const Path& p) { return std::filesystem::absolute(p); }
  static void SetCurrentPath(const Path& p) { return std::filesystem::current_path(p); }
  static void SetCurrentPath(const String& p) { return std::filesystem::current_path(Path(p)); }
  static bool Exists(const Path& p) { return std::filesystem::exists(p); }
  static bool Exists(const String& p) { return std::filesystem::exists(Path(p)); }
  static bool CreateDirectory(const Path& p) { return std::filesystem::create_directory(p); }
  static bool CreateDirectory(const String& p) { return std::filesystem::create_directory(Path(p)); }
  static bool CreateDirectories(const Path& p) { return std::filesystem::create_directories(p); }
  static bool CreateDirectories(const String& p) { return std::filesystem::create_directories(Path(p)); }
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
  static String m_exePath;
};


struct FileExt
{
  static String JSON;
  static String SCENE;
  static String PACKAGE;
  static String ASSET;
};
