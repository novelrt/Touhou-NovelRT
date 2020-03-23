// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BULLETWAVEDATA_H
#define TOUHOUNOVELRT_BULLETS_BULLETWAVEDATA_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  using namespace NovelRT;
  using namespace NovelRT::Maths;

  class BulletWaveData {
  private:
    std::map<size_t, std::vector<BulletInstanceConfig>> _bulletInstances;
    NovelRT::Timing::Timestamp _timeToNextWave;
  public:
    BulletWaveData(const std::map<size_t, std::vector<BulletInstanceConfig>>& bulletInstanceData, NovelRT::Timing::Timestamp timeToNextState) noexcept;

    inline const std::map<size_t, std::vector<BulletInstanceConfig>>& getInstanceData() const noexcept {
      return _bulletInstances;
    }

    inline NovelRT::Timing::Timestamp getTimeToNextState() const noexcept {
      return _timeToNextWave;
    }
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_BULLETWAVEDATA_H
