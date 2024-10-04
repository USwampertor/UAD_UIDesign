#pragma once

#include "uiPrerequisites.h"

#include <SFPhysics/SFPhysics.h>


using PhysicsCollisionResult = sfp::PhysicsBodyCollisionResult;
using PhysicsRectangle = sfp::PhysicsRectangle;
using PhysicsBody = sfp::PhysicsBody;
using World = sfp::World;

using CollisionCallback = Callback<void, const PhysicsCollisionResult&>;
