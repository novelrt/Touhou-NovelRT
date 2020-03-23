// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_PLAYER_CONTROLLER_H
#define TOUHOUNOVELRT_PLAYER_CONTROLLER_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Player {
  class Controller {
  private:
    Gun _gun;
    NovelRT::Input::KeyCode _moveUpKey;
    NovelRT::Input::KeyCode _moveDownKey;
    NovelRT::Input::KeyCode _moveLeftKey;
    NovelRT::Input::KeyCode _moveRightKey;
    NovelRT::Input::KeyCode _usePreciseMovementKey;
    NovelRT::Input::KeyCode _shootKey;
    NovelRT::Input::KeyCode _spellcardKey;
    MovementState _movementState;
    std::weak_ptr<NovelRT::Input::InteractionService> _input;
    std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> _physicsNode;
    

    void controllerUpdate(NovelRT::Timing::Timestamp delta);
    void movementUpdate(NovelRT::Timing::Timestamp delta, const std::shared_ptr<NovelRT::Input::InteractionService>& input);
    void combatUpdate(NovelRT::Timing::Timestamp delta, const std::shared_ptr<NovelRT::Input::InteractionService>& input);

  public:
    Controller(const Gun& gun, NovelRT::NovelRunner* runner, std::weak_ptr<NovelRT::Input::InteractionService> input, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> physicsNode) noexcept;

    inline Gun& getGunHandler() {
      return _gun;
    }
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_CONTROLLER_H
