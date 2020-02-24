// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_PLAYER_MOVEMENTSTATE_H
#define TOUHOUNOVELRT_PLAYER_MOVEMENTSTATE_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Player {
  enum class MovementState : uint32_t {
    Idle = 0b00000000000000000000000000000000,
    Up = 0b00000000000000000000000000000001,
    Down = 0b00000000000000000000000000000010,
    Left = 0b00000000000000000000000000000100,
    Right = 0b00000000000000000000000000001000,
    UpLeft = Up | Left,
    UpRight = Up | Right,
    DownLeft = Down | Left,
    DownRight = Down | Right,
    Everything = ~Idle
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_MOVEMENTSTATE_H
