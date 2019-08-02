/**
 * File:   vgcanvas_nanovg_gl.c
 * Author: AWTK Develop Team
 * Brief:  vector graphics canvas base on nanovg-gl
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-04-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#if defined(WITH_NANOVG_GL3)
#define NANOVG_GL3_IMPLEMENTATION
#endif

#if defined(WITH_NANOVG_GLES2)
#define NANOVG_GLES2_IMPLEMENTATION
#endif

#if defined(WITH_NANOVG_GLES3)
#define NANOVG_GLES3_IMPLEMENTATION
#endif

#ifndef WITHOUT_GLAD
#include "glad/glad.h"
#endif /*WITHOUT_GLAD*/
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include "nanovg.h"
#include "tkc/utf8.h"
#include "tkc/mem.h"
#include "base/vgcanvas.h"
#include "base/image_manager.h"
#include "base/native_window.h"
#include "base/assets_manager.h"

#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"

typedef struct _vgcanvas_nanovg_t {
  vgcanvas_t base;

  int font_id;
  NVGcontext* vg;
  uint32_t text_align_v;
  uint32_t text_align_h;

  native_window_t* window;
} vgcanvas_nanovg_t;

#include "texture.inc"
#include "vgcanvas_nanovg_gl.inc"
#include "vgcanvas_nanovg.inc"

vgcanvas_t* vgcanvas_create(uint32_t w, uint32_t h, uint32_t stride, bitmap_format_t format,
                            void* win) {
  native_window_info_t info;
  native_window_t* window = NATIVE_WINDOW(win);
  return_value_if_fail(native_window_get_info(win, &info) == RET_OK, NULL);
  vgcanvas_nanovg_t* nanovg = (vgcanvas_nanovg_t*)TKMEM_ZALLOC(vgcanvas_nanovg_t);
  return_value_if_fail(nanovg != NULL, NULL);

  (void)format;

  nanovg->base.w = w;
  nanovg->base.h = h;
  nanovg->base.vt = &vt;
  nanovg->window = window;
  nanovg->base.ratio = info.ratio;

#if defined(WITH_NANOVG_GL3)
  nanovg->vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#elif defined(WITH_NANOVG_GLES2)
  nanovg->vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#elif defined(WITH_NANOVG_GLES3)
  nanovg->vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#endif

  if (nanovg->vg == NULL) {
    assert(!"OpenGL is not supported!");
  }

  return &(nanovg->base);
}
