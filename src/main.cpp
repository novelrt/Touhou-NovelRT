// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT");
  auto scene = std::make_unique<TouhouNovelRT::SceneGraph::SimpleScene>();

  auto transform = NovelRT::Transform(TouhouNovelRT::SceneGraph::SimpleScene::WorldOrigin, 0.0f, NovelRT::Maths::GeoVector<float>::one() * 50.0f);
  auto playerNode = std::make_shared<TouhouNovelRT::SceneGraph::PlayerNode>(std::shared_ptr(std::move(runner->getRenderer().lock()->createBasicFillRect(transform, 1, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255)))));

  auto factory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(100.0f, 100.0f), NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 2, true);
  auto spellcardFactory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(100.0f, 100.0f), NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 2, std::vector<std::string>());
  spellcardFactory.setIsFill(true);
  auto reimuSpellcard = std::make_shared<TouhouNovelRT::Bullets::ReimuSpellcard>(std::make_shared<TouhouNovelRT::Bullets::Emitter>(400.0f, 2.0f, runner, playerNode, spellcardFactory));
  auto coll = std::vector<std::shared_ptr<TouhouNovelRT::Bullets::Emitter>> { std::make_shared<TouhouNovelRT::Bullets::Emitter>(1800.0f, 0.05f, runner, playerNode, factory) };
  auto playerGun = TouhouNovelRT::Player::Gun(coll, std::shared_ptr<TouhouNovelRT::Bullets::PlayerSpellcard>(reimuSpellcard));
  auto controller = TouhouNovelRT::Player::Controller(playerGun, runner.get(), runner->getInteractionService(), playerNode);

  runner->SceneConstructionRequested += [&] {
    playerNode->getRenderObject()->executeObjectBehaviour();
    controller.getGunHandler().invokeSceneConstruction();
  };

  return runner->runNovel();
}
