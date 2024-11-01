#pragma once
#include "uiPrerequisites.h"
#include "uiComponent.h"
#include "uiShaderFile.h"

#include "SFML/Graphics/Shader.hpp"

class Shader : public Component, public sf::Shader
{
public:
  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::SHADER; }

  virtual void Initialize() override;

  virtual void OnDestroy() override;
  
  virtual void PropagateTransform(const Transform2D& newTransform) override;
 
  virtual void Update(const float& delta) override;

  void SetVertexShader(const ShaderFile& data);
  
  void SetFragmentShader(const ShaderFile& data);

  void SetGeometryShader(const ShaderFile& data);

};

