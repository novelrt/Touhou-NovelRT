// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::World {
  Scene::Scene(std::weak_ptr<NovelRT::NovelRunner> runner, std::string backgroundFile, std::string borderFile, bool isScrolling) :
    _runner(runner),
    _backgroundTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((_screenWidth/2.0f), (_screenHeight / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(_screenWidth, (_screenHeight / 3.0f) * 2.25f))),
    _backgroundImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_backgroundTransform, 100, backgroundFile))),
    _borderTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((_screenWidth / 2.0f), (_screenHeight / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(_screenWidth * 2.0f, _screenHeight * 2.0f))),
    _borderImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_borderTransform, 101, borderFile))),
    _secondBkgdTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>(-960.0f, (_screenHeight / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(_screenWidth, (_screenHeight / 3.0f) * 2.25f))),
    _secondBkgdImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_secondBkgdTransform, 100, backgroundFile))),
    _isScrolling(isScrolling) {
    runner.lock()->Update += [&](auto delta) { updateBackground(delta); };
  }

  void Scene::updateBackground(double delta) {
    if (_isScrolling) {
      int backOne = _backgroundImage->getTransform().getPosition().getX();
      int backTwo = _secondBkgdImage->getTransform().getPosition().getX();
      auto movementVector = NovelRT::Maths::GeoVector<float>::zero();
      movementVector.setX(150.f);

      if (backOne > 1920) {
        _backgroundImage->getTransform().setPosition(NovelRT::Maths::GeoVector<float>(-960, _backgroundTransform.getPosition().getY()));
      }
      else if (backTwo > 1920) {
        _secondBkgdImage->getTransform().setPosition(NovelRT::Maths::GeoVector<float>(-960, _backgroundTransform.getPosition().getY()));
      }

      auto delt = static_cast<float>(delta);
      _backgroundImage->getTransform().setPosition(_backgroundImage->getTransform().getPosition() + (movementVector * delt));
      _secondBkgdImage->getTransform().setPosition(_secondBkgdImage->getTransform().getPosition() + (movementVector * delt));
      _backgroundImage->executeObjectBehaviour();
      _secondBkgdImage->executeObjectBehaviour();
    }
  }

  void Scene::drawObjects() {
    _borderImage->executeObjectBehaviour();
    _backgroundImage->executeObjectBehaviour();
    _secondBkgdImage->executeObjectBehaviour();
  }

}
