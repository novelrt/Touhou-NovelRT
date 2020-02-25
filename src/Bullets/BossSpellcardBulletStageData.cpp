// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BossSpellcardBulletStageData::BossSpellcardBulletStageData(const std::vector<BulletWaveData>& waveData, const std::vector<std::shared_ptr<Emitter>>& spellcardEmitters) noexcept :
   _waveData(waveData),
  _spellcardEmitters(spellcardEmitters){
  }
}
