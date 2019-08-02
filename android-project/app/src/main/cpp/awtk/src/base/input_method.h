﻿/**
 * File:   input_method.h
 * Author: AWTK Develop Team
 * Brief:  input method interface.
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
 * 2018-06-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_INPUT_METHOD_H
#define TK_INPUT_METHOD_H

#include "base/widget.h"
#include "base/input_engine.h"
#include "base/suggest_words.h"

BEGIN_C_DECLS

struct _input_method_t;
typedef struct _input_method_t input_method_t;

typedef ret_t (*input_method_request_t)(input_method_t* im, widget_t* widget);
typedef ret_t (*input_method_destroy_t)(input_method_t* im);

/**
 * @enum input_type_t
 * @annotation ["scriptable"]
 * @prefix INPUT_
 * 输入类型常量定义。
 */
typedef enum _input_type_t {
  /**
   * @const INPUT_TEXT
   * 文本。
   */
  INPUT_TEXT = 0,
  /**
   * @const INPUT_INT
   * 整数。
   */
  INPUT_INT,
  /**
   * @const INPUT_UINT
   * 非负整数。
   */
  INPUT_UINT,
  /**
   * @const INPUT_HEX
   * 16进制整数。
   */
  INPUT_HEX,
  /**
   * @const INPUT_FLOAT
   * 浮点数。
   */
  INPUT_FLOAT,
  /**
   * @const INPUT_UFLOAT
   * 非负浮点数。
   */
  INPUT_UFLOAT,
  /**
   * @const INPUT_EMAIL
   * 邮件地址。
   */
  INPUT_EMAIL,
  /**
   * @const INPUT_PASSWORD
   * 密码。
   */
  INPUT_PASSWORD,
  /**
   * @const INPUT_PHONE
   * 电话号码。
   */
  INPUT_PHONE,
  /**
   * @const INPUT_CUSTOM
   * 使用自定义的软键盘(如计算器等应用不希望弹出系统软键盘)。
   */
  INPUT_CUSTOM
} input_type_t;

/**
 * @class im_commit_event_t
 * @parent event_t
 * 输入法提交输入的文本事件。
 */
typedef struct _im_commit_event_t {
  event_t e;
  /**
   * @property {char*} text
   * @annotation ["readable"]
   * 提交的文本。
   */
  const char* text;

  /**
   * @property {bool_t} replace;
   * @annotation ["readable"]
   * 是否替换原来的文本。
   */
  bool_t replace;
} im_commit_event_t;

/**
 * @class im_action_button_info_event_t
 * @parent event_t
 * 设置软键盘上的action按钮的信息事件。
 */
typedef struct _im_action_button_info_event_t {
  event_t e;
  /**
   * @property {char*} text
   * @annotation ["readable"]
   * 软键盘上的action按钮显示的文本。
   */
  const char* text;
  /**
   * @property {bool_t} enable
   * @annotation ["readable"]
   * 软键盘上的action按钮启用。
   */
  bool_t enable;
} im_action_button_info_event_t;

/**
 * @class im_candidates_event_t
 * @parent event_t
 * 输入法请求显示候选字的事件。
 */
typedef struct _im_candidates_event_t {
  event_t e;
  /**
   * @property {char*} candidates
   * @annotation ["readable"]
   * 可选的文本，多个文本以\0分隔。如：里\0李\0力\0离\0
   */
  const char* candidates;

  /**
   * @property {uint32_t} candidates_nr
   * @annotation ["readable"]
   * 可选的文本的个数。
   */
  uint32_t candidates_nr;
} im_candidates_event_t;

/**
 * @class input_method_t
 * 输入法接口。
 *
 * @annotation ["scriptable"]
 * 常见的实现方式有以下几种：
 *
 * * 空实现。用于不需要输入法的嵌入式平台。
 *
 * * 缺省实现。用于需要输入法的嵌入式平台。
 *
 * * 基于SDL实现的平台原生输入法。用于桌面系统和手机系统。
 *
 * ```graphviz
 *  [default_style]
 *
 *  input_method_default_t -> input_method_t [arrowhead=empty style=dashed]
 *  input_method_sdl_t -> input_method_t [arrowhead=empty style=dashed]
 *  input_method_null_t -> input_method_t [arrowhead=empty style=dashed]
 *
 * ```
 *
 * > 输入类型请参考：[input\_type](input_type_t.md)
 *
 */
struct _input_method_t {
  /**
   * @property {widget_t*} widget
   * @annotation ["private"]
   * 当前的焦点控件。
   */
  widget_t* widget;

  /**
   * @property {widget_t*} keyboard
   * @annotation ["private"]
   * 当前的软件键盘。
   */
  widget_t* keyboard;

  /**
   * @property {widget_t*} win
   * @annotation ["private"]
   * 当前的窗口。
   */
  widget_t* win;

  /**
   * @property {int32_t} win_delta_y
   * @annotation ["private"]
   * 由于软键盘的弹出，可能会将窗口向上推移，win_delta_y为推移的距离。
   */
  int32_t win_delta_y;

