// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_EMITTER_H
#define TOUHOUNOVELRT_BULLETS_EMITTER_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class Emitter {
  private:
    std::vector<std::unique_ptr<Bullet>> _bulletPool;
    NovelRT::Maths::GeoVector<float> _direction;
    float _bulletSpeed;
    float _cooldown;
    float _timeToNextBullet;
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    std::shared_ptr<NovelRT::WorldObject> _muzzle;
    BulletFactory _factory;

    void updateEmitter(double delta) noexcept;
  public:
    Emitter(float bulletSpeed, float cooldown, std::weak_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::WorldObject> muzzle, const BulletFactory& factory) noexcept;
    void shoot(NovelRT::Maths::GeoVector<float> direction) noexcept;
    void constructBullets() noexcept;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_EMITTER_H
