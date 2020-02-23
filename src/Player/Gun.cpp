// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Player {
  Gun::Gun(const std::vector<std::shared_ptr<Bullets::Emitter>>& emitters) noexcept :
    _emitters(emitters) {
  }

  void Gun::shoot(const NovelRT::Maths::GeoVector<float>& direction) noexcept {
    for (auto& emitter : _emitters) {
      emitter->shoot(direction);
    }
  }


}
