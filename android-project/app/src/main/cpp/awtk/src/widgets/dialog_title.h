﻿/**
 * File:   dialog_title.h
 * Author: AWTK Develop Team
 * Brief:  dialog title
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

#ifndef TK_DIALOG_TITLE_H
#define TK_DIALOG_TITLE_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @class dialog_title_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 对话框标题控件。
 *
 * 它本身不提供布局功能，仅提供具有语义的标签，让xml更具有可读性。
 * 子控件的布局可用layout\_children属性指定。
 * 请参考[布局参数](https://github.com/zlgopen/awtk/blob/master/docs/layout.md)。
 *
 * dialog\_title\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于dialog\_title\_t控件。
 *
 * 在xml中使用"dialog\_title"标签创建dialog\_title。如：
 *
 * ```xml
 * <dialog anim_hint="center_scale(duration=300)" x="c" y="m" w="80%" h="160" text="Dialog">
 * <dialog_title x="0" y="0" w="100%" h="30" text="Hello AWTK" />
 * <dialog_client x="0" y="bottom" w="100%" h="-30">
 *   <label name="" x="center" y="middle:-20" w="200" h="30" text="Are you ready?"/>
 *   <button name="quit" x="10" y="bottom:10" w="40%" h="30" text="确定"/>
 *   <button name="quit" x="right:10" y="bottom:10" w="40%" h="30" text="取消"/>
 * </dialog_client>
 * </dialog>
 * ```
 *
 * 在c代码中，用dialog\_create\_simple创建对话框时，自动创建dialog标题对象。
 *
 */
typedef struct _dialog_title_t {
  widget_t widget;
} dialog_title_t;

/**
 * @method dialog_title_create
 * 创建dialog对象。
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} dialog对象。
 */
widget_t* dialog_title_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method dialog_title_cast
 * 转换为dialog_title对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget dialog_title对象。
 *
 * @return {widget_t*} dialog_title对象。
 */
widget_t* dialog_title_cast(widget_t* widget);

#define DIALOG_TITLE(widget) ((dialog_title_t*)(dialog_title_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(dialog_title);

END_C_DECLS

#endif /*TK_DIALOG_TITLE_H*/
