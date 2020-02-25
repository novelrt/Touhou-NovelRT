// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";

  auto borderPath = (imagesDirPath / "background/default.png");
  auto bkPath = imagesDirPath / "background/default_spell1.png";

  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT");
  auto scene = std::make_unique<TouhouNovelRT::SceneGraph::SimpleScene>(runner, bkPath.string(), borderPath.string(), true);

  auto playerTransform = NovelRT::Transform(TouhouNovelRT::SceneGraph::SimpleScene::WorldOrigin, 0.0f, NovelRT::Maths::GeoVector<float>(95 * 2, 98 * 2));
  auto playerNode = std::make_shared<TouhouNovelRT::SceneGraph::PlayerNode>(runner, std::shared_ptr(std::move(runner->getRenderer().lock()->createImageRect(playerTransform, 3, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255)))));
  scene->insert(playerNode);

  auto factory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(100.0f, 100.0f), NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 2, true);
  auto spellcardFactory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(100.0f, 100.0f), NovelRT::Graphics::RGBAConfig(0, 255, 0, 255), 2, std::vector<std::string>());
  spellcardFactory.setIsFill(true);
  auto reimuSpellcard = std::make_shared<TouhouNovelRT::Bullets::ReimuSpellcard>(std::make_shared<TouhouNovelRT::Bullets::Emitter>(400.0f, 2.0f, runner, playerNode, spellcardFactory));
  auto coll = std::vector<std::shared_ptr<TouhouNovelRT::Bullets::Emitter>> { std::make_shared<TouhouNovelRT::Bullets::Emitter>(1800.0f, 0.05f, runner, playerNode, factory) };
  auto playerGun = TouhouNovelRT::Player::Gun(coll, std::shared_ptr<TouhouNovelRT::Bullets::PlayerSpellcard>(reimuSpellcard));
  auto controller = TouhouNovelRT::Player::Controller(playerGun, runner.get(), runner->getInteractionService(), playerNode);

  auto bossSpellcard = TouhouNovelRT::Bullets::BossSpellcard(runner, TouhouNovelRT::Bullets::BossSpellcardBulletStageData(std::vector<TouhouNovelRT::Bullets::BulletWaveData>{TouhouNovelRT::Bullets::BulletWaveData(std::map<size_t, std::vector<TouhouNovelRT::Bullets::BulletInstanceConfig>>{ {0, std::vector<TouhouNovelRT::Bullets::BulletInstanceConfig>{ TouhouNovelRT::Bullets::BulletInstanceConfig(NovelRT::Maths::GeoVector<float>(0.0f, 1.0f), NovelRT::Maths::GeoVector<float>(200.0f, 200.0f), 0.0f, 100.0f)  }} }, 1) }, coll));
  bossSpellcard.activate();

  runner->SceneConstructionRequested += [&] {
    controller.getGunHandler().invokeSceneConstruction();
    scene->drawObjects();
  };

  return runner->runNovel();
}
