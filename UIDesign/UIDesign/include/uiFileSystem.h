#pragma once

#include "uiPrerequisites.h"

#include <filesystem>


using Path = std::filesystem::path;
using DirectoryEntry = std::filesystem::directory_entry;
using FileStatus = std::filesystem::file_status;
using FileType = std::filesystem::file_type;

// TODO: Simplify this
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
  static void Copy(const String& from, 
                   const String& to) { return std::filesystem::copy(Path(from), Path(to)); }
  static void Copy(const Path& from, 
                   const Path& to) { return std::filesystem::copy(from, to); }
  static void Rename(const String& oldName, 
                     const String& newName) { return std::filesystem::rename(Path(oldName), Path(newName)); }
  static void Rename(const Path& oldName, 
                     const Path& newName) { return std::filesystem::rename(oldName, newName); }
  static bool IsEmpty(const Path& p) { return std::filesystem::is_empty(p); }
  static bool IsEmpty(const String& p) { return std::filesystem::is_empty(Path(p)); }
  static bool Erase(const Path& p) { return std::filesystem::remove(p); }
  static bool Erase(const String& p) { return std::filesystem::remove(Path(p)); }
  static bool EraseAll(const Path& p) { return std::filesystem::remove_all(p); }
  static bool EraseAll(const String& p) { return std::filesystem::remove_all(Path(p)); }
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
  static String GetAllStringFromFile(const String& p)
  {
    IFStream f;
    f.open(p.c_str());
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
