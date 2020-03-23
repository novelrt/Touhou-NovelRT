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
    NovelRT::Maths::GeoVector2<float> _direction;
    float _bulletSpeed;
    NovelRT::Timing::Timestamp _cooldown;
    NovelRT::Timing::Timestamp _timeToNextBullet;
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> _muzzle;
    BulletFactory _factory;

    void updateEmitter(NovelRT::Timing::Timestamp delta) noexcept;
  public:
    Emitter(float bulletSpeed, float cooldown, std::weak_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> muzzle, const BulletFactory& factory) noexcept;
    bool tryShoot(const NovelRT::Maths::GeoVector2<float>& direction, const NovelRT::Maths::GeoVector2<float>& position, float rotation, float bulletSpeed) noexcept;
    bool tryShoot(const NovelRT::Maths::GeoVector2<float>& direction) noexcept;
    void constructBullets() noexcept;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_EMITTER_H
