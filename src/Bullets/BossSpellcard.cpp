// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::Bullets {
  void BossSpellcard::updateSpellcard(double delta) noexcept {
    if(_delta <= 0 || _wave == std::numeric_limits<size_t>::max()) {
      if (_wave == std::numeric_limits<size_t>::max()) {
        _wave = 0;
      }

      auto index = _wave++;
      if (_stage.getWaveData().size() <= index) {
        index = 0;
      }

      _delta = _stage.getWaveData().at(index).getTimeToNextState();
      auto& map = _stage.getWaveData().at(index).getInstanceData();
      auto& emitters = _stage.getEmitters();
      for (auto& pair : map) {
        for(auto& bullet : pair.second) {
          emitters.at(pair.first)->tryShoot(bullet.getDirection(), bullet.getPosition(), bullet.getRotation(), bullet.getSpeed());
        }
      }
    }
    _delta -= delta;
  }

  BossSpellcard::BossSpellcard(std::weak_ptr<NovelRT::NovelRunner> runner, const BossSpellcardBulletStageData& stage) noexcept :
    _active(false),
    _updateDelegate(NovelRT::Utilities::EventHandler<double>([&](auto delta) { updateSpellcard(delta); })),
    _delta(0.0f),
    _stage(stage),
    _runner(runner){}

  void BossSpellcard::activate() noexcept {
    if (_runner.expired() || _active) {
      return;
    }

    _active = true;
    _runner.lock()->Update += _updateDelegate;
  }

  void BossSpellcard::deactivate() noexcept {
    if (_runner.expired() || !_active) {
      return;
    }

    _active = false;
    _runner.lock()->Update -= _updateDelegate;
  }
}
