// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BossSpellcard::BossSpellcard(std::weak_ptr<NovelRT::NovelRunner> runner, const std::vector<BossSpellcardBulletStageData>& stages) noexcept :
    _delta(0.0f),
    _stages(stages),
    _stage(0),
    _runner(runner){}
}
