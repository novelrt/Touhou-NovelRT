// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_REIMUSPELLCARD_H
#define TOUHOUNOVELRT_BULLETS_REIMUSPELLCARD_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class ReimuSpellcard : public PlayerSpellcard {
  public:
    ReimuSpellcard(std::shared_ptr<Emitter> spellcardEmitter) noexcept;
    void activate() noexcept final;
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_REIMUSPELLCARD_H
