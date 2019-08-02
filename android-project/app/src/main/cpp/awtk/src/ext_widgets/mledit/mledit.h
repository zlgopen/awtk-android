﻿/**
 * File:   mledit.h
 * Author: AWTK Develop Team
 * Brief:  mledit
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
 * 2019-06-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_MLEDIT_H
#define TK_MLEDIT_H

#include "base/widget.h"
#include "base/text_edit.h"

BEGIN_C_DECLS

/**
 * @class mledit_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 多行编辑器控件。
 *
 * mledit\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于mledit\_t控件。
 *
 * 在xml中使用"mledit"标签创建多行编辑器控件。如：
 *
 * ```xml
 * <mledit x="c" y="m" w="300" h="300" />
 * ```
 *
 * > 更多用法请参考：[mledit.xml](
 * https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/ui/mledit.xml)
 *
 * 在c代码中使用函数mledit\_create创建多行编辑器控件。如：
 *
 * ```c
 * widget_t* tc = mledit_create(win, 10, 10, 240, 240);
 * ```
 *
 * > 完整示例请参考：[mledit demo](
 * https://github.com/zlgopen/awtk-c-demos/blob/master/demos/mledit.c)
 *
 * time\_clock一般不需要设置style。
 *
 */
typedef struct _mledit_t {
  widget_t widget;

  /**
   * @property {bool_t} readonly
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 编辑器是否为只读。
   */
  bool_t readonly;
  /**
   * @property {uint8_t} top_margin
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 上边距。
   */
  uint8_t top_margin;
  /**
   * @property {uint8_t} bottom_margin
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 下边距。
   */
  uint8_t bottom_margin;
  /**
   * @property {uint8_t} left_margin
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 左边距。
   */
  uint8_t left_margin;
  /**
   * @property {uint8_t} right_margin
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 右边距。
   */
  uint8_t right_margin;
  /**
   * @property {char*} tips
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 输入提示。
   */
  char* tips;
  /**
   * @property {bool_t} focus
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 设置为焦点(通常用于在XML中缺省设置为焦点控件)。
   */
  bool_t focus;

  /**
   * @property {bool_t} wrap_word
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 是否自动折行。
   */
  bool_t wrap_word;

  /**
   * @property {uint32_t} max_lines
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 最大行数。
   */
  uint32_t max_lines;

  /*private*/
  text_edit_t* model;
  uint32_t timer_id;

  wstr_t temp;
} mledit_t;

/**
 * @method mledit_create
 * 创建mledit对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* mledit_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method mledit_set_readonly
 * 设置编辑器是否为只读。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} readonly 只读。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t mledit_set_readonly(widget_t* widget, bool_t readonly);

/**
 * @method mledit_set_wrap_word
 * 设置编辑器是否自动折行。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} wrap_word 是否自动折行。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t mledit_set_wrap_word(widget_t* widget, bool_t wrap_word);

/**
 * @method mledit_set_max_lines
 * 设置编辑器的最大行数。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {uint32_t} max_lines 最大行数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t mledit_set_max_lines(widget_t* widget, uint32_t max_lines);

/**
 * @method mledit_set_input_tips
 * 设置编辑器的输入提示。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {char*} tips 输入提示。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t mledit_set_input_tips(widget_t* widget, const char* tips);

/**
 * @method mledit_cast
 * 转换为mledit对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget mledit对象。
 *
 * @return {widget_t*} mledit对象。
 */
widget_t* mledit_cast(widget_t* widget);

#define WIDGET_TYPE_MLEDIT "mledit"

#define MLEDIT_PROP_MAX_LINES "max_lines"
#define MLEDIT_PROP_WRAP_WORD "wrap_word"
#define MLEDIT(widget) ((mledit_t*)(mledit_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(mledit);

END_C_DECLS

#endif /*TK_MLEDIT_H*/
