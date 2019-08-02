﻿/**
 * File:   widget_animator_move.h
 * Author: AWTK Develop Team
 * Brief:  animate widget by change its x/y(just wrap widget_animator_prop2)
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
 * 2018-05-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_WIDGET_ANIMATOR_MOVE_H
#define TK_WIDGET_ANIMATOR_MOVE_H

#include "widget_animators/widget_animator_prop2.h"

BEGIN_C_DECLS

#define widget_animator_move_create(widget, duration, delay, easing) \
  widget_animator_prop2_create(widget, duration, delay, easing, WIDGET_PROP_X, WIDGET_PROP_Y)

#define widget_animator_move_set_params widget_animator_prop2_set_params

END_C_DECLS

#endif /*TK_WIDGET_ANIMATOR_MOVE_H*/
