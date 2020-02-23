// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  auto runner = NovelRT::NovelRunner(0, "TouhouNovelRT");
  runner.getDebugService().lock()->setIsFpsCounterVisible(true);
  auto transform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(1920.0f / 2.0f, 1080.0f / 2.0f), 0.0f, NovelRT::Maths::GeoVector<float>::one() * 400.0f);
  auto objPtr = std::shared_ptr<NovelRT::WorldObject>(std::move(runner.getRenderer().lock()->createBasicFillRect(transform, 1, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255))));
  auto controller = TouhouNovelRT::Player::Controller(&runner, runner.getInteractionService(), objPtr);

  runner.SceneConstructionRequested += [&] {
    objPtr->executeObjectBehaviour();
  };

  return runner.runNovel();
}
