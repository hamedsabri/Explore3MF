include(Source/CMakeLists.txt)

add_library(lib3MF STATIC ${SRCS_COMMON})

target_include_directories(lib3MF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_include_directories(lib3MF PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Include)

if(MSVC)
    target_compile_options(lib3MF PUBLIC "$<$<CONFIG:DEBUG>:/Od;/Ob0;/Gm;/sdl;/W3;/WX;/FC;/wd4996>")
    target_compile_options(lib3MF PUBLIC "$<$<CONFIG:RELEASE>:/O2;/sdl;/WX;/Oi;/Gy;/FC;/wd4996>")
endif()
