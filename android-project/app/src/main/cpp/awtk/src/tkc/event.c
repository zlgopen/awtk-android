﻿/**
 * File:   event.c
 * Author: AWTK Develop Team
 * Brief:  event structs
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
 * 2018-03-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/event.h"
#include "tkc/time_now.h"

event_t event_init(uint32_t type, void* target) {
  event_t e;

  memset(&e, 0x00, sizeof(e));

  e.type = type;
  e.target = target;
  e.time = time_now_ms();

  return e;
}

event_t* event_cast(event_t* event) {
  return event;
}

prop_change_event_t* prop_change_event_cast(event_t* event) {
  return_value_if_fail(event != NULL, NULL);
  return_value_if_fail(event->type == EVT_PROP_CHANGED || event->type == EVT_PROP_WILL_CHANGE,
                       NULL);

  return (prop_change_event_t*)event;
}

event_t* event_create(uint32_t type, void* target) {
  event_t* e = TKMEM_ZALLOC(event_t);

  return_value_if_fail(e != NULL, NULL);
  *e = event_init(type, target);

  return e;
}

ret_t event_destroy(event_t* event) {
  return_value_if_fail(event != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(event);

  return RET_OK;
}
