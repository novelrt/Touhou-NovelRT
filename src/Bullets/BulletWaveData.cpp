// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletWaveData::BulletWaveData(const std::map<size_t, std::vector<BulletInstanceConfig>>& bulletInstanceData, float timeToNextWave) noexcept :
    _bulletInstances(bulletInstanceData),
    _timeToNextWave(timeToNextWave) {}
}
