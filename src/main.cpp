// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
  std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";
  std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";

  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT");
  auto scene = std::make_unique<TouhouNovelRT::SceneGraph::SimpleScene>(runner, "", "", false);
  auto audio = runner->getAudioService();
  audio.lock()->initializeAudio();

  auto titleTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f/4.0f)*1.5f, 1080.0f / 2.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto menuTitle = runner->getRenderer().lock()->createTextRect(titleTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 32.0f, (fontsDirPath / "2P.ttf").string());
  menuTitle->setText("Touhou-NovelRT Service Menu");

  runner->SceneConstructionRequested += [&]() {
    scene->drawObjects();
    menuTitle->executeObjectBehaviour();
  };

  return runner->runNovel();
}
