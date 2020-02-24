// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_H
#define TOUHOUNOVELRT_H

//dependencies
#include <NovelRT.h>

//value types
#include "Player/MovementState.h"

//game includes and typedefs
namespace TouhouNovelRT::Player {
  typedef class Controller Controller;
  typedef class Gun Gun;
}

namespace TouhouNovelRT::Bullets {
  typedef class Bullet Bullet;
  typedef class Emitter Emitter;
}

//Bullets Types
#include "Bullets/Bullet.h"
#include "Bullets/BulletFactory.h"
#include "Bullets/Emitter.h"
#include "Bullets/PlayerSpellcard.h"
#include "Bullets/ReimuSpellcard.h"

//Player Types
#include "Player/Gun.h"
#include "Player/Controller.h"

#endif //!TOUHOUNOVELRT_H
