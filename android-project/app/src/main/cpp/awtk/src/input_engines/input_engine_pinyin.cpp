﻿/**
 * File:   input_engine_pinyin.c
 * Author: AWTK Develop Team
 * Brief:  pinyin input method engine
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
 * 2018-06-23 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utf8.h"
#include "tkc/buffer.h"
#include "base/input_engine.h"

#include "pinyinime.h"

#define MAX_WORD_LEN 32

using namespace ime_pinyin;
static ret_t input_engine_pinyin_reset_input(input_engine_t* engine) {
  (void)engine;
  im_reset_search();

  return RET_OK;
}

static ret_t input_engine_pinyin_add_candidate(input_engine_t* engine, wbuffer_t* wb,
                                               uint32_t index) {
  uint32_t i = 0;
  char str[MAX_WORD_LEN * 2 + 1];
  char16 str16[MAX_WORD_LEN + 1];
  wchar_t wstr[MAX_WORD_LEN + 1];
  im_get_candidate(index, str16, MAX_WORD_LEN);

  str16[MAX_WORD_LEN] = 0;
  while (str16[i] && i < MAX_WORD_LEN) {
    wstr[i] = str16[i];
    i++;
  }
  wstr[i] = 0;

  utf8_from_utf16(wstr, str, sizeof(str) - 1);

  if ((wb->cursor + strlen(str) + 1) >= wb->capacity) {
    return RET_FAIL;
  }

  return wbuffer_write_string(wb, str);
}

static ret_t input_engine_pinyin_input(input_engine_t* engine, int c) {
  uint32_t i = 0;
  wbuffer_t wb;
  uint32_t nr = im_search(engine->keys.str, engine->keys.size);
  wbuffer_init(&wb, (uint8_t*)(engine->candidates), sizeof(engine->candidates));

  wbuffer_write_string(&wb, engine->keys.str);
  engine->candidates_nr = 1;

  for (i = 0; i < nr; i++) {
    if (input_engine_pinyin_add_candidate(engine, &wb, i) == RET_OK) {
      engine->candidates_nr++;
    } else {
      break;
    }
  }

  (void)c;

  return RET_OK;
}

input_engine_t* input_engine_create(void) {
  input_engine_t* engine = TKMEM_ZALLOC(input_engine_t);
  return_value_if_fail(engine != NULL, NULL);

  str_init(&(engine->keys), TK_IM_MAX_INPUT_CHARS + 1);
  engine->reset_input = input_engine_pinyin_reset_input;
  engine->input = input_engine_pinyin_input;

  im_open_decoder_rom();
  im_set_max_lens(32, 16);

  return engine;
}

ret_t input_engine_destroy(input_engine_t* engine) {
  return_value_if_fail(engine != NULL, RET_BAD_PARAMS);
  str_reset(&(engine->keys));
  im_close_decoder();
  TKMEM_FREE(engine);

  return RET_OK;
}
