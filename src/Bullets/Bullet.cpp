// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  using namespace NovelRT;
  using namespace NovelRT::Maths;

  Bullet::Bullet(float bulletSpeed, std::weak_ptr<NovelRT::NovelRunner> runner, std::unique_ptr<NovelRT::Graphics::RenderObject> renderTarget) noexcept :
    NovelRT::WorldObject(renderTarget->getTransform(), renderTarget->getLayer()),
    _direction(GeoVector<float>::zero()),
    _bulletSpeed(bulletSpeed),
    _renderTarget(std::move(renderTarget)) {
  }

  void Bullet::bulletUpdate(double delta) noexcept {
    if (!getActive()) {
      return;
    }

    getTransform().setPosition(getTransform().getPosition() + _direction * _bulletSpeed * static_cast<float>(delta));
  }

  void Bullet::executeObjectBehaviour() {
    auto& targetTransform = _renderTarget->getTransform();
    if (_isDirty) {
      _renderTarget->setLayer(getLayer());
      targetTransform.setPosition(getTransform().getPosition());
      targetTransform.setRotation(getTransform().getRotation());
      targetTransform.setScale(getTransform().getScale());
    }

    _renderTarget->executeObjectBehaviour();
  }
}
