// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  using namespace NovelRT;
  using namespace NovelRT::Maths;

  Bullet::Bullet(float bulletSpeed, std::weak_ptr<NovelRT::NovelRunner> runner, std::unique_ptr<NovelRT::Graphics::RenderObject> renderTarget, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> enemy) noexcept :
    NovelRT::WorldObject(renderTarget->transform(), renderTarget->layer()),
    _direction(GeoVector2<float>::zero()),
    _bulletSpeed(bulletSpeed),
    _renderTarget(std::move(renderTarget)),
    _enemy(enemy) {
  }

  void Bullet::bulletUpdate(NovelRT::Timing::Timestamp delta) noexcept {
    if (!getActive()) {
      return;
    }

    transform().position() = transform().position() + _direction * _bulletSpeed * delta.getSecondsFloat();

    auto bulletBounds = transform().getBounds();
    auto bulletPosition = bulletBounds.position();
    auto bulletSize = bulletBounds.size();

    auto enemyBounds = _enemy->getRenderObject()->transform().getBounds();
    auto enemyPosition = enemyBounds.position();
    auto enemySize = enemyBounds.size();

    if ((enemyPosition.getX() < bulletPosition.getX() + bulletSize.getX()) &&
        (bulletPosition.getX() < enemyPosition.getX() + enemySize.getX()) &&
        (enemyPosition.getY() < bulletPosition.getY() + bulletSize.getY()) &&
        (bulletPosition.getY() < enemyPosition.getY() + enemySize.getY())) {
      setActive(false);
      _enemy->onCollision();
    }
  }

  void Bullet::executeObjectBehaviour() {
    auto& targetTransform = _renderTarget->transform();
    if (_isDirty) {
      _renderTarget->layer() = layer();
      targetTransform.position() = transform().position();
      targetTransform.setRotation(transform().getRotation());
      targetTransform.setScale(transform().getScale());
    }

    _renderTarget->executeObjectBehaviour();
  }
}
