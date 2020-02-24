// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::World {
  Scene::Scene(std::weak_ptr<NovelRT::NovelRunner> runner, std::string backgroundFile, std::string borderFile) : _runner(runner),
    _screenWidth(_runner.lock()->getWindowingService().lock()->getWindowSize().getX()),
    _screenHeight(_runner.lock()->getWindowingService().lock()->getWindowSize().getY()),
    _backgroundTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>(0,(_screenHeight/3.0f)*2.0f), 0, NovelRT::Maths::GeoVector<float>(_screenWidth*2.0f, _screenHeight))),
    _backgroundImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_backgroundTransform, 100, backgroundFile))),
    _backgroundDoubleTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>(_backgroundTransform.getPosition().getX(), (_screenHeight / 3.0f) * 2.0f), 0, NovelRT::Maths::GeoVector<float>(_screenWidth * 2.0f, _screenHeight))),
    _backgroundDoubleImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_backgroundDoubleTransform, 100, backgroundFile))),
    _borderTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((_screenWidth/2.0f), (_screenHeight/2.0f)), 0, NovelRT::Maths::GeoVector<float>(_screenWidth*2.0f, _screenHeight*2.0f))),
    _borderImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_borderTransform, 101, borderFile))) {

  }

  void Scene::drawObjects() {
    _borderImage->executeObjectBehaviour();
    _backgroundImage->executeObjectBehaviour();
    _backgroundDoubleImage->executeObjectBehaviour();
  }
}
