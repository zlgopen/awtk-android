﻿/**
 * File:   image_value.h
 * Author: AWTK Develop Team
 * Brief:  image_value
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
 * 2018-12-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_IMAGE_VALUE_H
#define TK_IMAGE_VALUE_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @class image_value_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * 图片值控件。
 *
 * 可以用图片来表示如电池电量、WIFI信号强度和其它各种数值的值。
 *
 * 其原理如下：
 *
 *  * 1.把value以format为格式转换成字符串。
 *  * 2.把每个字符与image(图片文件名前缀)映射成一个图片名。
 *  * 3.最后把这些图片显示出来。
 *
 *image\_value\_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于image\_value\_t控件。
 *
 *在xml中使用"image\_value"标签创建图片值控件。如：
 *
 * ```xml
 * <image_value  value="0" image="num_" />
 * ```
 *
 * > 更多用法请参考：
 * [image\_value](https://github.com/zlgopen/awtk/blob/master/demos/assets/raw/ui/image_value.xml)
 *
 * 在c代码中使用函数image\_value\_create创建图片值控件。如：
 *
 * ```c
 * image_value = image_value_create(win, 10, 10, 200, 200);
 * image_value_set_image(image_value, "num_");
 * image_value_set_value(image_value, 100);
 * ```
 *
 * > 完整示例请参考：
 * [image_value demo](https://github.com/zlgopen/awtk-c-demos/blob/master/demos/image_value.c)
 *
 * 可用通过style来设置控件的显示风格，如背景颜色和边框等等，不过一般情况并不需要。
 *
 */
typedef struct _image_value_t {
  widget_t widget;

  /**
   * @property {char*} image
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 图片名称的前缀。
   */
  char* image;

  /**
   * @property {char*} format
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 数值到字符串转换时的格式，缺省为"%d"。
   */
  char* format;

  /**
   * @property {float_t} value
   * @annotation ["set_prop","get_prop","readable","persitent","design","scriptable"]
   * 值。
   */
  float_t value;
} image_value_t;

/**
 * @method image_value_create
 * 创建image_value对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* image_value_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method image_value_set_image
 * 设置图片前缀。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget image_value对象。
 * @param {const char*} image 图片前缀。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t image_value_set_image(widget_t* widget, const char* image);

/**
 * @method image_value_set_format
 * 设置格式。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget image_value对象。
 * @param {const char*} format 格式。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t image_value_set_format(widget_t* widget, const char* format);

/**
 * @method image_value_set_value
 * 设置值。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget image_value对象。
 * @param {float_t} value 值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t image_value_set_value(widget_t* widget, float_t value);

/**
 * @method image_value_cast
 * 转换为image_value对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget image_value对象。
 *
 * @return {widget_t*} image_value对象。
 */
widget_t* image_value_cast(widget_t* widget);

#define WIDGET_TYPE_IMAGE_VALUE "image_value"

/* "."不是有效的文件名，所以把字符"."映射成"dot" */
#define IMAGE_VALUE_MAP_DOT "dot"
/* "/"不是有效的文件名，所以把字符"/"映射成"slash" */
#define IMAGE_VALUE_MAP_SLASH "slash"

#ifndef IMAGE_VALUE_MAX_CHAR_NR
#define IMAGE_VALUE_MAX_CHAR_NR 8
#endif /*IMAGE_VALUE_MAX_CHAR_NR*/

#define IMAGE_VALUE(widget) ((image_value_t*)(image_value_cast(WIDGET(widget))))

/*public for subclass and runtime type check*/
TK_EXTERN_VTABLE(image_value);

END_C_DECLS

#endif /*TK_IMAGE_VALUE_H*/
