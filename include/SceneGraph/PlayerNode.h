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

    virtual void addPosition(const NovelRT::Maths::GeoVector<float>& delta) {
      if (delta == NovelRT::Maths::GeoVector(0.0f, 0.0f)) {
        return;
      }

      auto position = getRenderObject()->getTransform().getPosition() + delta;
      setPosition(position);
    }
  };

  class PlayerNode : public PhysicsNode {
  private:
    std::unique_ptr<NovelRT::Animation::SpriteAnimator> _animator;

    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _idleState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingRightState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingLeftState;

    const int32_t Idle = 0;
    const int32_t MovingRight = 1;
    const int32_t MovingLeft = 2;

    int32_t _activeState;

  public:
    PlayerNode(std::shared_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      PhysicsNode(renderObject),
      _idleState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingRightState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingLeftState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _activeState(Idle) {

      std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
      std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
      std::filesystem::path imagesDirPath = resourcesDirPath / "Images" / "char" / "marisa";

      auto idleFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 10; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(1.0f / 15.0f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "idle" / ("0-" + std::to_string(i) + ".png")).string()));
        frame.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        idleFrames.push_back(frame);
      }

      _idleState->setShouldLoop(true);
      _idleState->insertNewState(_movingRightState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingRight; }});
      _idleState->insertNewState(_movingLeftState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingLeft; }});
      _idleState->setFrames(idleFrames);

      auto movingFramesRight = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 1; i < 7; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(1.0f / 15.0f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "right" / ("100-" + std::to_string(i) + ".png")).string()));
        frame.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          imageRect->getTransform().setScale(imageRect->getTexture()->getSize());
        };
        movingFramesRight.push_back(frame);
      }

      _movingRightState->setShouldLoop(false);
      _movingRightState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _movingRightState->insertNewState(_movingLeftState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingLeft; }});
      _movingRightState->setFrames(movingFramesRight);

      auto movingFramesLeft = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 1; i < 5; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(1.0f / 15.0f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "left" / ("105-" + std::to_string(i) + ".png")).string()));
        frame.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          imageRect->getTransform().setScale(imageRect->getTexture()->getSize());
        };
        movingFramesLeft.push_back(frame);
      }

      _movingLeftState->setShouldLoop(false);
      _movingLeftState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _movingLeftState->insertNewState(_movingRightState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingRight; }});
      _movingLeftState->setFrames(movingFramesLeft);

      _animator = std::make_unique<NovelRT::Animation::SpriteAnimator>(runner.get(), reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject()).get());
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

    void addPosition(const NovelRT::Maths::GeoVector<float>& delta) override {
      if (delta.getX() == 0.0f) {
        _activeState = Idle;

        if (delta.getY() == 0.0f) {
          return;
        }
      }
      else if (delta.getX() < 0.0f) {
        _activeState = MovingLeft;
      }
      else {
        _activeState = MovingRight;
      }

      auto position = getRenderObject()->getTransform().getPosition() + delta;
      setPosition(position);
    }
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
