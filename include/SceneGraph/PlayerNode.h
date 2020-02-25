// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_SCENEGRAPH_PLAYERNODE_H
#define TOUHOUNOVELRT_SCENEGRAPH_PLAYERNODE_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::SceneGraph {
  class PhysicsNode : public NovelRT::SceneGraph::RenderObjectNode {
  public:
    PhysicsNode(std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      RenderObjectNode(renderObject) {
    }

    const float getRotation() const {
      return getRenderObject()->getTransform().getRotation();
    }

    const NovelRT::Maths::GeoVector<float>& getPosition() const {
      return getRenderObject()->getTransform().getPosition();
    }

    virtual void setPosition(const NovelRT::Maths::GeoVector<float>& position) {
      getRenderObject()->getTransform().getPosition() = position;
    }
  };

  class PlayerNode : public PhysicsNode {
  public:
    PlayerNode(std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      PhysicsNode(renderObject) {
    }

    void setPosition(const NovelRT::Maths::GeoVector<float>& position) override {
      auto yOff = (SceneGraph::SimpleScene::WorldSize.getY() - ((SceneGraph::SimpleScene::WorldSize.getY() / 3.0f) * 2.25f)) / 2.0f;
      auto size = getRenderObject()->getTransform().getScale() / 2.0f;

      auto xPos = std::clamp(position.getX(), size.getX(), SceneGraph::SimpleScene::WorldSize.getX() - size.getX());
      auto yPos = std::clamp(position.getY(), size.getY() + yOff, SceneGraph::SimpleScene::WorldSize.getY() - yOff - size.getY());

      getRenderObject()->getTransform().getPosition() = NovelRT::Maths::GeoVector(xPos, yPos);
    }
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
