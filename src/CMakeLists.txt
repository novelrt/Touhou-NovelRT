find_package(Freetype REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(libpng CONFIG REQUIRED)
find_package(LibSndFile CONFIG REQUIRED)
find_package(NovelRT CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(TOUHOU_NOVELRT_HEADERS)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${TOUHOU_NOVELRT_HEADERS})

file(GLOB_RECURSE TOUHOU_NOVELRT_SOURCES CONFIGURE_DEPENDS *.cpp)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${TOUHOU_NOVELRT_SOURCES})

set(TOUHOU_NOVELRT_LINK_LIBRARIES
    NovelRT::NovelRT
)

add_executable(TouhouNovelRT ${TOUHOU_NOVELRT_HEADERS} ${TOUHOU_NOVELRT_SOURCES})
target_link_libraries(TouhouNovelRT ${TOUHOU_NOVELRT_LINK_LIBRARIES})

file(GLOB_RECURSE NOVELRT_RESOURCE_INPUTS CONFIGURE_DEPENDS
  "${NovelRT_DIR}/../../Resources/Fonts/*.ttf"
  "${NovelRT_DIR}/../../Resources/Images/*.png"
  "${NovelRT_DIR}/../../Resources/Scripts/*.lua"
  "${NovelRT_DIR}/../../Resources/Shaders/*.glsl"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_RESOURCE_INPUTS})

set(NOVELRT_RESOURCE_OUTPUTS
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTResources.txt
)

add_custom_command(OUTPUT ${NOVELRT_RESOURCE_OUTPUTS}
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${NovelRT_DIR}/../../Resources" $<TARGET_FILE_DIR:TouhouNovelRT>/Resources
  COMMAND ${CMAKE_COMMAND} -E touch ${NOVELRT_RESOURCE_OUTPUTS}
  DEPENDS ${NOVELRT_RESOURCE_INPUTS}
)

add_custom_target(NovelRTResources ALL DEPENDS ${NOVELRT_RESOURCE_OUTPUTS} SOURCES ${NOVELRT_RESOURCE_INPUTS})

install(TARGETS TouhouNovelRT
        EXPORT TouhouNovelRTTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY "$<TARGET_FILE_DIR:TouhouNovelRT>/Resources"
        DESTINATION bin/Resources
)
