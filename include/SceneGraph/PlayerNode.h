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

    virtual void onCollision() {
    }
  };

  class PlayerNode : public PhysicsNode {
  private:
    std::unique_ptr<NovelRT::Animation::SpriteAnimator> _animator;

    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _idleState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingRightState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingLeftState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _stunState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _deathState;

    const int32_t Idle = 0;
    const int32_t MovingRight = 1;
    const int32_t MovingLeft = 2;
    const int32_t Stun = 4;
    const int32_t Death = 5;

    int32_t _activeState;
    int32_t _health;

  public:
    PlayerNode(std::shared_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      PhysicsNode(renderObject),
      _idleState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingRightState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingLeftState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _stunState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _deathState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _activeState(Idle),
      _health(3) {

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
      _idleState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _idleState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
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
      _movingRightState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _movingRightState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
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
      _movingLeftState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _movingLeftState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
      _movingLeftState->setFrames(movingFramesLeft);

      auto stunFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      {
        auto frame0 = NovelRT::Animation::SpriteAnimatorFrame();
        frame0.setDuration((1.0f / 15.0f) * 10.0f);
        frame0.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-0.png").string()));
        frame0.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        stunFrames.push_back(frame0);

        auto frame10 = NovelRT::Animation::SpriteAnimatorFrame();
        frame10.setDuration((1.0f / 15.0f) * 10.0f);
        frame10.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-10.png").string()));
        frame10.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        stunFrames.push_back(frame10);

        auto frame20 = NovelRT::Animation::SpriteAnimatorFrame();
        frame20.setDuration((1.0f / 15.0f) * 1.0f);
        frame20.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-20.png").string()));
        frame20.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        frame20.FrameExit += [&]() { _activeState = Idle; };
        stunFrames.push_back(frame20);
      }

      _stunState->setShouldLoop(true);
      _stunState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _stunState->setFrames(stunFrames);

      auto deathFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      {
        auto frame0 = NovelRT::Animation::SpriteAnimatorFrame();
        frame0.setDuration((1.0f / 15.0f) * 1.0f);
        frame0.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-0.png").string()));
        frame0.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame0);

        auto frame1 = NovelRT::Animation::SpriteAnimatorFrame();
        frame1.setDuration((1.0f / 15.0f) * 9.0f);
        frame1.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-1.png").string()));
        frame1.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame1);

        auto frame10 = NovelRT::Animation::SpriteAnimatorFrame();
        frame10.setDuration((1.0f / 15.0f) * 1.0f);
        frame10.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-10.png").string()));
        frame10.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame10);

        auto frame11 = NovelRT::Animation::SpriteAnimatorFrame();
        frame11.setDuration((1.0f / 15.0f) * 9.0f);
        frame11.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-11.png").string()));
        frame11.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame11);

        auto frame20 = NovelRT::Animation::SpriteAnimatorFrame();
        frame20.setDuration((1.0f / 15.0f) * 20.0f);
        frame20.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-20.png").string()));
        frame20.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame20);

        auto frame40 = NovelRT::Animation::SpriteAnimatorFrame();
        frame40.setDuration((1.0f / 15.0f) * 10.0f);
        frame40.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-40.png").string()));
        frame40.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame40);

        auto frame50 = NovelRT::Animation::SpriteAnimatorFrame();
        frame50.setDuration((1.0f / 15.0f) * 1.0f);
        frame50.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-50.png").string()));
        frame50.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame50);

        auto frame51 = NovelRT::Animation::SpriteAnimatorFrame();
        frame51.setDuration((1.0f / 15.0f) * 1.0f);
        frame51.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-50.png").string()));
        frame51.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        frame51.FrameExit += [&]() { getRenderObject()->setActive(false); };
        deathFrames.push_back(frame51);
      }

      _deathState->setShouldLoop(true);
      _deathState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _deathState->setFrames(deathFrames);

      _animator = std::make_unique<NovelRT::Animation::SpriteAnimator>(runner.get(), reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject()).get());
      _animator->insertNewState(_idleState);
      _animator->play();
    }

    void setPosition(const NovelRT::Maths::GeoVector<float>& position) override {
      auto yOff = (SceneGraph::SimpleScene::WorldSize.getY() - ((SceneGraph::SimpleScene::WorldSize.getY() / 3.0f) * 2.25f)) / 2.0f;
      auto size = getRenderObject()->getTransform().getScale() / 2.0f;

      auto xPos = std::clamp(position.getX(), size.getX(), SceneGraph::SimpleScene::WorldSize.getX() - (TouhouNovelRT::SceneGraph::SimpleScene::WorldSize.getX() / 5) - size.getX());
      auto yPos = std::clamp(position.getY(), size.getY() + yOff, SceneGraph::SimpleScene::WorldSize.getY() - yOff - size.getY());

      getRenderObject()->getTransform().getPosition() = NovelRT::Maths::GeoVector(xPos, yPos);
    }

    void addPosition(const NovelRT::Maths::GeoVector<float>& delta) override {
      if (delta.getX() == 0.0f) {
        if (_activeState == MovingLeft || _activeState == MovingRight) {
          _activeState = Idle;
        } else if (delta.getY() == 0.0f) {
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

    void onCollision() override {
      if (_activeState == Stun) {
        return;
      } else if (_health < 0) {
        _activeState = Death;
      } else {
        _activeState = Stun;
        _health--;
      }
    }
  };

  class BossNode : public PhysicsNode {
  private:
    std::unique_ptr<NovelRT::Animation::SpriteAnimator> _animator;

    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _idleState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingRightState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _movingLeftState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _stunState;
    std::shared_ptr<NovelRT::Animation::SpriteAnimatorState> _deathState;

    const int32_t Idle = 0;
    const int32_t MovingRight = 1;
    const int32_t MovingLeft = 2;
    const int32_t Stun = 3;
    const int32_t Death = 4;

    int32_t _activeState;
    int32_t _health;

  public:
    BossNode(std::shared_ptr<NovelRT::NovelRunner> runner, std::shared_ptr<NovelRT::Graphics::RenderObject> renderObject) :
      PhysicsNode(renderObject),
      _idleState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingRightState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _movingLeftState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _stunState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _deathState(std::make_shared<NovelRT::Animation::SpriteAnimatorState>()),
      _activeState(Idle),
      _health(3) {

      std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
      std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
      std::filesystem::path imagesDirPath = resourcesDirPath / "Images" / "char" / "cirno";

      auto idleFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 6; i++) {
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
      _idleState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _idleState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
      _idleState->setFrames(idleFrames);

      auto movingFramesRight = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 8; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(1.0f / 15.0f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "right" / ("21-" + std::to_string(i) + ".png")).string()));
        frame.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          imageRect->getTransform().setScale(imageRect->getTexture()->getSize());
        };
        movingFramesRight.push_back(frame);
      }

      _movingRightState->setShouldLoop(false);
      _movingRightState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _movingRightState->insertNewState(_movingLeftState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingLeft; }});
      _movingRightState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _movingRightState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
      _movingRightState->setFrames(movingFramesRight);

      auto movingFramesLeft = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      for (int32_t i = 0; i < 8; i++) {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.setDuration(1.0f / 15.0f);
        frame.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "left" / ("20-" + std::to_string(i) + ".png")).string()));
        frame.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          imageRect->getTransform().setScale(imageRect->getTexture()->getSize());
        };
        movingFramesLeft.push_back(frame);
      }

      _movingLeftState->setShouldLoop(false);
      _movingLeftState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _movingLeftState->insertNewState(_movingRightState, std::vector<std::function<bool()>> {[&]() { return _activeState == MovingRight; }});
      _movingLeftState->insertNewState(_stunState, std::vector<std::function<bool()>> {[&]() { return _activeState == Stun; }});
      _movingLeftState->insertNewState(_deathState, std::vector<std::function<bool()>> {[&]() { return _activeState == Death; }});
      _movingLeftState->setFrames(movingFramesLeft);

      auto stunFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      {
        auto frame0 = NovelRT::Animation::SpriteAnimatorFrame();
        frame0.setDuration((1.0f / 15.0f) * 10.0f);
        frame0.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-0.png").string()));
        frame0.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        stunFrames.push_back(frame0);

        auto frame10 = NovelRT::Animation::SpriteAnimatorFrame();
        frame10.setDuration((1.0f / 15.0f) * 10.0f);
        frame10.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-10.png").string()));
        frame10.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        stunFrames.push_back(frame10);

        auto frame20 = NovelRT::Animation::SpriteAnimatorFrame();
        frame20.setDuration((1.0f / 15.0f) * 1.0f);
        frame20.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "stun" / "5000-20.png").string()));
        frame20.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        frame20.FrameExit += [&]() { _activeState = Idle; };
        stunFrames.push_back(frame20);
      }

      _stunState->setShouldLoop(true);
      _stunState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _stunState->setFrames(stunFrames);

      auto deathFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

      {
        auto frame1 = NovelRT::Animation::SpriteAnimatorFrame();
        frame1.setDuration((1.0f / 15.0f) * 9.0f);
        frame1.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-1.png").string()));
        frame1.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame1);

        auto frame10 = NovelRT::Animation::SpriteAnimatorFrame();
        frame10.setDuration((1.0f / 15.0f) * 10.0f);
        frame10.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-10.png").string()));
        frame10.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame10);

        auto frame20 = NovelRT::Animation::SpriteAnimatorFrame();
        frame20.setDuration((1.0f / 15.0f) * 10.0f);
        frame20.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-20.png").string()));
        frame20.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame20);

        auto frame30 = NovelRT::Animation::SpriteAnimatorFrame();
        frame30.setDuration((1.0f / 15.0f) * 10.0f);
        frame30.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-30.png").string()));
        frame30.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame30);

        auto frame40 = NovelRT::Animation::SpriteAnimatorFrame();
        frame40.setDuration((1.0f / 15.0f) * 10.0f);
        frame40.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-40.png").string()));
        frame40.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        deathFrames.push_back(frame40);

        auto frame50 = NovelRT::Animation::SpriteAnimatorFrame();
        frame50.setDuration((1.0f / 15.0f) * 1.0f);
        frame50.setTexture(runner->getRenderer().lock()->getTexture((imagesDirPath / "death" / "5030-50.png").string()));
        frame50.FrameEnter += [&]() {
          auto imageRect = reinterpret_cast<const std::shared_ptr<NovelRT::Graphics::ImageRect>&>(getRenderObject());
          auto textureSize = imageRect->getTexture()->getSize();
          imageRect->getTransform().setScale(textureSize);
        };
        frame50.FrameExit += [&]() { getRenderObject()->setActive(false); };
        deathFrames.push_back(frame50);
      }

      _deathState->setShouldLoop(true);
      _deathState->insertNewState(_idleState, std::vector<std::function<bool()>> {[&]() { return _activeState == Idle; }});
      _deathState->setFrames(deathFrames);

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
        if (_activeState == MovingLeft || _activeState == MovingRight) {
          _activeState = Idle;
        } else if (delta.getY() == 0.0f) {
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

    void onCollision() override {
      if (_activeState == Stun) {
        return;
      } else if (_health < 0) {
        _activeState = Death;
      } else {
        _activeState = Stun;
        _health--;
      }
    }
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
