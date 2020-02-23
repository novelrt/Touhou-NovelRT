// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_PLAYER_GUN_H
#define TOUHOUNOVELRT_PLAYER_GUN_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Player {
  class Gun {
  private:
    std::vector<std::shared_ptr<Bullets::Emitter>> _emitters;

  public:
    Gun(const std::vector<std::shared_ptr<Bullets::Emitter>>& emitters) noexcept;
    void shoot(const NovelRT::Maths::GeoVector<float>& direction) noexcept;
    void invokeSceneConstruction() const;
  };
}

#endif //!TOUHOUNOVELRT_PLAYER_GUN_H
