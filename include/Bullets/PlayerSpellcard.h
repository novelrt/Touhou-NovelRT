// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_BULLETS_PLAYERSPELLCARD_H
#define TOUHOUNOVELRT_BULLETS_PLAYERSPELLCARD_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::Bullets {
  class PlayerSpellcard {
  protected:
    int32_t _cardsLeft;
    std::shared_ptr<Emitter> _spellcardEmitter;

  public:
    PlayerSpellcard(std::shared_ptr<Emitter> spellcardEmitter) noexcept;
    virtual void activate() noexcept = 0;
    void constructSpellcard() noexcept;

    inline void incrementCardCount() noexcept {
      ++_cardsLeft;
    };

    inline void decrementCardCount() noexcept {
      --_cardsLeft;
    }

    inline int32_t getCardCount() const noexcept {
      return _cardsLeft;
    }

    inline void setCardCount(int32_t value) noexcept {
      _cardsLeft = value;
    }



    
  };
}

#endif //!TOUHOUNOVELRT_BULLETS_PLAYERSPELLCARD_H
