﻿/**
 * File:   edit.h
 * Author: AWTK Develop Team
 * Brief:  edit
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
 * 2018-02-06 Li XianJing <xianjimli@hotmail.com> created
 * 2018-11-20 Li YaoShen  <liyaoshen@zlg.cn> 1.text selection; 2.cursor movable
 *
 */

#ifndef TK_EDIT_H
#define TK_EDIT_H

#include "base/widget.h"
#include "base/text_edit.h"
#include "base/input_method.h"

BEGIN_C_DECLS

typedef struct _input_limit_t {
  input_type_t type;
  union {
    struct {
      uint32_t min;
      uint32_t max;
    } t;
    struct {
      int32_t min;
      int32_t max;
      uint32_t step;
    } i;
    struct {
      double min;
      double max;
      double step;
    } f;
  } u;
} input_limit_t;

typedef bool_t (*edit_is_valid_char_t)(widget_t* widget, wchar_t c);

/**
 * @class edit_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 单行编辑器控件。
 *
 * 在基于SDL的平台，单行编辑器控件使用平台原生的输入法，对于嵌入式平台使用内置的输入法。
 *
 * 在使用内置的输入法时，软键盘由输入类型决定，开发者可以自定义软键盘的界面。
 *
 * edit\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于edit\_t控件。
 *
 * edit\_t本身可以做为容器，放入按钮等控件。有几个特殊的子控件：
 *
 * * 名为"clear"的按钮。点击时清除编辑器中的内容。
 * * 名为"inc"的按钮。点击时增加编辑器的值，用于实现类似于spinbox的功能。
 * * 名为"dec"的按钮。点击时减少编辑器的值，用于实现类似于spinbox的功能。
 * * 名为"visible"的复选框。勾选时显示密码，反之不显示密码。
 *
 *在xml中使用"edit"标签创建编辑器控件。如：
 *
 * ```xml
 * <edit x="c" y="m" w="80" h="30"
 *   tips="age" input_type="uint" min="0" max="150" step="1" auto_fix="true" style="number" />
 * ```
 *
 * > XXX：需要在min/max/step之前设置input\_type。
 *
 * >更多用法请参考：
 * [edit.xml](https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/ui/edit.xml)
 *
 * 在c代码中使用函数edit\_create创建编辑器控件。如：
 *
 * ```c
 *  widget_t* edit = edit_create(win, 10, 10, 128, 30);
 *  widget_set_text(edit, L"OK");
 * ```
 *
 * > 创建之后，可以用widget\_set\_text或widget\_set\_text\_utf8设置文本内容。
 *
 * > 完整示例请参考：
 * [edit demo](https://github.com/zlgopen/awtk-c-demos/blob/master/demos/edit.c)
 *
 * 可用通过style来设置控件的显示风格，如字体的大小和颜色等等。如：
 *
 * ```xml
 * <style name="default" border_color="#a0a0a0"  text_color="black" text_align_h="left">
 *   <normal     bg_color="#f0f0f0" />
 *   <focused    bg_color="#f0f0f0" border_color="black"/>
 *   <disable    bg_color="gray" text_color="#d0d0d0" />
 *   <error      bg_color="#f0f0f0" text_color="red" />
 *   <empty      bg_color="#f0f0f0" text_color="#a0a0a0" />
 * </style>
 * ```
 *
 * > 更多用法请参考：
 * [theme
 *default](https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/styles/default.xml#L104)
 *
 */
typedef struct _edit_t {
  widget_t widget;

  /**
   * @property {bool_t} readonly
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 编辑器是否为只读。
   */
  bool_t readonly;
  /**
   * @property {bool_t} password_visible
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 密码是否可见。
   */
  bool_t password_visible;
  /**
   * @property {bool_t} auto_fix
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 输入无效时，是否自动改正。
   */
  bool_t auto_fix;
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
   * @property {input_type_t} input_type
   * @annotation ["set_prop","get_prop","persitent","design"]
   * 输入类型。
   * XXX：需要在min/max/step之前设置。
   */

  /**
   * @property {float_t} min
   * @annotation ["set_prop","get_prop","persitent","design"]
   * 最小值或最小长度。
   */

  /**
   * @property {float_t} max
   * @annotation ["set_prop","get_prop","persitent","design"]
   * 最大值或最大长度。
   */

  /**
   * @property {float_t} step
   * @annotation ["set_prop","get_prop","persitent","design"]
   * 步长。
   * 作为数值型编辑器时，一次增加和减少时的数值。
   */

  /*private*/
  uint32_t idle_id;
  uint32_t timer_id;
  input_limit_t limit;
  text_edit_t* model;
  edit_is_valid_char_t is_valid_char;
} edit_t;

