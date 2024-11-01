#pragma once

#include "uiPrerequisites.h"
#include "uiResource.h"
#include "uiFileSystem.h"

class ShaderFile : public Resource
{
public: 
  ShaderFile() : Resource(ShaderFile::StaticType()) {}
  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::SHADER; }
  bool LoadFromFile(const String& filePath) 
  {
    m_shaderData = FileSystem::GetAllStringFromFile(filePath);
    return !m_shaderData.empty();
  }
  bool LoadFromString(const String& fileData)
  {
    m_shaderData = fileData;
    return !m_shaderData.empty();
  }
  String& GetShader() { return m_shaderData; }
private:
  String m_shaderData;
};