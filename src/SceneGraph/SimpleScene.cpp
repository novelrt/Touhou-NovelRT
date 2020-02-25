// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

namespace TouhouNovelRT::SceneGraph {
  SimpleScene::SimpleScene(std::weak_ptr<NovelRT::NovelRunner> runner, std::string backgroundFile, std::string borderFile, bool isScrolling) :
    _runner(runner),
      _quadTree(std::make_shared<NovelRT::Maths::QuadTree>(WorldBounds)),
      _bkgdTransformOne(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((WorldSize.getX() * 1.5f), (WorldSize.getY() / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(WorldSize.getX(), (WorldSize.getY() / 3.0f) * 2.25f))),
      _bkgdImageOne(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_bkgdTransformOne, 100, backgroundFile))),
      _borderTransform(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((WorldSize.getX() / 2.0f), (WorldSize.getY() / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(WorldSize.getX() * 2.0f, WorldSize.getY() * 2.0f))),
      _borderImage(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_borderTransform, 101, borderFile))),
      _bkgdTransformTwo(NovelRT::Transform(NovelRT::Maths::GeoVector<float>((WorldSize.getX() / 2.0f), (WorldSize.getY() / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(WorldSize.getX(), (WorldSize.getY() / 3.0f) * 2.25f))),
      _bkgdImageTwo(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_bkgdTransformTwo, 100, backgroundFile))),
      _bkgdTransformThree(NovelRT::Transform(NovelRT::Maths::GeoVector<float>(-(WorldSize.getX() * 1.5f), (WorldSize.getY() / 2.0f)), 0, NovelRT::Maths::GeoVector<float>(WorldSize.getX(), (WorldSize.getY() / 3.0f) * 2.25f))),
      _bkgdImageThree(std::move(_runner.lock()->getRenderer().lock()->createImageRect(_bkgdTransformThree, 100, backgroundFile))),
      _isScrolling(isScrolling) {
      runner.lock()->Update += [&](auto delta) { updateBackground(delta); };
    }

  void SimpleScene::drawObjects() {
    _borderImage->executeObjectBehaviour();
    _bkgdImageOne->executeObjectBehaviour();
    _bkgdImageTwo->executeObjectBehaviour();
    _bkgdImageThree->executeObjectBehaviour();

    for (auto& item : this->getNodes()) {
      auto renderObjectNode = reinterpret_cast<const std::shared_ptr<NovelRT::SceneGraph::RenderObjectNode>&>(item);
      renderObjectNode->getRenderObject()->executeObjectBehaviour();
    }
  }

  void SimpleScene::updateBackground(double delta) {
    if (_isScrolling) {
      auto backOne = _bkgdImageOne->getTransform().getPosition().getX();
      auto backTwo = _bkgdImageTwo->getTransform().getPosition().getX();
      auto backThree = _bkgdImageThree->getTransform().getPosition().getX();
      auto movementVector = NovelRT::Maths::GeoVector<float>::zero();
      movementVector.setX(150.f);

      if (backOne > 2880) {
        _bkgdImageOne->getTransform().setPosition(NovelRT::Maths::GeoVector<float>(-960, _bkgdTransformOne.getPosition().getY()));
      }
      else if (backTwo > 2880) {
        _bkgdImageTwo->getTransform().setPosition(NovelRT::Maths::GeoVector<float>(-960, _bkgdTransformTwo.getPosition().getY()));
      }
      else if (backThree > 2880) {
        _bkgdImageThree->getTransform().setPosition(NovelRT::Maths::GeoVector<float>(-960, _bkgdTransformThree.getPosition().getY()));
      }

      auto delt = static_cast<float>(delta);
      _bkgdImageOne->getTransform().setPosition(_bkgdImageOne->getTransform().getPosition() + (movementVector * delt));
      _bkgdImageTwo->getTransform().setPosition(_bkgdImageTwo->getTransform().getPosition() + (movementVector * delt));
      _bkgdImageThree->getTransform().setPosition(_bkgdImageThree->getTransform().getPosition() + (movementVector * delt));
      _bkgdImageOne->executeObjectBehaviour();
      _bkgdImageTwo->executeObjectBehaviour();
      _bkgdImageThree->executeObjectBehaviour();
    }
  }
}
