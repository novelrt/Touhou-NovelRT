// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletInstanceConfig::BulletInstanceConfig(const GeoVector2<float>& direction, const GeoVector2<float>& startingPosition, float startingRotation, float speed) noexcept :
    _direction(direction),
    _startingPosition(startingPosition),
    _startingRotation(startingRotation),
    _speed(speed) {
  }
}
