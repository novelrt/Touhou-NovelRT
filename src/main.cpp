// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char *argv[]) {
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
  std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";
  std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";

  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT - Service Menu");
  auto scene = std::make_unique<TouhouNovelRT::SceneGraph::SimpleScene>(runner, "", "", false);
  auto audio = runner->getAudioService();
  audio.lock()->initializeAudio();

  //howToUseMagicNumbers.exe
  auto state = 0;
  auto selection = 0;

  auto titleY = 1080.0f / 8.0f;
  auto titleOff = titleY + 20.0f;

  //Don't do this ever again plz.
  auto titleTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f / 4.0f)+85, titleY), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto inputTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f / 2.0f)-50, titleOff*2.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto screenTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f / 2.0f) - 115, titleOff * 2.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto colourTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f / 2.0f) - 115, titleOff * 3.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));

  //Don't do this part 2 - the Remix.
  auto menuTitle = runner->getRenderer().lock()->createTextRect(titleTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 32.0f, (fontsDirPath / "2P.ttf").string());
  auto inputOutput = runner->getRenderer().lock()->createTextRect(inputTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto screenOutput = runner->getRenderer().lock()->createTextRect(screenTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto colourOutput = runner->getRenderer().lock()->createTextRect(colourTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());

  //Don't do this part 3 - the Trilogy.
  menuTitle->setText("Touhou-NovelRT Service Menu");
  inputOutput->setText("IO Test");
  screenOutput->setText("Screen Test");
  colourOutput->setText("Colour Test");
  


  runner->SceneConstructionRequested += [&]() {
    scene->drawObjects();
    menuTitle->executeObjectBehaviour();
    inputOutput->executeObjectBehaviour();
    screenOutput->executeObjectBehaviour();
    colourOutput->executeObjectBehaviour();
  };

  return runner->runNovel();
}




/*
  auto titleTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f/4.0f)*1.5f, 1080.0f / 2.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto menuTitle = runner->getRenderer().lock()->createTextRect(titleTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 32.0f, (fontsDirPath / "2P.ttf").string());
  menuTitle->setText("Touhou-NovelRT Service Menu");*/
