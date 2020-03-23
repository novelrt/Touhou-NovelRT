// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  Emitter::Emitter(float bulletSpeed, float cooldown, std::weak_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> muzzle, const BulletFactory& factory) noexcept :
    _bulletSpeed(bulletSpeed),
    _cooldown(NovelRT::Timing::Timestamp::fromSeconds(cooldown)),
    _timeToNextBullet(NovelRT::Timing::Timestamp(0)),
    _runner(runner),
    _muzzle(muzzle),
    _factory(factory){
    _runner.lock()->Update += [&](auto delta) { updateEmitter(delta); };
  }

  void Emitter::updateEmitter(NovelRT::Timing::Timestamp delta) noexcept {
    _timeToNextBullet += delta;

    for (auto& bullet : _bulletPool) {
      if (bullet->transform().position().getX() > 1920.0f || bullet->transform().position().getX() < 0.0f || bullet->transform().position().getY() > 1080.0f || bullet->transform().position().getY() < 0.0f) {
        bullet->setActive(false);
        continue;
      }

      bullet->bulletUpdate(delta);
    }
  }

  bool Emitter::tryShoot(const NovelRT::Maths::GeoVector2<float>& direction, const NovelRT::Maths::GeoVector2<float>& position, float rotation, float bulletSpeed) noexcept {
    if (_timeToNextBullet < _cooldown) {
      return false;
    }

    _timeToNextBullet = NovelRT::Timing::Timestamp(0);

    for (auto& bullet : _bulletPool) {
      if (bullet->getActive()) {
        continue;
      }

      bullet->transform().position() = position;
      bullet->transform().setRotation(rotation);
      _bulletPool.back()->setDirection(direction);
      bullet->setActive(true);
      return true;
    }

    _bulletPool.push_back(std::move(_factory.create(position, direction, bulletSpeed)));
    _bulletPool.back()->transform().setRotation(rotation);
    _bulletPool.back()->setDirection(direction);
    _bulletPool.back()->setActive(true);

    return true;
  }

  bool Emitter::tryShoot(const NovelRT::Maths::GeoVector2<float>& direction) noexcept {
    return tryShoot(direction, _muzzle->getPosition(), _muzzle->getRotation(), _bulletSpeed);
  }

  void Emitter::constructBullets() noexcept {
    for (auto& bullet : _bulletPool) {
      if (!bullet->getActive()) {
        continue;
      }

      bullet->executeObjectBehaviour();
    }
  }
}


