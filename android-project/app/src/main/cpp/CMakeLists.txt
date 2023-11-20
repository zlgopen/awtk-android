# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(APP_SOURCE_DIR "app")
set(PLUGINS_SOURCE_DIR "plugins")
set(AWTK_SOURCE_DIR "awtk")
set(SDL2_SOURCE_DIR "awtk/3rd/SDL")

file(GLOB SOURCE_FILES
  ${SDL2_SOURCE_DIR}/src/hidapi/android/hid.cpp 
	${SDL2_SOURCE_DIR}/src/*.c
	${SDL2_SOURCE_DIR}/src/audio/*.c
	${SDL2_SOURCE_DIR}/src/audio/android/*.c
	${SDL2_SOURCE_DIR}/src/audio/dummy/*.c
	${SDL2_SOURCE_DIR}/src/atomic/*.c
	${SDL2_SOURCE_DIR}/src/core/android/*.c
	${SDL2_SOURCE_DIR}/src/cpuinfo/*.c
	${SDL2_SOURCE_DIR}/src/dynapi/*.c
	${SDL2_SOURCE_DIR}/src/events/*.c
	${SDL2_SOURCE_DIR}/src/file/*.c
	${SDL2_SOURCE_DIR}/src/haptic/*.c
	${SDL2_SOURCE_DIR}/src/haptic/android/*.c
	${SDL2_SOURCE_DIR}/src/joystick/*.c
	${SDL2_SOURCE_DIR}/src/joystick/android/*.c
	${SDL2_SOURCE_DIR}/src/joystick/hidapi/*.c
	${SDL2_SOURCE_DIR}/src/loadso/dlopen/*.c
	${SDL2_SOURCE_DIR}/src/power/*.c
	${SDL2_SOURCE_DIR}/src/power/android/*.c
	${SDL2_SOURCE_DIR}/src/filesystem/android/*.c
	${SDL2_SOURCE_DIR}/src/sensor/*.c
	${SDL2_SOURCE_DIR}/src/sensor/android/*.c
	${SDL2_SOURCE_DIR}/src/render/*.c
	${SDL2_SOURCE_DIR}/src/render/*/*.c
	${SDL2_SOURCE_DIR}/src/stdlib/*.c
	${SDL2_SOURCE_DIR}/src/thread/*.c
	${SDL2_SOURCE_DIR}/src/thread/pthread/*.c
	${SDL2_SOURCE_DIR}/src/timer/*.c
	${SDL2_SOURCE_DIR}/src/timer/unix/*.c
	${SDL2_SOURCE_DIR}/src/video/*.c
	${SDL2_SOURCE_DIR}/src/video/android/*.c
	${SDL2_SOURCE_DIR}/src/video/yuv2rgb/*.c
	${AWTK_SOURCE_DIR}/3rd/libunibreak/*.c
	${AWTK_SOURCE_DIR}/3rd/gpinyin/src/*.cpp
	${AWTK_SOURCE_DIR}/3rd/nanovg/base/*.c
	${AWTK_SOURCE_DIR}/src/tkc/*.c
	${AWTK_SOURCE_DIR}/src/base/*.c
	${AWTK_SOURCE_DIR}/src/layouters/*.c
	${AWTK_SOURCE_DIR}/src/widgets/*.c
	${AWTK_SOURCE_DIR}/src/ui_loader/*.c
	${AWTK_SOURCE_DIR}/src/xml/*.c
	${AWTK_SOURCE_DIR}/src/svg/*.c
	${AWTK_SOURCE_DIR}/src/blend/*.c
	${AWTK_SOURCE_DIR}/src/clip_board/*.c
	${AWTK_SOURCE_DIR}/src/font_loader/*.c
    ${AWTK_SOURCE_DIR}/src/graphic_buffer/*.c
	${AWTK_SOURCE_DIR}/src/ext_widgets/*.c
	${AWTK_SOURCE_DIR}/src/ext_widgets/*/*.c
	${AWTK_SOURCE_DIR}/src/custom_widgets/*.c
	${AWTK_SOURCE_DIR}/src/custom_widgets/*/*.c
	${AWTK_SOURCE_DIR}/src/custom_widgets/*.cc
	${AWTK_SOURCE_DIR}/src/custom_widgets/*/*.cc
	${AWTK_SOURCE_DIR}/src/custom_widgets/*.cxx
	${AWTK_SOURCE_DIR}/src/custom_widgets/*/*.cxx
	${AWTK_SOURCE_DIR}/src/custom_widgets/*.cpp
	${AWTK_SOURCE_DIR}/src/custom_widgets/*/*.cpp
	${AWTK_SOURCE_DIR}/src/image_loader/*.c
	${AWTK_SOURCE_DIR}/src/widget_animators/*.c
	${AWTK_SOURCE_DIR}/src/window_animators/*.c
	${AWTK_SOURCE_DIR}/src/window_manager/window_manager_default.c
	${AWTK_SOURCE_DIR}/src/native_window/native_window_sdl.c
	${AWTK_SOURCE_DIR}/src/dialog_highlighters/*.c
	${AWTK_SOURCE_DIR}/src/*.c
	${AWTK_SOURCE_DIR}/src/ubjson/*.c
	${AWTK_SOURCE_DIR}/src/streams/serial/*.c
	${AWTK_SOURCE_DIR}/src/streams/buffered/*.c
	${AWTK_SOURCE_DIR}/src/streams/mem/*.c
	${AWTK_SOURCE_DIR}/src/streams/file/*.c
	${AWTK_SOURCE_DIR}/src/streams/inet/*.c
	${AWTK_SOURCE_DIR}/src/streams/*.c
	${AWTK_SOURCE_DIR}/src/csv/*.c
	${AWTK_SOURCE_DIR}/src/conf_io/*.c
	${AWTK_SOURCE_DIR}/src/fscript_ext/*.c
	${AWTK_SOURCE_DIR}/src/charset/*.c
	${AWTK_SOURCE_DIR}/src/input_methods/*.c
	${AWTK_SOURCE_DIR}/src/input_engines/input_engine_pinyin.cpp
	${AWTK_SOURCE_DIR}/src/lcd/lcd_nanovg.c
	${AWTK_SOURCE_DIR}/src/main_loop/main_loop_simple.c
	${AWTK_SOURCE_DIR}/src/main_loop/main_loop_sdl.c
	${AWTK_SOURCE_DIR}/src/main_loop/main_loop_console.c
	${AWTK_SOURCE_DIR}/src/platforms/pc/*.c
	${AWTK_SOURCE_DIR}/src/vgcanvas/vgcanvas_nanovg_gl.c)

include_directories(${SDL2_SOURCE_DIR}/include
  ${AWTK_SOURCE_DIR}/src
  ${AWTK_SOURCE_DIR}/3rd
  ${AWTK_SOURCE_DIR}/3rd/glad
  ${AWTK_SOURCE_DIR}/3rd/nanovg
  ${AWTK_SOURCE_DIR}/3rd/nanovg/gl
  ${AWTK_SOURCE_DIR}/3rd/nanovg/base
  ${AWTK_SOURCE_DIR}/3rd/gpinyin/include
  ${AWTK_SOURCE_DIR}/3rd/libunibreak
  ${AWTK_SOURCE_DIR}/src/ext_widgets
  ${AWTK_SOURCE_DIR}/src/custom_widgets
  ${PLUGINS_SOURCE_DIR}
  EXTRA_INCLUDES
)

#set(CMAKE_C_FLAGS "-Os ")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")

set(CMAKE_C_FLAGS "-Os -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} EXTRA_CFLAGS")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DANDROID -DMOBILE_APP -DWITH_ASSET_LOADER ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLINUX -DWITH_STB_FONT -DWITHOUT_GLAD ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTBTT_STATIC -DSTB_IMAGE_STATIC -DWITH_STB_IMAGE ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_VGCANVAS -DWITH_UNICODE_BREAK -DWITH_DESKTOP_STYLE ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSDL2 -DHAS_STD_MALLOC -DWITH_SDL -DWITH_FS_RES -DHAS_STDIO ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_NANOVG_GPU -DWITH_VGCANVAS_LCD ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_NANOVG_GLES2 -DWITH_GPU_GLES2 -DWITH_GPU_GL ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGL_GLEXT_PROTOTYPES ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSDL_VIDEO_OPENGL_EGL -DSDL_VIDEO_OPENGL_ES2 ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSDL_TIMER_UNIX -DHAS_PTHREAD ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_DATA_READER_WRITER=1 ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAS_GET_TIME_US64=1 ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} EXTRA_CPPFLAGS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID -DMOBILE_APP -DWITH_ASSET_LOADER ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DWITH_STB_FONT -DWITHOUT_GLAD ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTBTT_STATIC -DSTB_IMAGE_STATIC -DWITH_STB_IMAGE ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_VGCANVAS -DWITH_UNICODE_BREAK -DWITH_DESKTOP_STYLE ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSDL2 -DHAS_STD_MALLOC -DWITH_SDL -DWITH_FS_RES -DHAS_STDIO ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_NANOVG_GPU -DWITH_VGCANVAS_LCD ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_NANOVG_GLES2 -DWITH_GPU_GLES2 -DWITH_GPU_GL ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_GLEXT_PROTOTYPES ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSDL_VIDEO_OPENGL_EGL -DSDL_VIDEO_OPENGL_ES2 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSDL_TIMER_UNIX -DHAS_PTHREAD ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_DATA_READER_WRITER=1 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAS_GET_TIME_US64=1 ")

#if you want use awtk input method instead of android input method please uncomment the following two lines
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_DEFAULT_IM=1 -DWITH_IME_PINYIN=1 ")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_DEFAULT_IM=1 -DWITH_IME_PINYIN=1 ")

if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
elseif(${ANDROID_ABI} STREQUAL "arm64-v8a")
    include_directories(${ANDROID_SYSROOT}/usr/include/aarch64-linux-android)
else()
    include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
endif()

set(ANDROID_LIBS dl m android log EGL OpenSLES GLESv2 GLESv1_CM)

add_library(awtk SHARED ${SOURCE_FILES})
target_link_libraries(awtk ${ANDROID_LIBS})

#hidapi
file(GLOB SOURCE_FILES ${SDL2_SOURCE_DIR}/src/hidapi/android/hid.cpp) 
add_library(hidapi SHARED ${SOURCE_FILES})
target_link_libraries(hidapi ${ANDROID_LIBS})

#application
file(GLOB_RECURSE APP_SOURCE_FILES  
  ${PLUGINS_SOURCE_DIR}/**/*.c
  ${PLUGINS_SOURCE_DIR}/**/*.cpp
  ${APP_SOURCE_DIR}/*.c
  ${APP_SOURCE_DIR}/*.cpp
  ${APP_SOURCE_DIR}/**/*.c
  ${APP_SOURCE_DIR}/**/*.cpp
  )

add_library(app SHARED ${APP_SOURCE_FILES})
target_link_libraries(app ${ANDROID_LIBS} awtk)

