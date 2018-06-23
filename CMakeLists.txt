cmake_minimum_required(VERSION 3.2)
project(guiwut)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

file(GLOB_RECURSE SOURCE_FILES *.c *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h*)

add_library(guiwut STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(guiwut
                      utilswut)

                      
include_directories("$ENV{WUT_ROOT}/include/libutilswut" REQUIRED)
include_directories("$ENV{DEVKITPRO}/portlibs/ppc/include" REQUIRED)
include_directories("$ENV{DEVKITPRO}/portlibs/ppc/include/freetype2" REQUIRED)
                      
target_include_directories(guiwut PUBLIC "include")
target_include_directories(guiwut PRIVATE "src")

wut_enable_stdcpp(guiwut)
wut_default_malloc(guiwut)

target_include_directories(guiwut PUBLIC "include")
target_compile_options(guiwut PUBLIC "-D__LOGGING__")

install(TARGETS guiwut
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libguiwut"
        FILES_MATCHING PATTERN "*.h*")