  /**
   * @property {bool_t} action_button_enable
   * @annotation ["readable"]
   * 软键盘的上的action按钮是否可用。
   */
  bool_t action_button_enable;

  /**
   * @property {bool_t} action_button_enable
   * @annotation ["readable"]
   * 软键盘的上的action按钮文本。
   */
  char action_buton_text[TK_NAME_LEN + 1];

  /**
   * @property {emitter_t} emitter
   * @annotation ["private"]
   * emitter。用于实现dispatch/on/off等功能。
   */
  emitter_t emitter;

  /**
   * @property {input_type_t} input_type
   * @annotation ["readable"]
   * 当前输入的类型。
   */
  input_type_t input_type;

  input_engine_t* engine;
  suggest_words_t* suggest_words;
  /**
   * 子类需要实现的函数。
   */
  input_method_request_t request;
  input_method_destroy_t destroy;

  /*private*/
  bool_t busy;
};

/**
 * @method input_method_dispatch
 * 分发一个事件。
 * @param {input_method_t*} im 控件对象。
 * @param {event_t*} e 事件。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_dispatch(input_method_t* im, event_t* e);

/**
 * @method input_method_dispatch_to_widget
 * 分发一个事件当前焦点控件。
 * @param {input_method_t*} im 控件对象。
 * @param {event_t*} e 事件。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_dispatch_to_widget(input_method_t* im, event_t* e);

/**
 * @method input_method_on
 * 注册指定事件的处理函数。
 * @param {input_method_t*} im 输入法对象。
 * @param {event_type_t} type 事件类型。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {uint32_t} 返回id，用于input_method_off。
 */
uint32_t input_method_on(input_method_t* im, event_type_t type, event_func_t on_event, void* ctx);

/**
 * @method input_method_off
 * 注销指定事件的处理函数。
 * @param {input_method_t*} im 输入法对象。
 * @param {uint32_t} id input_method_on返回的ID。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_off(input_method_t* im, uint32_t id);

/**
 * @method input_method_request
 * 打开或关闭输入法。
 * @param {input_method_t*} im 输入法对象。
 * @param {widget_t*} widget 焦点控件，为NULL时关闭输入法，非NULL时打开输入法。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_request(input_method_t* im, widget_t* widget);

/**
 * @method input_method_update_action_button_info
 * 设置软键盘上的action按钮的信息。
 * @param {input_method_t*} im 输入法对象。
 * @param {char*} text 按钮的文本。
 * @param {bool_t} enable 按钮的是否可用。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_update_action_button_info(input_method_t* im, const char* text, bool_t enable);

/**
 * @method input_method_dispatch_action
 * 软键盘上的action按钮被点击时，调用本函数分发EVT_IM_ACTION事件。
 * @param {input_method_t*} im 输入法对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_dispatch_action(input_method_t* im);

/**
 * @method input_method_commit_text
 * 提交输入文本。
 * @annotation ["scriptable"]
 * @param {input_method_t*} im 输入法对象。
 * @param {char*} text 文本。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_commit_text(input_method_t* im, const char* text);

/**
 * @method input_method_commit_text_ex
 * 提交输入文本。
 * @param {input_method_t*} im 输入法对象。
 * @param {bool_t} replace 是否替换原来的文本。
 * @param {char*} text 文本。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_commit_text_ex(input_method_t* im, bool_t replace, const char* text);

/**
 * @method input_method_dispatch_key
 * 提交按键。
 * @annotation ["scriptable"]
 * @param {input_method_t*} im 输入法对象。
 * @param {uint32_t} key 键值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_dispatch_key(input_method_t* im, uint32_t key);

/**
 * @method input_method_dispatch_candidates
 * 请求显示候选字。
 * @param {input_method_t*} im 输入法对象。
 * @param {char*} strs 候选字列表。
 * @param {uint32_t} nr 候选字个数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_dispatch_candidates(input_method_t* im, const char* strs, uint32_t nr);

/**
 * @method input_method_create
 * 创建输入法对象。在具体实现中实现。
 *
 * @return {input_method_t*} 成功返回输入法对象，失败返回NULL。
 */
input_method_t* input_method_create(void);

/**
 * @method input_method_destroy
 * 销毁输入法对象。在具体实现中实现。
 * @param {input_method_t*} im 输入法对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_destroy(input_method_t* im);

/**
 * @method input_method
 * 获取全局输入法对象。
 * @alias input_method_instance
 * @annotation ["constructor", "scriptable"]
 *
 * @return {input_method_t*} 成功返回输入法对象，失败返回NULL。
 */
input_method_t* input_method(void);

/**
 * @method input_method_set
 * 设置全局输入法对象。
 * @param {input_method_t*} im 输入法对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t input_method_set(input_method_t* im);

event_t* im_commit_event_init(im_commit_event_t* e, const char* text, bool_t replace);

END_C_DECLS

#endif /*TK_INPUT_METHOD_H*/
