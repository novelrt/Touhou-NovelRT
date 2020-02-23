// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  Emitter::Emitter(float bulletSpeed, float cooldown, std::weak_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::WorldObject> muzzle, const Bullet& bulletPrefab) noexcept :
    _bulletSpeed(bulletSpeed),
    _cooldown(cooldown),
    _timeToNextBullet(0.0f),
    _runner(runner),
    _muzzle(muzzle),
    _bulletPrefab(bulletPrefab){
    _runner.lock()->Update += [&](auto delta) { updateEmitter(delta); };
  }

  void Emitter::updateEmitter(double delta) noexcept {
    _timeToNextBullet -= static_cast<float>(delta);

    for (auto& bullet : _bulletPool) {
      if (bullet.getTransform().getPosition().getX() > 1920.0f || bullet.getTransform().getPosition().getX() < 0.0f || bullet.getTransform().getPosition().getY() > 1080.0f || bullet.getTransform().getPosition().getY() < 0.0f) {
        bullet.setInUse(false);
      }
    }
  }

  void Emitter::shoot(NovelRT::Maths::GeoVector<float> direction) noexcept {
    if (_timeToNextBullet > 0.0f) {
      return;
    }

    _timeToNextBullet = _cooldown;

    for (auto& bullet : _bulletPool) {
      if (bullet.getInUse()) {
        continue;
      }

      bullet.getTransform().setPosition(_muzzle->getTransform().getPosition());
      bullet.getTransform().setRotation(_muzzle->getTransform().getRotation());
      _bulletPool.back().setDirection(direction);
      bullet.setInUse(true);
      return;
    }

    _bulletPool.push_back(Bullet(_bulletPrefab));
    _bulletPool.back().getTransform().setPosition(_muzzle->getTransform().getPosition());
    _bulletPool.back().getTransform().setRotation(_muzzle->getTransform().getRotation());
    _bulletPool.back().setDirection(direction);
    _bulletPool.back().setInUse(true);
  }
}


