// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_BULLETFACTORY_H
#define TOUHOUNOVELRT_BULLETS_BULLETFACTORY_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class BulletFactory {
  private:
    NovelRT::Graphics::RGBAConfig _colourConfig;
    bool _isFill;
    int _layer;
    NovelRT::Maths::GeoVector<float> _scale;
    std::weak_ptr<NovelRT::NovelRunner> _runner;

    std::shared_ptr<NovelRT::Graphics::Texture> _texture;

  public:
    BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, bool isFill = false, const std::string& textureFile = std::string("")) noexcept;
    BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, std::shared_ptr<NovelRT::Graphics::Texture> texture) noexcept;

    std::unique_ptr<Bullet> create(const NovelRT::Maths::GeoVector<float>& startingPosition, const NovelRT::Maths::GeoVector<float>& direction, float speed) noexcept;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_BULLETFACTORY_H
