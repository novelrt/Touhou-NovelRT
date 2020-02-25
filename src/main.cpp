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

  auto playerTransform = NovelRT::Transform(TouhouNovelRT::SceneGraph::SimpleScene::WorldOrigin, 0.0f, NovelRT::Maths::GeoVector<float>(0.0f, 0.0f));
  auto playerNode = std::make_shared<TouhouNovelRT::SceneGraph::PlayerNode>(runner, std::shared_ptr(std::move(runner->getRenderer().lock()->createImageRect(playerTransform, 3, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255)))));
  scene->insert(playerNode);

  auto playerBulletFactory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(36.0f, 36.0f), NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 2, false, (imagesDirPath / "bullet" / "circle" / "small-17.png").string());
  auto playerBulletEmitter = std::vector<std::shared_ptr<TouhouNovelRT::Bullets::Emitter>>{ std::make_shared<TouhouNovelRT::Bullets::Emitter>(TouhouNovelRT::SceneGraph::SimpleScene::WorldSize.getX() * 0.75f, 1.0f / 15.0f, runner, playerNode, playerBulletFactory) };
  auto playerSpellcardFactory = TouhouNovelRT::Bullets::BulletFactory(runner, NovelRT::Maths::GeoVector<float>(36.0f, 36.0f), NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 2, std::vector<std::string>());
  auto playerSpellcard = std::make_shared<TouhouNovelRT::Bullets::MarisaSpellcard>(std::make_shared<TouhouNovelRT::Bullets::Emitter>(400.0f, 2.0f, runner, playerNode, playerSpellcardFactory));
  auto playerGun = TouhouNovelRT::Player::Gun(playerBulletEmitter, std::shared_ptr<TouhouNovelRT::Bullets::MarisaSpellcard>(playerSpellcard));
  auto playerController = TouhouNovelRT::Player::Controller(playerGun, runner.get(), runner->getInteractionService(), playerNode);

  auto bulletMap = std::map<size_t, std::vector<TouhouNovelRT::Bullets::BulletInstanceConfig>>{
      {
        0, std::vector<TouhouNovelRT::Bullets::BulletInstanceConfig>{
          TouhouNovelRT::Bullets::BulletInstanceConfig(NovelRT::Maths::GeoVector<float>(0.0f, 1.0f), NovelRT::Maths::GeoVector<float>(200.0f, 200.0f), 0.0f, 100.0f)
        }
      },
      {
        0, std::vector<TouhouNovelRT::Bullets::BulletInstanceConfig>{
          TouhouNovelRT::Bullets::BulletInstanceConfig(NovelRT::Maths::GeoVector<float>(0.0f, 1.0f), NovelRT::Maths::GeoVector<float>(200.0f, 200.0f), 0.0f, 100.0f)
        }
      },
  };

  // auto bossSpellcard = TouhouNovelRT::Bullets::BossSpellcard(runner, TouhouNovelRT::Bullets::BossSpellcardBulletStageData(std::vector<TouhouNovelRT::Bullets::BulletWaveData>{TouhouNovelRT::Bullets::BulletWaveData(bulletMap, 1) }, playerBulletEmitter));
  // bossSpellcard.activate();

  runner->SceneConstructionRequested += [&]() {
    scene->drawObjects();
    playerController.getGunHandler().invokeSceneConstruction();
  };

  return runner->runNovel();
}
