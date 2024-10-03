#include "imgui.h"
#include "imgui-SFML.h"

#include "uiApp.h"
#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiAtlas.h"
#include "uiBullet.h"
#include "uiBoxCollider.h"
#include "uiEntity.h"
#include "uiInput.h"
#include "uiInputManager.h"
#include "uiInputMapping.h"
#include "uiPhysics.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include "uiGameSettings.h"

#include <cstdlib>
#include <ctime>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main() {


  App::StartUp();
  App::Instance().Run();

  return 0;

  
}