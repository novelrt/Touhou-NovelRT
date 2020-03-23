// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BULLETINSTANCECONFIG_H
#define TOUHOUNOVELRT_BULLETS_BULLETINSTANCECONFIG_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  using namespace NovelRT;
  using namespace NovelRT::Maths;
  class BulletInstanceConfig {
  private:
    GeoVector2<float> _direction;
    GeoVector2<float> _startingPosition;
    float _startingRotation;
    float _speed;

  public:
    BulletInstanceConfig(const GeoVector2<float>& direction, const GeoVector2<float>& startingPosition, float startingRotation, float speed) noexcept;

    inline const GeoVector2<float>& getDirection() const noexcept {
      return _direction;
    }

    inline const GeoVector2<float>& getPosition() const noexcept {
      return _startingPosition;
    }

    inline float getRotation() const noexcept {
      return _startingRotation;
    }

    inline float getSpeed() const noexcept {
      return _speed;
    }
  };
}


#endif //!TOUHOUNOVELRT_BULLETS_BULLETINSTANCECONFIG_H
