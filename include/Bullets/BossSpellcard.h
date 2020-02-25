// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H
#define TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class BossSpellcard {
  private:
    NovelRT::Utilities::EventHandler<double> _updateDelegate;
    double _delta;
    BossSpellcardBulletStageData _stage;
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    size_t _wave = std::numeric_limits<size_t>::max();
    bool _active;

    void updateSpellcard(double delta) noexcept;


  public:
    BossSpellcard(std::weak_ptr<NovelRT::NovelRunner> runner, const BossSpellcardBulletStageData& stage) noexcept;

    void activate() noexcept;
    void deactivate() noexcept;
    void constructBullets() noexcept;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H
