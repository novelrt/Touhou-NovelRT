// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Enemy {
  BossEnemy::BossEnemy(std::weak_ptr<NovelRT::NovelRunner> runner, const std::vector<Bullets::BossSpellcard> spellcards) noexcept :
    _runner(runner),
    _spellcards(spellcards) {}

  void BossEnemy::playSpellcard(size_t index) noexcept {
    _spellcards.at(index).activate();
  }
}
