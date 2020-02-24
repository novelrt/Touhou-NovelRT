// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef TOUHOUNOVELRT_WORLD_SCENE_H
#define TOUHOUNOVELRT_WORLD_SCENE_H

#ifndef TOUHOUNOVELRT_H
#error Please do not include this directly. Use the centralised header (TouhouNovelRT.h) instead!
#endif

namespace TouhouNovelRT::World {
  class Scene {
  private:
    std::weak_ptr<NovelRT::NovelRunner> _runner;
    const float _screenWidth = 1920;
    const float _screenHeight = 1080;
    bool _isScrolling;
    std::vector<NovelRT::WorldObject> _sceneObjects;
    NovelRT::Transform _backgroundTransform;
    NovelRT::Transform _secondBkgdTransform;
    NovelRT::Transform _borderTransform;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _backgroundImage;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _secondBkgdImage;
    std::unique_ptr<NovelRT::Graphics::ImageRect> _borderImage;

    void updateBackground(double delta);

  public:
    Scene(std::weak_ptr<NovelRT::NovelRunner> runner, std::string backgroundFile, std::string borderFile, bool isScrolling);
    void drawObjects();
  };
}

#endif //!TOUHOUNOVELRT_WORLD_SCENE_H
