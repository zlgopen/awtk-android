﻿/**
 * File:   bsvg.h
 * Author: AWTK Develop Team
 * Brief:  bsvg
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
 * 2018-11-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_BSVG_H
#define TK_BSVG_H

#include "svg/svg_shape.h"
#include "svg/bsvg_common.h"

BEGIN_C_DECLS

typedef struct _bsvg_t {
  uint32_t size;
  const uint32_t* data;
  bsvg_header_t* header;
} bsvg_t;

const uint8_t* bsvg_visit_path(const uint8_t* p, void* ctx, tk_visit_t on_path);
bsvg_t* bsvg_init(bsvg_t* svg, const uint32_t* data, uint32_t size);
ret_t bsvg_visit(bsvg_t* svg, void* ctx, tk_visit_t on_shape, tk_visit_t on_path);

/*for test*/
const svg_shape_t* bsvg_get_first_shape(bsvg_t* svg);

END_C_DECLS

#endif /*TK_BSVG_H*/
