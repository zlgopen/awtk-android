﻿/**
 * File:   font.c
 * Author: AWTK Develop Team
 * Brief:  font interface
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
 * 2018-01-13 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "base/font.h"

ret_t font_get_glyph(font_t* f, wchar_t chr, font_size_t font_size, glyph_t* g) {
  return_value_if_fail(f != NULL && f->get_glyph != NULL && g != NULL, RET_BAD_PARAMS);

  return f->get_glyph(f, chr, font_size, g);
}

int32_t font_get_baseline(font_t* f, font_size_t font_size) {
  if (f != NULL && f->get_baseline != NULL) {
    return f->get_baseline(f, font_size);
  } else {
    return font_size;
  }
}

bool_t font_match(font_t* f, const char* name, font_size_t font_size) {
  return_value_if_fail(f != NULL && f->match != NULL, FALSE);

  return f->match(f, name, font_size);
}

ret_t font_destroy(font_t* f) {
  return_value_if_fail(f != NULL && f->destroy != NULL, RET_BAD_PARAMS);

  return f->destroy(f);
}

glyph_t* glyph_create(void) {
  return TKMEM_ZALLOC(glyph_t);
}

glyph_t* glyph_clone(glyph_t* old) {
  glyph_t* g = NULL;
  return_value_if_fail(old != NULL, NULL);

  g = glyph_create();
  return_value_if_fail(g != NULL, NULL);
  *g = *old;

  return g;
}

ret_t glyph_destroy(glyph_t* g) {
  return_value_if_fail(g != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(g);

  return RET_OK;
}
