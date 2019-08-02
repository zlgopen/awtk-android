﻿/**
 * File:   time_clock.h
 * Author: AWTK Develop Team
 * Brief:  time_clock
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
 * 2018-08-30 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_TIME_CLOCK_H
#define TK_TIME_CLOCK_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @class time_clock_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 模拟时钟控件。
 *
 * time\_clock\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于time\_clock\_t控件。
 *
 * 在xml中使用"time\_clock"标签创建模拟时钟控件。如：
 *
 * ```xml
 * <time_clock x="c" y="m" w="300" h="300" bg_image="clock_bg" image="clock"
 *   hour_image="clock_hour" minute_image="clock_minute" second_image="clock_second"/>
 * ```
 *
 * > 更多用法请参考：[time\_clock.xml](
 * https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/ui/time_clock.xml)
 *
 * 在c代码中使用函数time\_clock\_create创建模拟时钟控件。如：
 *
 * ```c
 * widget_t* tc = time_clock_create(win, 10, 10, 240, 240);
 * time_clock_set_image(tc, "clock");
 * time_clock_set_bg_image(tc, "clock_bg");
 * time_clock_set_hour_image(tc, "clock_hour");
 * time_clock_set_minute_image(tc, "clock_minute");
 * time_clock_set_second_image(tc, "clock_second");
 * ```
 *
 * > 完整示例请参考：[time_clock demo](
 * https://github.com/zlgopen/awtk-c-demos/blob/master/demos/time_clock.c)
 *
 * time\_clock一般不需要设置style。
 *
 */
typedef struct _time_clock_t {
  widget_t widget;

  /**
   * @property {int32_t} hour
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 小时。
   */
  int32_t hour;
  /**
   * @property {int32_t} minute
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 分钟。
   */
  int32_t minute;
  /**
   * @property {int32_t} second
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 秒。
   */
  int32_t second;

  /**
   * @property {char*} image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 中心图片。
   */
  char* image;
  /**
   * @property {char*} bg_image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 背景图片。
   */
  char* bg_image;
  /**
   * @property {char*} hour_image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 时针图片。
   */
  char* hour_image;
  /**
   * @property {char*} minute_image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 分针图片。
   */
  char* minute_image;
  /**
   * @property {char*} second_image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 秒针图片。
   */
  char* second_image;

} time_clock_t;

/**
 * @method time_clock_create
 * 创建time_clock对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* time_clock_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method time_clock_cast
 * 转换为time_clock对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget time_clock对象。
 *
 * @return {widget_t*} time_clock对象。
 */
widget_t* time_clock_cast(widget_t* widget);

/**
 * @method time_clock_set_hour
 * 设置小时的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {int32_t} hour 小时的值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_hour(widget_t* widget, int32_t hour);

/**
 * @method time_clock_set_minute
 * 设置分钟的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {int32_t} minute 分钟的值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_minute(widget_t* widget, int32_t minute);

/**
 * @method time_clock_set_second
 * 设置秒的值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {int32_t} second 秒的值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_second(widget_t* widget, int32_t second);

/**
 * @method time_clock_set_hour_image
 * 设置小时的图片。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {const char*} hour 小时的图片。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_hour_image(widget_t* widget, const char* hour);

/**
 * @method time_clock_set_minute_image
 * 设置分钟的图片。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {const char*} minute_image 分钟的图片。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_minute_image(widget_t* widget, const char* minute_image);

/**
 * @method time_clock_set_second_image
 * 设置秒的图片。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {const char*} second_image 秒的图片。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_second_image(widget_t* widget, const char* second_image);

/**
 * @method time_clock_set_bg_image
 * 设置背景图片。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {const char*} bg_image 背景图片。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_bg_image(widget_t* widget, const char* bg_image);

/**
 * @method time_clock_set_image
 * 设置图片。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget 控件对象。
 * @param {const char*} image 图片。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_clock_set_image(widget_t* widget, const char* image);

#define TIME_CLOCK_PROP_HOUR "hour"
#define TIME_CLOCK_PROP_MINUTE "minute"
#define TIME_CLOCK_PROP_SECOND "second"

#define TIME_CLOCK_PROP_IMAGE "image"
#define TIME_CLOCK_PROP_BG_IMAGE "bg_image"
#define TIME_CLOCK_PROP_HOUR_IMAGE "hour_image"
#define TIME_CLOCK_PROP_MINUTE_IMAGE "minute_image"
#define TIME_CLOCK_PROP_SECOND_IMAGE "second_image"

#define WIDGET_TYPE_TIME_CLOCK "time_clock"

#define TIME_CLOCK(widget) ((time_clock_t*)(time_clock_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(time_clock);

END_C_DECLS

#endif /*TK_TIME_CLOCK_H*/
