// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <TouhouNovelRT.h>

int main(int argc, char* argv[]) {

  //Get path
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
  std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";
  std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";

  //Activate systems
  auto runner = std::make_shared<NovelRT::NovelRunner>(0, "TouhouNovelRT - Service Menu");
  auto scene = std::make_unique<TouhouNovelRT::SceneGraph::SimpleScene>(runner, "", "", false);
  auto audio = runner->getAudioService();
  audio.lock()->initializeAudio();


  //Create Input vars
  auto buttonUp = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::UpArrow);
  auto buttonDown = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::DownArrow);
  auto buttonLeft = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::LeftArrow);
  auto buttonRight = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::RightArrow);
  auto buttonSelect = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::Spacebar);

  //Creating necessary vars
  auto state = 0;
  auto previousState = 0;
  int selection = 0;
  NovelRT::Audio::SoundBank::iterator bgm;
  bool loadingMusic = false;

  auto mid = 1920.0f / 2.0f;
  auto titleY = 1080.0f / 8.0f;
  auto titleOff = titleY + 20.0f;

  //Creating Transforms
  auto titleTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f / 4.0f) + 85.0f, titleY), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto inputTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid - 50.0f, titleOff * 2.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto screenTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid - 115.0f, titleOff * 2.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto colourTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid - 115.0f, titleOff * 3.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto soundTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid - 105.0f, titleOff * 3.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto screenTestTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid, titleY * 4.0f), 0, NovelRT::Maths::GeoVector<float>(1920, 1080));
  auto redExitTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((mid / 2.5f), titleY * 7.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto whiteExitTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((mid)-.0f, titleY * 7.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto loadingTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f/3.0f)-20.0f, titleY * 4.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto hearSoundTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>(mid - 105.0f, titleOff * 3.5f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));

  //Create UI Objects
  auto menuTitle = runner->getRenderer().lock()->createTextRect(titleTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 32.0f, (fontsDirPath / "2P.ttf").string());
  auto inputOutput = runner->getRenderer().lock()->createTextRect(inputTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto screenOutput = runner->getRenderer().lock()->createTextRect(screenTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto colourOutput = runner->getRenderer().lock()->createTextRect(colourTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto soundOutput = runner->getRenderer().lock()->createTextRect(soundTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());
  auto redExit = runner->getRenderer().lock()->createTextRect(redExitTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 0, 0, 255), 52.0f, (fontsDirPath / "2P.ttf").string());
  auto whiteExit = runner->getRenderer().lock()->createTextRect(whiteExitTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 52.0f, (fontsDirPath / "2P.ttf").string());
  auto loading = runner->getRenderer().lock()->createTextRect(loadingTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 96.0f, (fontsDirPath / "2P.ttf").string());
  auto hearSound = runner->getRenderer().lock()->createTextRect(hearSoundTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 30.0f, (fontsDirPath / "2P.ttf").string());


  //Setting UI Text
  menuTitle->setText("Touhou-NovelRT Service Menu");
  inputOutput->setText("IO Test");  //0
  screenOutput->setText("Screen Test"); //1
  colourOutput->setText("Colour Test"); //2
  soundOutput->setText("Sound Test"); //3
  redExit->setText("Press 'Select' to cancel");
  whiteExit->setText("Exit");
  loading->setText("Loading...");
  hearSound->setText("Playing Music.");


  //Activating images and deactivating unnecessary menus
  auto screenTest = runner->getRenderer().lock()->createImageRect(screenTestTransform, 1, (imagesDirPath / "testpattern.png").string(), NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
  auto colourTest = runner->getRenderer().lock()->createImageRect(screenTestTransform, 1, (imagesDirPath / "colortest.png").string(), NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
  screenTest->setActive(false);
  colourTest->setActive(false);
  redExit->setActive(false);
  whiteExit->setActive(false);
  loading->setActive(false);
  hearSound->setActive(false);

  runner->SceneConstructionRequested += [&]() {
    scene->drawObjects();
    menuTitle->executeObjectBehaviour();
    inputOutput->executeObjectBehaviour();
    screenOutput->executeObjectBehaviour();
    colourOutput->executeObjectBehaviour();
    soundOutput->executeObjectBehaviour();
    screenTest->executeObjectBehaviour();
    colourTest->executeObjectBehaviour();
    redExit->executeObjectBehaviour();
    whiteExit->executeObjectBehaviour();
    loading->executeObjectBehaviour();
    hearSound->executeObjectBehaviour();
  };

  runner->Update += [&](double delta) {
    //update input

    //input checks
    if (buttonSelect == NovelRT::Input::KeyState::KeyDown) {
      // 0 = main, 1 = io, 2 = screen, 3 = colour, 4 = sound

      //If we are not in the Main Menu
      if (state != 0)
      {
        if (redExit->getActive()) redExit->setActive(false);
        if (whiteExit->getActive()) whiteExit->setActive(false);
        switch (state) {
        case 5:
        case 4: {
          selection = 3;

          audio.lock()->stopMusic();

          audio.lock()->unloadMusic(*bgm);
          //audio.lock()->unloadSound(sfxOne);

          hearSound->setActive(false);

          menuTitle->setActive(true);
          inputOutput->setActive(true);
          screenOutput->setActive(true);
          colourOutput->setActive(true);
          soundOutput->setActive(true);
          break; }
        case 3: {
          colourTest->setActive(false);
          selection = 2;

          menuTitle->setActive(true);
          inputOutput->setActive(true);
          screenOutput->setActive(true);
          colourOutput->setActive(true);
          soundOutput->setActive(true);
          break; }
        case 2: {
          screenTest->setActive(false);
          selection = 1;

          menuTitle->setActive(true);
          inputOutput->setActive(true);
          screenOutput->setActive(true);
          colourOutput->setActive(true);
          soundOutput->setActive(true);
          break; }
        case 1: {
          selection = 0;

          menuTitle->setActive(true);
          inputOutput->setActive(true);
          screenOutput->setActive(true);
          colourOutput->setActive(true);
          soundOutput->setActive(true);
          break; }
        default: break;
        }

        state = previousState;
        previousState = 0;
      }
      else {
        //If we're in the Main Menu
        switch (selection) {
        case 0: {
          previousState = state;
          state = 1;

          whiteExit->setActive(true);
          std::cout << "ioTest" << std::endl;
          break; }
        case 1: {
          previousState = state;
          state = 2;
          screenTest->setActive(true);
          redExit->setActive(true);
          std::cout << "screenTest" << std::endl;
          break; }
        case 2: {
          previousState = state;
          state = 3;
          colourTest->setActive(true);
          redExit->setActive(true);
          std::cout << "colourTest" << std::endl;
          break; }
        case 3: {
          previousState = state;
          loading->setActive(true);
          loadingMusic = true;
          std::cout << "state " << state << std::endl;
          selection++;
          break; }
        case 4: {
          state = 4;
          std::cout << "loading..." << std::endl;
          bgm = audio.lock()->loadMusic((soundsDirPath / "marisa.ogg").string());
          loading->setActive(false);
          std::cout << "soundTest 2" << std::endl;
          hearSound->setActive(true);
          redExit->setActive(true);
          audio.lock()->playMusic(bgm, -1);
          selection++;
          break; }
        case 5: {
          std::cout << "play" << std::endl;
          
          selection++;
          break;
        }
        case 6: {
          break;
        }
        }//end switch

        //Turn off Main Menu
        menuTitle->setActive(false);
        inputOutput->setActive(false);
        screenOutput->setActive(false);
        colourOutput->setActive(false);
        soundOutput->setActive(false);
      } //end else

      
    } else {
      if (state == 0) {
        //If Down, increase Menu Selection for nav.
        if (buttonDown == NovelRT::Input::KeyState::KeyDown) {
          selection++;
          if (selection > 4) selection = 3;
        }
        //If Up, decrease for nav.
        else if (buttonUp == NovelRT::Input::KeyState::KeyDown) {
          selection--;
          if (selection < 0) selection = 0;
        }
      }
    }
    //end input check


    //red text selection
    switch (selection) {
    case 3: {
      soundOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));
      inputOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      screenOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      colourOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      break;
    }
    case 2: {
      inputOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      screenOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      colourOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));
      soundOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      break;
    }
    case 1: {
      inputOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      screenOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));
      colourOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      soundOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      break;
    }
    case 0:
    default: {
      soundOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      inputOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));
      screenOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      colourOutput->setColourConfig(NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
      }
    }

    //Update button states
    buttonUp = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::UpArrow);
    buttonDown = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::DownArrow);
    buttonLeft = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::LeftArrow);
    buttonRight = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::RightArrow);
    buttonSelect = runner->getInteractionService().lock()->getKeyState(NovelRT::Input::KeyCode::Spacebar);

    };
    
  return runner->runNovel();
}




/*
  auto titleTransform = NovelRT::Transform(NovelRT::Maths::GeoVector<float>((1920.0f/4.0f)*1.5f, 1080.0f / 2.0f), 0, NovelRT::Maths::GeoVector<float>(500.0f, 500.0f));
  auto menuTitle = runner->getRenderer().lock()->createTextRect(titleTransform, 0,
    NovelRT::Graphics::RGBAConfig(255, 255, 255, 255), 32.0f, (fontsDirPath / "2P.ttf").string());
  menuTitle->setText("Touhou-NovelRT Service Menu");*/
