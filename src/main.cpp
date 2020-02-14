// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

int main(int argc, char *argv[]) {
  auto runner = NovelRT::NovelRunner(0, "TouhouNovelRT");
  runner.runNovel();
  return 0;
}
