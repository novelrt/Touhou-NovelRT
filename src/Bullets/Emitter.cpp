// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  Emitter::Emitter(float bulletSpeed, float cooldown, std::weak_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> muzzle, const BulletFactory& factory) noexcept :
    _bulletSpeed(bulletSpeed),
    _cooldown(cooldown),
    _timeToNextBullet(0.0f),
    _runner(runner),
    _muzzle(muzzle),
    _factory(factory){
    _runner.lock()->Update += [&](auto delta) { updateEmitter(delta); };
  }

  void Emitter::updateEmitter(double delta) noexcept {
    _timeToNextBullet -= static_cast<float>(delta);

    for (auto& bullet : _bulletPool) {
      if (bullet->getTransform().getPosition().getX() > 1920.0f || bullet->getTransform().getPosition().getX() < 0.0f || bullet->getTransform().getPosition().getY() > 1080.0f || bullet->getTransform().getPosition().getY() < 0.0f) {
        bullet->setActive(false);
        continue;
      }

      bullet->bulletUpdate(delta);
    }
  }

  bool Emitter::tryShoot(NovelRT::Maths::GeoVector<float> direction) noexcept {
    if (_timeToNextBullet > 0.0f) {
      return false;
    }

    _timeToNextBullet = _cooldown;

    for (auto& bullet : _bulletPool) {
      if (bullet->getActive()) {
        continue;
      }

      bullet->getTransform().setPosition(_muzzle->getPosition());
      bullet->getTransform().setRotation(_muzzle->getRotation());
      _bulletPool.back()->setDirection(direction);
      bullet->setActive(true);
      return true;
    }

    _bulletPool.push_back(std::move(_factory.create(_muzzle->getPosition(), _direction, _bulletSpeed)));
    _bulletPool.back()->getTransform().setPosition(_muzzle->getPosition());
    _bulletPool.back()->getTransform().setRotation(_muzzle->getRotation());
    _bulletPool.back()->setDirection(direction);
    _bulletPool.back()->setActive(true);

    return true;
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


