// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H
#define TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class BossSpellcard {
  protected:
    double _delta;
    std::vector<BossSpellcardBulletStageData> _stages;
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    size_t _stage;

  public:
    BossSpellcard(std::weak_ptr<NovelRT::NovelRunner> runner, const std::vector<BossSpellcardBulletStageData>& stages) noexcept;

    virtual void activate() noexcept = 0;
    virtual void deactivate() noexcept = 0;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_BOSSSPELLCARD_H
