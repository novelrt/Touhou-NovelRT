// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  PlayerSpellcard::PlayerSpellcard(std::shared_ptr<Emitter> spellcardEmitter) noexcept :
    _cardsLeft(2),
    _spellcardEmitter(spellcardEmitter){}
  void PlayerSpellcard::constructSpellcard() noexcept {
    _spellcardEmitter->constructBullets();
  }
}
