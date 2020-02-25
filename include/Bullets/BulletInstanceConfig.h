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
    GeoVector<float> _startingPosition;
    GeoVector<float> _startingRotation;
    float _speed;

  public:
    BulletInstanceConfig(const GeoVector<float>& startingPosition, const GeoVector<float>& startingRotation, float speed) noexcept;

    inline const GeoVector<float>& getPosition() const noexcept {
      return _startingPosition;
    }

    inline const GeoVector<float>& getRotation() const noexcept {
      return _startingRotation;
    }

    inline float getSpeed() const noexcept {
      return _speed;
    }
  };
}


#endif //!TOUHOUNOVELRT_BULLETS_BULLETINSTANCECONFIG_H
