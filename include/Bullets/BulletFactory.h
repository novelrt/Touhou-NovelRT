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
    int _layer; //I know this is inconsistent but the layer parameter on rects is int, not int32_t, so I did this for consistency. - Ruby <3
    int32_t _textureCounter;
    NovelRT::Maths::GeoVector<float> _scale;
    std::weak_ptr<NovelRT::NovelRunner> _runner;

    std::vector<std::shared_ptr<NovelRT::Graphics::Texture>> _textureVector;


  public:
    BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, bool isFill = false, const std::string& textureFile = std::string("")) noexcept;
    BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, std::shared_ptr<NovelRT::Graphics::Texture> texture) noexcept;
    BulletFactory(std::weak_ptr<NovelRT::NovelRunner> runner, NovelRT::Maths::GeoVector<float> scale, NovelRT::Graphics::RGBAConfig colourConfig, int layer, const std::vector<std::string>& bulletTextures) noexcept;

    std::unique_ptr<Bullet> create(const NovelRT::Maths::GeoVector<float>& startingPosition, const NovelRT::Maths::GeoVector<float>& direction, float speed) noexcept;

    inline void setIsFill(bool value) noexcept {
      _isFill = value;
    }
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_BULLETFACTORY_H
