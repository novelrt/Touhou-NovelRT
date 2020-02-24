// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  using namespace NovelRT;
  using namespace NovelRT::Maths;

  ReimuSpellcard::ReimuSpellcard(std::shared_ptr<Emitter> spellcardEmitter) noexcept :
    PlayerSpellcard(spellcardEmitter) {}

  void ReimuSpellcard::activate() noexcept {
    if (getCardCount() > 0 && _spellcardEmitter->tryShoot(GeoVector<float>(0.0f, 1.0f))) {
      decrementCardCount();
    }
  }
}


