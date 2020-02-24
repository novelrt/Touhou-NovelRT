// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT");
  auto transform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(1920.0f / 2.0f, 1080.0f / 2.0f), 0.0f, NovelRT::Maths::GeoVector<float>::one() * 50.0f);
  auto objPtr = std::shared_ptr<NovelRT::WorldObject>(std::move(runner->getRenderer().lock()->createBasicFillRect(transform, 1, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255))));
  auto factory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(100.0f, 100.0f), NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 2, true);

  auto coll = std::vector<std::shared_ptr<TouhouNovelRT::Bullets::Emitter>> { std::make_shared<TouhouNovelRT::Bullets::Emitter>(1800.0f, 0.05f, runner, objPtr, factory) };
  auto bla = TouhouNovelRT::Player::Gun(coll);
  auto controller = TouhouNovelRT::Player::Controller(bla, runner.get(), runner->getInteractionService(), objPtr);

  runner->SceneConstructionRequested += [&] {
    objPtr->executeObjectBehaviour();
    controller.getGunHandler().invokeSceneConstruction();
  };

  return runner->runNovel();
}
