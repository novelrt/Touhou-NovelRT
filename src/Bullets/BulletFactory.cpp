// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletFactory::BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector2<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, bool isFill, const std::string& textureFile, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> enemy) noexcept :
    _colourConfig(colourConfig),
    _isFill(isFill),
    _layer(layer),
    _textureCounter(0),
    _scale(scale),
    _runner(runner),
    _textureVector(std::vector<std::shared_ptr<NovelRT::Graphics::Texture>> {_runner.lock()->getRenderer().lock()->getTexture(textureFile)}),
    _enemy(enemy) {}

  BulletFactory::BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector2<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, std::shared_ptr<NovelRT::Graphics::Texture> texture, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> enemy) noexcept :
    _colourConfig(colourConfig),
    _isFill(false),
    _layer(layer),
    _textureCounter(0),
    _scale(scale),
    _runner(runner),
    _textureVector(std::vector<std::shared_ptr<NovelRT::Graphics::Texture>> {texture}),
    _enemy(enemy) {}

  BulletFactory::BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector2<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, const std::vector<std::string>& bulletTextures, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> enemy) noexcept :
    _colourConfig(colourConfig),
    _isFill(false),
    _layer(layer),
    _textureCounter(0),
    _scale(scale),
    _runner(runner),
    _textureVector(std::vector<std::shared_ptr<NovelRT::Graphics::Texture>>()),
    _enemy(enemy) {
    for (auto& path : bulletTextures) {
      _textureVector.emplace_back(_runner.lock()->getRenderer().lock()->getTexture(path));
    }
  }

  std::unique_ptr<Bullet> BulletFactory::create(const NovelRT::Maths::GeoVector2<float>& startingPosition, const NovelRT::Maths::GeoVector2<float>& direction, float speed) noexcept
  {
    if (_runner.expired()) {
      return nullptr;
    }

    auto rendererPtr = _runner.lock()->getRenderer().lock();
    auto transform = NovelRT::Transform(startingPosition, 0.0f, _scale);

    std::unique_ptr<NovelRT::Graphics::RenderObject> ptr = nullptr;

    if (_isFill) {
      ptr = std::unique_ptr<NovelRT::Graphics::RenderObject>(std::move(rendererPtr->createBasicFillRect(transform, _layer, _colourConfig)));
    } else {
      auto rect = rendererPtr->createImageRect(transform, _layer, _colourConfig);

      if (_textureCounter >= _textureVector.size()) {
        _textureCounter = 0;
      }

      rect->texture() = _textureVector.at(_textureCounter++);
      ptr = std::unique_ptr<NovelRT::Graphics::RenderObject>(std::move(rect));
    }

    return std::make_unique<Bullet>(speed, _runner, std::move(ptr), _enemy);
  }
}
