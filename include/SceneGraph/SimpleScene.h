// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_SCENEGRAPH_SIMPLESCENE_H
#define TOUHOUNOVELRT_SCENEGRAPH_SIMPLESCENE_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::SceneGraph {
  class SimpleScene : public NovelRT::SceneGraph::Scene {
  private:
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    std::shared_ptr<NovelRT::Maths::QuadTree> _quadTree;
    NovelRT::Transform _bkgdTransformOne;
    NovelRT::Transform _bkgdTransformTwo;
    NovelRT::Transform _bkgdTransformThree;
    NovelRT::Transform _borderTransform;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _bkgdImageOne;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _bkgdImageTwo;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _bkgdImageThree;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _borderImage;
    bool _isScrolling;

    void updateBackground(NovelRT::Timing::Timestamp delta);

  public:
    inline static const NovelRT::Maths::GeoVector2<float> WorldSize = NovelRT::Maths::GeoVector2(1920.0f, 1080.0f);
    inline static const NovelRT::Maths::GeoVector2<float> WorldOrigin = WorldSize / 2.0f;
    inline static const NovelRT::Maths::GeoBounds WorldBounds = NovelRT::Maths::GeoBounds(WorldOrigin, WorldSize, 0.0f);

    SimpleScene(std::weak_ptr<NovelRT::NovelRunner> runner, std::string backgroundFile, std::string borderFile, bool isScrolling);

    void drawObjects();
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
