// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_EMEMY_BOSSENEMY_H
#define TOUHOUNOVELRT_EMEMY_BOSSENEMY_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Enemy {
  class BossEnemy {
  private:
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    std::vector<Bullets::BossSpellcard> _spellcards;

  public:
    BossEnemy(std::weak_ptr<NovelRT::NovelRunner> runner, const std::vector<Bullets::BossSpellcard> spellcards) noexcept;
    void playSpellcard(size_t index) noexcept;
  };
}

#endif //!TOUHOUNOVELRT_EMEMY_BOSSENEMY_H
