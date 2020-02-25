// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_SCENEGRAPH_SIMPLESCENE_H
#define TOUHOUNOVELRT_SCENEGRAPH_SIMPLESCENE_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::SceneGraph {
  class SimpleScene : public NovelRT::SceneGraph::Scene {
  private:
    std::shared_ptr<NovelRT::Maths::QuadTree> _quadTree;

  public:
    inline static const NovelRT::Maths::GeoVector<float> WorldSize = NovelRT::Maths::GeoVector(1920.0f, 1080.0f);
    inline static const NovelRT::Maths::GeoVector<float> WorldOrigin = WorldSize / 2.0f;
    inline static const NovelRT::Maths::GeoBounds WorldBounds = NovelRT::Maths::GeoBounds(WorldOrigin, WorldSize, 0.0f);

    SimpleScene() :
      _quadTree(std::make_shared<NovelRT::Maths::QuadTree>(WorldBounds)){
    }
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
