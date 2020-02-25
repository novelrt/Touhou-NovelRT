// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletInstanceConfig::BulletInstanceConfig(const GeoVector<float>& direction, const GeoVector<float>& startingPosition, float startingRotation, float speed) noexcept :
    _direction(direction),
    _startingPosition(startingPosition),
    _startingRotation(startingRotation),
    _speed(speed) {
  }
}
