// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_H
#define TOUHOUNOVELRT_H

#include <limits>

//dependencies
#include <NovelRT.h>

//value types
#include "Player/MovementState.h"
#include "Bullets/BulletInstanceConfig.h"
#include "Bullets/BulletWaveData.h"

//game includes and typedefs
namespace TouhouNovelRT::Bullets {
  typedef class BossSpellcard BossSpellcard;
  typedef class BossSpellcardBulletStageData BossSpellcardBulletStageData;
  typedef class Bullet Bullet;
  typedef class Emitter Emitter;
  typedef class PlayerSpellcard PlayerSpellcard;
  typedef class ReimuSpellcard ReimuSpellcard;
}

namespace TouhouNovelRT::Enemy {
  typedef class BossEnemy BossEnemy;
}

namespace TouhouNovelRT::Player {
  typedef class Controller Controller;
  typedef class Gun Gun;
}

namespace TouhouNovelRT::SceneGraph {
  typedef class PlayerNode PlayerNode;
  typedef class SimpleScene SimpleScene;
}

//SceneGraph Types
#include "SceneGraph/SimpleScene.h"
#include "SceneGraph/PlayerNode.h"

//Bullets Types
#include "Bullets/BossSpellcardBulletStageData.h"
#include "Bullets/BossSpellcard.h"
#include "Bullets/Bullet.h"
#include "Bullets/BulletFactory.h"
#include "Bullets/Emitter.h"
#include "Bullets/PlayerSpellcard.h"
#include "Bullets/ReimuSpellcard.h"

//Enemy Types
#include "Enemy/BossEnemy.h"

//Player Types
#include "Player/Gun.h"
#include "Player/Controller.h"

#endif //!TOUHOUNOVELRT_H
