/**
 * File:   window_animator_slide_left.h
 * Author: AWTK Develop Team
 * Brief:  slide_left window animator
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
 * 2019-03-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "base/window_animator.h"

#ifndef TK_WINDOW_ANIMATOR_SLIDE_LEFT_H
#define TK_WINDOW_ANIMATOR_SLIDE_LEFT_H

BEGIN_C_DECLS

window_animator_t* window_animator_slide_left_create(bool_t open, object_t* args);

END_C_DECLS

#endif /*TK_WINDOW_ANIMATOR_SLIDE_LEFT_H*/
