// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Player {
  Gun::Gun(const std::vector<std::shared_ptr<Bullets::Emitter>>& emitters, std::shared_ptr<Bullets::PlayerSpellcard> spellcardEmitter) noexcept :
    _emitters(emitters),
  _spellcardEmitter(spellcardEmitter) {
  }

  void Gun::shoot(const NovelRT::Maths::GeoVector2<float>& direction) noexcept {
    for (auto& emitter : _emitters) {
      emitter->tryShoot(direction);
    }
  }

  void Gun::shootSpellcard() noexcept {
    _spellcardEmitter->activate();
  }

  void Gun::invokeSceneConstruction() const {
    for (auto& emitter : _emitters) {
      emitter->constructBullets();
    }

    _spellcardEmitter->constructSpellcard();
  }


}
