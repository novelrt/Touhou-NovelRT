// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  BulletFactory::BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, bool isFill, const std::string& textureFile) noexcept :
    _colourConfig(colourConfig),
    _isFill(isFill),
    _layer(layer),
    _scale(scale),
    _runner(runner),
    _texture(_runner.lock()->getRenderer().lock()->getTexture(textureFile)) {}

  BulletFactory::BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, std::shared_ptr<NovelRT::Graphics::Texture> texture) noexcept :
    _colourConfig(colourConfig),
    _isFill(false),
    _layer(layer),
    _scale(scale),
    _runner(runner),
    _texture(texture) {}

  std::unique_ptr<Bullet> BulletFactory::create(const NovelRT::Maths::GeoVector<float>& startingPosition, const NovelRT::Maths::GeoVector<float>& direction, float speed) noexcept
  {
    if (_runner.expired()) {
      return nullptr;
    }

    auto rendererPtr = _runner.lock()->getRenderer().lock();
    auto transform = NovelRT::Transform(startingPosition, 0.0f, _scale);
    auto ptr = (_isFill) ? std::unique_ptr<NovelRT::Graphics::RenderObject>(std::move(rendererPtr->createBasicFillRect(transform, _layer, _colourConfig))) : std::unique_ptr<NovelRT::Graphics::RenderObject>(std::move(rendererPtr->createImageRect(transform, _layer, _colourConfig)));
    return std::make_unique<Bullet>(speed, _runner, ptr);
  }
}