/**
 * @event {event_t} EVT_VALUE_CHANGING
 * 文本正在改变事件(编辑中)。
 */

/**
 * @event {event_t} EVT_VALUE_CHANGED
 * 文本改变事件。
 */

/**
 * @method edit_create
 * 创建edit对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* edit_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method edit_cast
 * 转换为edit对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget edit对象。
 *
 * @return {widget_t*} edit对象。
 */
widget_t* edit_cast(widget_t* widget);

/**
 * @method edit_get_int
 * 获取int类型的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 *
 * @return {int32_t} 返回int的值。
 */
int32_t edit_get_int(widget_t* widget);

/**
 * @method edit_get_double
 * 获取double类型的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 *
 * @return {double} 返回double的值。
 */
double edit_get_double(widget_t* widget);

/**
 * @method edit_set_int
 * 设置int类型的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {int32_t} value 值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_int(widget_t* widget, int32_t value);

/**
 * @method edit_set_double
 * 设置double类型的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {double} value 值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_double(widget_t* widget, double value);

/**
 * @method edit_set_text_limit
 * 设置为文本输入及其长度限制，不允许输入超过max个字符，少于min个字符时进入error状态。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {uint32_t} min 最小长度。
 * @param {uint32_t} max 最大长度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_text_limit(widget_t* widget, uint32_t min, uint32_t max);

/**
 * @method edit_set_int_limit
 * 设置为整数输入及取值范围。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {int32_t} min 最小值。
 * @param {int32_t} max 最大值。
 * @param {int32_t} step 步长。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_int_limit(widget_t* widget, int32_t min, int32_t max, uint32_t step);

/**
 * @method edit_set_float_limit
 * 设置为浮点数输入及取值范围。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {double} min 最小值。
 * @param {double} max 最大值。
 * @param {double} step 步长。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_float_limit(widget_t* widget, double min, double max, double step);

/**
 * @method edit_set_readonly
 * 设置编辑器是否为只读。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} readonly 只读。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_readonly(widget_t* widget, bool_t readonly);

/**
 * @method edit_set_auto_fix
 * 设置编辑器是否为自动改正。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} auto_fix 自动改正。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_auto_fix(widget_t* widget, bool_t auto_fix);

/**
 * @method edit_set_input_type
 * 设置编辑器的输入类型。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {input_type_t} type 输入类型。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_input_type(widget_t* widget, input_type_t type);

/**
 * @method edit_set_input_tips
 * 设置编辑器的输入提示。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {char*} tips 输入提示。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_input_tips(widget_t* widget, const char* tips);

/**
 * @method edit_set_password_visible
 * 当编辑器输入类型为密码时，设置密码是否可见。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} password_visible 密码是否可见。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_password_visible(widget_t* widget, bool_t password_visible);

/**
 * @method edit_set_focus
 * 设置为焦点。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget widget对象。
 * @param {bool_t} focus 是否为焦点。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_focus(widget_t* widget, bool_t focus);

/**
 * @method edit_set_is_valid_char
 * 设置输入字符检查函数。
 *> 如果内置检查函数不能满足需求时，可以设置自定义的检查函数。
 *
 * @param {widget_t*} widget widget对象。
 * @param {edit_is_valid_char_t} is_valid_char 检查输入字符是否有效的回调函数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t edit_set_is_valid_char(widget_t* widget, edit_is_valid_char_t is_valid_char);

#define EDIT(widget) ((edit_t*)(edit_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(edit);

/*public for spinbox and other controls*/
ret_t edit_on_destroy(widget_t* widget);
ret_t edit_on_paint_self(widget_t* widget, canvas_t* c);
ret_t edit_on_event(widget_t* widget, event_t* e);
ret_t edit_get_prop(widget_t* widget, const char* name, value_t* v);
ret_t edit_set_prop(widget_t* widget, const char* name, const value_t* v);
widget_t* edit_create_ex(widget_t* parent, const widget_vtable_t* vt, xy_t x, xy_t y, wh_t w,
                         wh_t h);

/*public for test*/
ret_t edit_inc(edit_t* edit);
ret_t edit_dec(edit_t* edit);
ret_t edit_clear(edit_t* edit);
bool_t edit_is_valid_value(widget_t* widget);
ret_t edit_input_char(widget_t* widget, wchar_t c);
bool_t edit_is_valid_char(widget_t* widget, wchar_t c);

END_C_DECLS

#endif /*TK_EDIT_H*/
