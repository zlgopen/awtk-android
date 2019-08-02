﻿/**
 * File:   main_loop.c
 * Author: AWTK Develop Team
 * Brief:  main_loop interface
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

#include "tkc/time_now.h"
#include "tkc/platform.h"
#include "base/main_loop.h"
#include "base/window_manager.h"

ret_t main_loop_run(main_loop_t* l) {
  return_value_if_fail(l != NULL && l->run != NULL, RET_BAD_PARAMS);
  l->running = TRUE;

  return l->run(l);
}

ret_t main_loop_quit(main_loop_t* l) {
  return_value_if_fail(l != NULL, RET_BAD_PARAMS);
  l->running = FALSE;

  if (l->quit != NULL) {
    l->quit(l);
    l->app_quited = TRUE;
  }

  return RET_OK;
}

ret_t main_loop_wakeup(main_loop_t* l) {
  return_value_if_fail(l != NULL, RET_BAD_PARAMS);

  if (l->wakeup != NULL) {
    l->wakeup(l);
  }

  return RET_OK;
}

ret_t main_loop_destroy(main_loop_t* l) {
  return_value_if_fail(l != NULL && l->destroy != NULL, RET_BAD_PARAMS);
  l->running = FALSE;

  return l->destroy(l);
}

static main_loop_t* s_default_main_loop = NULL;

main_loop_t* main_loop(void) {
  return s_default_main_loop;
}

ret_t main_loop_set(main_loop_t* loop) {
  s_default_main_loop = loop;

  return RET_OK;
}

ret_t main_loop_queue_event(main_loop_t* l, const event_queue_req_t* e) {
  return_value_if_fail(l != NULL && l->queue_event != NULL && e != NULL, RET_BAD_PARAMS);

  return l->queue_event(l, e);
}

#include "base/idle.h"
#include "base/timer.h"
#include "base/window_manager.h"

#define TK_MAX_SLEEP_TIME (1000 / TK_MAX_FPS)

ret_t main_loop_sleep_default(main_loop_t* l) {
  uint32_t sleep_time = 0;
  uint32_t now = time_now_ms();
  uint32_t gap = now - l->last_loop_time;
  int32_t least_sleep_time = gap > TK_MAX_SLEEP_TIME ? 0 : (TK_MAX_SLEEP_TIME - gap);

#ifdef WITH_SDL
  if (gap <= 8) {
    sleep_time = 8;
  }
#endif /*WITH_SDL*/

  sleep_time = tk_min(least_sleep_time, sleep_time);
  if (sleep_time > 0) {
    sleep_ms(sleep_time);
  }
  l->last_loop_time = time_now_ms();

  return RET_OK;
}

ret_t main_loop_sleep(main_loop_t* l) {
  if (l->sleep != NULL) {
    return l->sleep(l);
  }

  return main_loop_sleep_default(l);
}

ret_t main_loop_step(main_loop_t* l) {
  if (l->step != NULL) {
    return l->step(l);
  }

  return RET_OK;
}
