﻿/**
 * File:   slider.h
 * Author: AWTK Develop Team
 * Brief:  slider
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
 * 2018-04-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_SLIDER_H
#define TK_SLIDER_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @class slider_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 滑块控件。
 *
 * slider\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于slider\_t控件。
 *
 * 在xml中使用"slider"标签创建滑块控件。如：
 *
 * ```xml
 * <slider x="center" y="10" w="80%" h="20" value="10"/>
 * <slider style="img" x="center" y="50" w="80%" h="30" value="20" />
 * <slider style="img" x="center" y="90" w="80%" h="30" value="30" min="5" max="50" step="5"/>
 * ```
 *
 * > 更多用法请参考：
 * [basic](https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/ui/basic.xml)
 *
 * 在c代码中使用函数slider\_create创建滑块控件。如：
 *
 * ```c
 *  widget_t* slider = slider_create(win, 10, 10, 200, 30);
 *  widget_on(slider, EVT_VALUE_CHANGED, on_changed, NULL);
 *  widget_on(slider, EVT_VALUE_CHANGING, on_changing, NULL);
 * ```
 *
 * > 完整示例请参考：
 * [slider demo](https://github.com/zlgopen/awtk-c-demos/blob/master/demos/slider.c)
 *
 * 可用通过style来设置控件的显示风格，如图片和颜色等等。如：
 *
 * ```xml
 * <style name="img" bg_image="slider_bg" fg_image="slider_fg">
 *  <normal icon="slider_drag"/>
 *  <pressed icon="slider_drag_p"/>
 *  <over icon="slider_drag_o"/>
 * </style>
 * ```
 *
 * > 更多用法请参考：
 * [theme
 * default](https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/styles/default.xml#L179)
 *
 */
typedef struct _slider_t {
  widget_t widget;
  /**
   * @property {uint16_t} value
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 值。
   */
  uint16_t value;

  /**
   * @property {uint16_t} min
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 最小值。
   */
  uint16_t min;

  /**
   * @property {uint16_t} max
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 最大值。
   */
  uint16_t max;

  /**
   * @property {uint16_t} step
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 拖动的最小单位。
   */
  uint16_t step;

  /**
   * @property {bool_t} vertical
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 滑块的是否为垂直方向。
   */
  bool_t vertical;

  /**
   * @property {uint32_t} bar_size
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * bar的宽度或高度。
   */
  uint32_t bar_size;

  /*private*/
  bool_t dragging;
} slider_t;

/**
 * @event {event_t} EVT_VALUE_WILL_CHANGE
 * 值即将改变事件。
 */

/**
 * @event {event_t} EVT_VALUE_CHANGING
 * 值正在改变事件(拖动中)。
 */

/**
 * @event {event_t} EVT_VALUE_CHANGED
 * 值改变事件。
 */

/**
 * @method slider_create
 * 创建slider对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* slider_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method slider_cast
 * 转换为slider对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget slider对象。
 *
 * @return {widget_t*} slider对象。
 */
widget_t* slider_cast(widget_t* widget);

/**
 * @method slider_set_value
 * 设置滑块的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {uint16_t}  value 值
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_value(widget_t* widget, uint16_t value);

/**
 * @method slider_set_min
 * 设置滑块的最小值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {uint16_t}  min 最小值
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_min(widget_t* widget, uint16_t min);

/**
 * @method slider_set_max
 * 设置滑块的最大值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {uint16_t}  max 最大值
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_max(widget_t* widget, uint16_t max);

/**
 * @method slider_set_step
 * 设置滑块的拖动的最小单位。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {uint16_t}  step 拖动的最小单位。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_step(widget_t* widget, uint16_t step);

/**
 * @method slider_set_bar_size
 * 设置bar的宽度或高度。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {uint32_t}  bar_size bar的宽度或高度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_bar_size(widget_t* widget, uint32_t bar_size);

/**
 * @method slider_set_vertical
 * 设置滑块的方向。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {bool_t}  vertical 是否为垂直方向。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t slider_set_vertical(widget_t* widget, bool_t vertical);

#define SLIDER(widget) ((slider_t*)(slider_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(slider);

/*public for test*/
ret_t slider_dec(widget_t* widget);
ret_t slider_inc(widget_t* widget);
ret_t slider_set_value_internal(widget_t* widget, uint16_t value, event_type_t etype, bool_t force);

END_C_DECLS

#endif /*TK_SLIDER_H*/
