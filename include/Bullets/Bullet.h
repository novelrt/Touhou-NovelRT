// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BULLET_H
#define TOUHOUNOVELRT_BULLETS_BULLET_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class Bullet : public NovelRT::WorldObject {
  private:
    NovelRT::Maths::GeoVector2<float> _direction;
    float _bulletSpeed;
    std::unique_ptr<NovelRT::Graphics::RenderObject> _renderTarget;
    std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> _enemy;

  public:
    Bullet(float bulletSpeed, std::weak_ptr<NovelRT::NovelRunner> runner, std::unique_ptr<NovelRT::Graphics::RenderObject> renderTarget, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> enemy) noexcept;

    inline void setDirection(const NovelRT::Maths::GeoVector2<float>& value) noexcept {
      _direction = value;
    }

    void executeObjectBehaviour() final;

    void bulletUpdate(NovelRT::Timing::Timestamp delta) noexcept;
  };
}


#endif //!TOUHOUNOVELRT_BULLETS_BULLET_H
