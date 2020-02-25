// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletInstanceConfig::BulletInstanceConfig(const GeoVector<float>& startingPosition, const GeoVector<float>& startingRotation, float speed) noexcept :
    _startingPosition(startingPosition),
    _startingRotation(startingRotation),
    _speed(speed) {
  }
}
