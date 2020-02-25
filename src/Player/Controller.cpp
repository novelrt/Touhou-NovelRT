// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Player {
  using namespace NovelRT;
  using namespace NovelRT::Input;
  using namespace NovelRT::Maths;
  using namespace NovelRT::Utilities;

  Controller::Controller(const Gun& gun, NovelRT::NovelRunner* runner, std::weak_ptr<InteractionService> input, std::shared_ptr<TouhouNovelRT::SceneGraph::PhysicsNode> physicsNode) noexcept :
    _gun(gun),
    _moveUpKey(KeyCode::UpArrow),
    _moveDownKey(KeyCode::DownArrow),
    _moveLeftKey(KeyCode::LeftArrow),
    _moveRightKey(KeyCode::RightArrow),
    _usePreciseMovementKey(KeyCode::C),
    _shootKey(KeyCode::Z),
    _spellcardKey(KeyCode::X),
    _movementState(MovementState::Idle),
    _input(input),
    _physicsNode(physicsNode) {
    runner->Update += [&](auto delta) { controllerUpdate(delta); };
  }

  void Controller::controllerUpdate(double delta) {
    if (_input.expired()) {
      return;
    }

    auto input = _input.lock();
    combatUpdate(delta, input);
    movementUpdate(delta, input);
  }

  void Controller::movementUpdate(double delta, const std::shared_ptr<InteractionService>& input) {
    auto moveUpState = input->getKeyState(_moveUpKey);
    auto moveDownState = input->getKeyState(_moveDownKey);
    auto moveLeftState = input->getKeyState(_moveLeftKey);
    auto moveRightState = input->getKeyState(_moveRightKey);
    auto precisionMove = input->getKeyState(_usePreciseMovementKey);

    //all these if elses aren't needed, neither is the movement state enum - HOWEVER, this does show off NovelRT's bitflags feature. :D
    if (moveUpState == KeyState::KeyDown || moveUpState == KeyState::KeyDownHeld) {
      _movementState |= MovementState::Up;
    }
    else {
      _movementState &= ~MovementState::Up;
    }

    if (moveDownState == KeyState::KeyDown || moveDownState == KeyState::KeyDownHeld) {
      _movementState |= MovementState::Down;
    }
    else {
      _movementState &= ~MovementState::Down;
    }

    if (moveLeftState == KeyState::KeyDown || moveLeftState == KeyState::KeyDownHeld) {
      _movementState |= MovementState::Left;
    }
    else {
      _movementState &= ~MovementState::Left;
    }

    if (moveRightState == KeyState::KeyDown || moveRightState == KeyState::KeyDownHeld) {
      _movementState |= MovementState::Right;
    }
    else {
      _movementState &= ~MovementState::Right;
    }

    auto inputVector = GeoVector<float>::zero();

    auto applyUp = [&] { inputVector.setY(-1.0f); };
    auto applyDown = [&] { inputVector.setY(1.0f); };
    auto applyLeft = [&] { inputVector.setX(-1.0f); };
    auto applyRight = [&] { inputVector.setX(1.0f); };

    switch (_movementState) {
    case TouhouNovelRT::Player::MovementState::Idle:
      break;
    case TouhouNovelRT::Player::MovementState::Up: {
      applyUp();
      break;
    }
    case TouhouNovelRT::Player::MovementState::Down: {
      applyDown();
      break;
    }
    case TouhouNovelRT::Player::MovementState::Left: {
      applyLeft();
      break;
    }
    case TouhouNovelRT::Player::MovementState::Right: {
      applyRight();
      break;
    }
    case TouhouNovelRT::Player::MovementState::UpLeft: {
      applyUp();
      applyLeft();
      break;
    }
    case TouhouNovelRT::Player::MovementState::UpRight: {
      applyUp();
      applyRight();
      break;
    }
    case TouhouNovelRT::Player::MovementState::DownLeft: {
      applyDown();
      applyLeft();
      break;
    }
    case TouhouNovelRT::Player::MovementState::DownRight: {
      applyDown();
      applyRight();
      break;
    }
    case TouhouNovelRT::Player::MovementState::Everything:
    default:
      break;
    }

    if (inputVector != GeoVector<float>::zero()) {
      inputVector = inputVector.getNormalised();
    }

    auto moveSpeed = (precisionMove == KeyState::KeyDown || precisionMove == KeyState::KeyDownHeld) ? 250.0f : 600.0f;
    _physicsNode->addPosition((inputVector * (moveSpeed * static_cast<float>(delta))));
  }

  void Controller::combatUpdate(double delta, const std::shared_ptr<NovelRT::Input::InteractionService>& input) {
    auto shootState = input->getKeyState(_shootKey);
    auto spellcardState = input->getKeyState(_spellcardKey);

    if (shootState == KeyState::KeyDown || shootState == KeyState::KeyDownHeld) {
      _gun.shoot(GeoVector<float>(1.0f, 0.0f));
    }

    if (spellcardState == KeyState::KeyDown || spellcardState == KeyState::KeyDownHeld) {
      _gun.shootSpellcard();
    }
  }
}
