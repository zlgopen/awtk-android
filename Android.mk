LOCAL_PATH := $(call my-dir)

###########################
#
# AWTK shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := awtk

LOCAL_MODULE_FILENAME := libawtk

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/glad
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/nanovg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/nanovg/gl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/nanovg/base
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/SDL/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/libunibreak/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src/ext_widgets

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
        $(LOCAL_PATH)/3rd/SDL/src/hidapi/android/hid.cpp \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/audio/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/audio/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/audio/dummy/*.c) \
	$(LOCAL_PATH)/3rd/SDL/src/atomic/SDL_atomic.c.arm \
	$(LOCAL_PATH)/3rd/SDL/src/atomic/SDL_spinlock.c.arm \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/core/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/cpuinfo/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/dynapi/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/events/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/file/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/haptic/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/haptic/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/joystick/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/joystick/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/joystick/hidapi/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/loadso/dlopen/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/power/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/power/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/filesystem/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/sensor/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/sensor/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/render/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/render/*/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/stdlib/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/thread/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/thread/pthread/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/timer/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/timer/unix/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/video/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/video/android/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/SDL/src/video/yuv2rgb/*.c) 

LOCAL_SRC_FILES += \
	$(wildcard $(LOCAL_PATH)/3rd/libunibreak/*.c) \
	$(wildcard $(LOCAL_PATH)/3rd/nanovg/base/*.c) \
	$(wildcard $(LOCAL_PATH)/src/tkc/*.c) \
	$(wildcard $(LOCAL_PATH)/src/base/*.c) \
	$(wildcard $(LOCAL_PATH)/src/layouters/*.c) \
	$(wildcard $(LOCAL_PATH)/src/widgets/*.c) \
	$(wildcard $(LOCAL_PATH)/src/ui_loader/*.c) \
	$(wildcard $(LOCAL_PATH)/src/xml/*.c) \
	$(wildcard $(LOCAL_PATH)/src/svg/*.c) \
	$(wildcard $(LOCAL_PATH)/src/blend/*.c) \
	$(wildcard $(LOCAL_PATH)/src/clip_board/*.c) \
	$(wildcard $(LOCAL_PATH)/src/font_loader/*.c) \
	$(wildcard $(LOCAL_PATH)/src/ext_widgets/*.c) \
	$(wildcard $(LOCAL_PATH)/src/ext_widgets/*/*.c) \
	$(wildcard $(LOCAL_PATH)/src/image_loader/*.c) \
	$(wildcard $(LOCAL_PATH)/src/widget_animators/*.c) \
	$(wildcard $(LOCAL_PATH)/src/window_animators/*.c) \
	$(wildcard $(LOCAL_PATH)/src/dialog_highlighters/*.c) \
	$(wildcard $(LOCAL_PATH)/src/*.c) \
	$(wildcard $(LOCAL_PATH)/src/input_methods/*.c) \
	$(wildcard $(LOCAL_PATH)/src/lcd/lcd_nanovg.c) \
	$(wildcard $(LOCAL_PATH)/src/main_loop/main_loop_simple.c) \
	$(wildcard $(LOCAL_PATH)/src/main_loop/main_loop_sdl_gpu.c) \
	$(wildcard $(LOCAL_PATH)/src/platforms/pc/*.c) \
	$(wildcard $(LOCAL_PATH)/src/vgcanvas/vgcanvas_nanovg_gl.c)

LOCAL_SHORT_COMMANDS=true
LOCAL_CFLAGS += -DLINUX -DWITH_STB_FONT -DWITH_NULL_IM -DWITHOUT_GLAD 
LOCAL_CFLAGS += -DSTBTT_STATIC -DSTB_IMAGE_STATIC -DWITH_STB_IMAGE 
LOCAL_CFLAGS += -DWITH_VGCANVAS -DWITH_UNICODE_BREAK -DWITH_DESKTOP_STYLE 
LOCAL_CFLAGS += -DSDL2 -DHAS_STD_MALLOC -DWITH_SDL -DWITH_FS_RES -DHAS_STDIO 
LOCAL_CFLAGS += -DWITH_NANOVG_GPU -DWITH_VGCANVAS_LCD 
LOCAL_CFLAGS += -DWITH_NANOVG_GLES2 -DWITH_NANOVG_GL 
LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES 
LOCAL_CFLAGS += -DSDL_VIDEO_OPENGL_EGL -DSDL_VIDEO_OPENGL_ES2
LOCAL_CFLAGS += -DSDL_TIMER_UNIX -DHAS_PTHREAD 

LOCAL_CPP_EXTENSION := .cxx .cpp .cc
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
LOCAL_EXPORT_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)

