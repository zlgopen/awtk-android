# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

project(awtk_napi)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(PLUGINS_SOURCE_DIR "plugins")
set(SDL2_SOURCE_DIR "awtk/3rd/SDL")

include(awtk_common.mk)
	
file(GLOB SOURCE_FILES
  ${SDL2_SOURCE_DIR}/src/hidapi/android/hid.cpp 
	${SDL2_SOURCE_DIR}/src/audio/android/*.c
	${SDL2_SOURCE_DIR}/src/core/android/*.c
	${SDL2_SOURCE_DIR}/src/haptic/android/*.c
	${SDL2_SOURCE_DIR}/src/joystick/android/*.c
	${SDL2_SOURCE_DIR}/src/power/android/*.c
	${SDL2_SOURCE_DIR}/src/filesystem/android/*.c
	${SDL2_SOURCE_DIR}/src/sensor/android/*.c
	${SDL2_SOURCE_DIR}/src/video/android/*.c
	${AWTK_COMMON_SOURCE_FILES}
	${AWTK_SDL_COMMON_SOURCE_FILES}
	${AWTK_VGCANVAS_NANOVG_PLUS_SOURCE_FILES}
  ${PLUGINS_SOURCE_DIR}/**/*.c
  ${PLUGINS_SOURCE_DIR}/**/*.cpp
)

include_directories(${SDL2_SOURCE_DIR}/include
  ${AWTK_COMMON_INCLUDES}
  ${AWTK_NANOVG_PLUS_INCLUDES}
  ${PLUGINS_SOURCE_DIR}
  EXTRA_INCLUDES
)

#set(CMAKE_C_FLAGS "-Os ")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")

set(AWTK_ANDROID_FLAGS " -DANDROID -DLINUX -Os ${AWTK_VGCANVAS_NANOVG_PLUS_GLES2_FLAGS}")
set(SDL_FLAGS "-DSDL2 -DWITH_SDL -DSDL_VIDEO_OPENGL_EGL -DSDL_VIDEO_OPENGL_ES2  -DSDL_TIMER_UNIX  -DGL_GLEXT_PROTOTYPES ")
set(AWTK_FLAGS "${AWTK_COMMON_FLAGS} ${AWTK_ANDROID_FLAGS} ${SDL_FLAGS}")
set(CMAKE_C_FLAGS "${AWTK_FLAGS} EXTRA_CFLAGS")
set(CMAKE_CXX_FLAGS "--std=c++17 ${AWTK_FLAGS} EXTRA_CPPFLAGS")

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
add_library(app SHARED ${AWTK_APP_SOURCE_FILES})
target_link_libraries(app ${ANDROID_LIBS} awtk)

