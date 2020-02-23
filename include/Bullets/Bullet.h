// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_EMITTER_H
#define TOUHOUNOVELRT_BULLETS_BULLET_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class Bullet {
  private:
    NovelRT::Transform _transform;
    NovelRT::Maths::GeoVector<float> _direction;
    float _bulletSpeed;
    bool _isInUse;
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    std::shared_ptr<NovelRT::WorldObject> _bulletObject;


  public:
    Bullet(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Transform startingTransform, std::shared_ptr<NovelRT::WorldObject> bulletObject, float bulletSpeed) noexcept;
    Bullet() noexcept;

    inline bool getInUse() const noexcept {
      return _isInUse;
    }

    inline bool setInUse(bool value) noexcept {
      _isInUse = value;
    }

    NovelRT::Transform& getTransform() noexcept;
    inline void setDirection(const NovelRT::Maths::GeoVector<float>& value) noexcept {
      _direction = value;
    }
  };
}


#endif //!TOUHOUNOVELRT_BULLETS_BULLET_H
