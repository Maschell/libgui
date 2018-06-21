cmake_minimum_required(VERSION 3.2)
project(gui)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h*)

add_library(gui STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(gui
                      utilswut)

                      
include_directories("$ENV{WUT_ROOT}/include/libutils" REQUIRED)
include_directories("$ENV{DEVKITPRO}/portlibs/ppc/include" REQUIRED)
include_directories("$ENV{DEVKITPRO}/portlibs/ppc/include/freetype2" REQUIRED)
                      
target_include_directories(gui PUBLIC "include")
target_include_directories(gui PRIVATE "src")

wut_enable_stdcpp(gui)
wut_default_malloc(gui)

target_include_directories(gui PUBLIC "include")
target_compile_options(gui PUBLIC "-D__LOGGING__")

install(TARGETS gui
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libgui"
        FILES_MATCHING PATTERN "*.h*")