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
  private:
    std::unique_ptr<NovelRT::Animation::SpriteAnimator> _animator;

    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _idleState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingState;

    bool _shouldBeInIdle;

  public:
    PlayerNode(std::shared_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      PhysicsNode(renderObject),
      _idleState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _shouldBeInIdle(true) {

      std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
      std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
      std::filesystem::path imagesDirPath = resourcesDirPath / "Images" / "char" / "marisa";

      auto idleFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 10; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(0.1f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "idle" / ("0-" + std::to_string(i) + ".png")).string()));
        idleFrames.push_back(frame);
      }

      idleFrames.back().FrameExit += [&]() { _shouldBeInIdle = false; };

      _idleState->setShouldLoop(true);
      _idleState->insertNewState(_movingState, std::vector<std::function<bool()>> {[&]() { return !_shouldBeInIdle; }});
      _idleState->setFrames(idleFrames);

      auto movingFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 5; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(0.1f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "right" / ("100-" + std::to_string(i) + ".png")).string()));
        movingFrames.push_back(frame);
      }

      movingFrames.back().FrameExit += [&]() { _shouldBeInIdle = true; };

      _movingState->setShouldLoop(true);
      _movingState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _shouldBeInIdle; }});
      _movingState->setFrames(movingFrames);

      _animator = std::make_unique<NovelRT::Animation::SpriteAnimator>(runner.get(), reinterpret_cast<NovelRT::Graphics::ImageRect*>(getRenderObject().get()));
      _animator->insertNewState(_idleState);
      _animator->play();
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
