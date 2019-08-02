﻿/**
 * File:   time.h
 * Author: AWTK Develop Team
 * Brief:  time
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
 * 2018-04-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/time_now.h"
#include "tkc/platform.h"

uint32_t time_now_ms(void) {
  return get_time_ms();
}

uint32_t time_now_s(void) {
  return get_time_ms() / 1000;
}
