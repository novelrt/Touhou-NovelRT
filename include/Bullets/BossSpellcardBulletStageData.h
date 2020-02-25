// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BOSSSPELLCARDBULLETSTAGEDATA_H
#define TOUHOUNOVELRT_BULLETS_BOSSSPELLCARDBULLETSTAGEDATA_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class BossSpellcardBulletStageData {
  private:
    std::vector<BulletWaveData> _waveData;
    std::vector<std::shared_ptr<Emitter>> _spellcardEmitters;

  public:
    BossSpellcardBulletStageData(const std::vector<BulletWaveData>& waveData, const std::vector<std::shared_ptr<Emitter>>& spellcardEmitters) noexcept;

    inline const std::vector<BulletWaveData>& getWaveData() const noexcept {
      return _waveData;
    }

    inline const std::vector<std::shared_ptr<Emitter>>& getEmitters() const noexcept {
      return _spellcardEmitters;
    }
  };
}


#endif //!TOUHOUNOVELRT_BULLETS_BOSSSPELLCARDBULLETSTAGEDATA_H
