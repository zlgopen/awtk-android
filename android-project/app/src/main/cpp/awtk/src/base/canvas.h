﻿/**
 * File:   canvas.h
 * Author: AWTK Develop Team
 * Brief:  canvas provides basic drawings functions.
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

#ifndef TK_CANVAS_H
#define TK_CANVAS_H

#include "base/lcd.h"
#include "base/font_manager.h"

BEGIN_C_DECLS

struct _canvas_t;
typedef struct _canvas_t canvas_t;

/**
 * @class canvas_t
 * @annotation ["scriptable"]
 * canvas类。
 */
struct _canvas_t {
  /**
   * @property {xy_t} ox
   * @annotation ["readable", "scriptable"]
   * x坐标偏移。
   */
  xy_t ox;

  /**
   * @property {xy_t} oy
   * @annotation ["readable", "scriptable"]
   * y坐标偏移。
   */
  xy_t oy;

  xy_t clip_left;
  xy_t clip_top;
  xy_t clip_right;
  xy_t clip_bottom;
  uint32_t fps;
  bool_t show_fps;

  lcd_t* lcd;
  font_t* font;
  font_size_t font_size;
  char* font_name;

  align_v_t text_align_v;
  align_h_t text_align_h;
  font_manager_t* font_manager;
  uint8_t global_alpha;

  bool_t began_frame;
};

/**
 * @method canvas_init
 * 初始化，系统内部调用。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {lcd_t*} lcd lcd对象。
 * @param {font_manager_t*} font_manager 字体管理器对象。
 *
 * @return {canvas_t*} 返回canvas对象本身。
 */
canvas_t* canvas_init(canvas_t* c, lcd_t* lcd, font_manager_t* font_manager);

/**
 * @method canvas_get_width
 * 获取画布的宽度。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 *
 * @return {wh_t} 返回画布的宽度。
 *
 */
wh_t canvas_get_width(canvas_t* c);

/**
 * @method canvas_get_height
 * 获取画布的高度。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 *
 * @return {wh_t} 返回画布的高度。
 *
 */
wh_t canvas_get_height(canvas_t* c);

/**
 * @method canvas_get_clip_rect
 * 获取裁剪区。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {rect_t*} r rect对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_get_clip_rect(canvas_t* c, rect_t* r);

/**
 * @method canvas_set_clip_rect
 * 设置裁剪区。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const rect_t*} r rect对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_clip_rect(canvas_t* c, const rect_t* r);

/**
 * @method canvas_set_clip_rect_ex
 * 设置裁剪区。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const rect_t*} r rect对象。
 * @param {bool_t} translate 是否将裁剪区的位置加上canvas当前的偏移。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_clip_rect_ex(canvas_t* c, const rect_t* r, bool_t translate);

/**
 * @method canvas_set_fill_color
 * 设置填充颜色。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {color_t} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_fill_color(canvas_t* c, color_t color);

/**
 * @method canvas_set_text_color
 * 设置文本颜色。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {color_t} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_text_color(canvas_t* c, color_t color);

/**
 * @method canvas_set_stroke_color
 * 设置线条颜色。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {color_t} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_stroke_color(canvas_t* c, color_t color);

/**
 * @method canvas_set_fill_color_str
 * 设置填充颜色。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_set_fill_color
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_fill_color_str(canvas_t* c, const char* color);

/**
 * @method canvas_set_text_color_str
 * 设置文本颜色。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_set_text_color
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_text_color_str(canvas_t* c, const char* color);

/**
 * @method canvas_set_stroke_color_str
 * 设置线条颜色。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_set_stroke_color
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} color 颜色。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_stroke_color_str(canvas_t* c, const char* color);

/**
 * @method canvas_set_global_alpha
 * 设置全局alpha值。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {uint8_t} alpha alpha值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_global_alpha(canvas_t* c, uint8_t alpha);

/**
 * @method canvas_translate
 * 平移原点坐标。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} dx x偏移。
 * @param {xy_t} dy y偏移。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_translate(canvas_t* c, xy_t dx, xy_t dy);

/**
 * @method canvas_untranslate
 * 反向平移原点坐标。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} dx x偏移。
 * @param {xy_t} dy y偏移。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_untranslate(canvas_t* c, xy_t dx, xy_t dy);

/**
 * @method canvas_draw_vline
 * 画垂直线。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 * @param {wh_t} h 高度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_vline(canvas_t* c, xy_t x, xy_t y, wh_t h);

/**
 * @method canvas_draw_hline
 * 画水平线。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 * @param {wh_t} w 宽度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_hline(canvas_t* c, xy_t x, xy_t y, wh_t w);

/**
 * @method canvas_draw_points
 * 画多个点。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {const point_t*} points 点数组。
 * @param {uint32_t} nr 点的个数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_points(canvas_t* c, const point_t* points, uint32_t nr);

/**
 * @method canvas_fill_rect
 * 填充矩形。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 * @param {wh_t} w 宽度。
 * @param {wh_t} h 高度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_fill_rect(canvas_t* c, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method canvas_stroke_rect
 * 绘制矩形。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 * @param {wh_t} w 宽度。
 * @param {wh_t} h 高度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_stroke_rect(canvas_t* c, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method canvas_set_font
 * 设置字体。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} name 字体名称。
 * @param {font_size_t} size 字体大小。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_font(canvas_t* c, const char* name, font_size_t size);

/**
 * @method canvas_set_text_align
 * 设置文本对齐方式。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {align_h_t} align_h 水平对齐方式。
 * @param {align_v_t} align_v 垂直对齐方式。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_set_text_align(canvas_t* c, align_h_t align_h, align_v_t align_v);

/**
 * @method canvas_measure_text
 * 计算文本所占的宽度。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {const wchar_t*} str 字符串。
 * @param {uint32_t} nr 字符数。
 *
 * @return {float_t} 返回文本所占的宽度。
 */
float_t canvas_measure_text(canvas_t* c, const wchar_t* str, uint32_t nr);

/**
 * @method canvas_measure_utf8
 * 计算文本所占的宽度。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_measure_text
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} str 字符串。
 *
 * @return {float_t} 返回文本所占的宽度。
 */
float_t canvas_measure_utf8(canvas_t* c, const char* str);

/**
 * @method canvas_draw_text
 * 绘制文本。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {const wchar_t*} str 字符串。
 * @param {uint32_t} nr 字符数。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_text(canvas_t* c, const wchar_t* str, uint32_t nr, xy_t x, xy_t y);

/**
 * @method canvas_draw_utf8
 * 绘制文本。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_draw_text
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} str 字符串。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_utf8(canvas_t* c, const char* str, xy_t x, xy_t y);

/**
 * @method canvas_draw_text_in_rect
 * 绘制文本。
 *
 * @param {canvas_t*} c canvas对象。
 * @param {const wchar_t*} str 字符串。
 * @param {uint32_t} nr 字符数。
 * @param {const rect_t*} r 矩形区域。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_text_in_rect(canvas_t* c, const wchar_t* str, uint32_t nr, const rect_t* r);

/**
 * @method canvas_draw_utf8_in_rect
 * 绘制文本。
 *
 * > 供脚本语言使用。
 *
 * @alias canvas_draw_text_in_rect
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {const char*} str 字符串。
 * @param {const rect_t*} r 矩形区域。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_utf8_in_rect(canvas_t* c, const char* str, const rect_t* r);

/**
 * @method canvas_draw_icon
 * 绘制图标。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {bitmap_t*} img 图片对象。
 * @param {xy_t} cx 中心点x坐标。
 * @param {xy_t} cy 中心点y坐标。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_icon(canvas_t* c, bitmap_t* img, xy_t cx, xy_t cy);

/**
 * @method canvas_draw_image
 * 绘制图片。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 * @param {bitmap_t*} img 图片对象。
 * @param {rect_t*} src 源区域。
 * @param {rect_t*} dst 目的区域。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_draw_image(canvas_t* c, bitmap_t* img, rect_t* src, rect_t* dst);

/**
 * @method canvas_get_vgcanvas
 * 获取vgcanvas对象。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 *
 * @return {vgcanvas_t*} 返回vgcanvas对象。
 */
vgcanvas_t* canvas_get_vgcanvas(canvas_t* c);

/**
 * @method canvas_cast
 * 转换为canvas对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {canvas_t*} c canvas对象。
 *
 * @return {canvas_t*} canvas对象。
 */
canvas_t* canvas_cast(canvas_t* c);

/**
 * @method canvas_reset
 * 释放相关资源。
 *
 * @annotation ["scriptable"]
 * @param {canvas_t*} c canvas对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t canvas_reset(canvas_t* c);

/*private*/
ret_t canvas_draw_image_ex(canvas_t* c, bitmap_t* img, image_draw_type_t draw_type,
                           const rect_t* dst);
ret_t canvas_draw_image_at(canvas_t* c, bitmap_t* img, xy_t x, xy_t y);
ret_t canvas_draw_icon_in_rect(canvas_t* c, bitmap_t* img, rect_t* r);

ret_t canvas_draw_image_center(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_patch3_x(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_patch3_x_scale_y(canvas_t* c, bitmap_t* img, rect_t* dst);

ret_t canvas_draw_image_patch3_y(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_patch3_y_scale_x(canvas_t* c, bitmap_t* img, rect_t* dst);

ret_t canvas_draw_image_patch9(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_repeat(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_repeat_x(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_repeat_y(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_scale(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_scale_w(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_scale_h(canvas_t* c, bitmap_t* img, rect_t* dst);
ret_t canvas_draw_image_scale_down(canvas_t* c, bitmap_t* img, rect_t* src, rect_t* dst);

ret_t canvas_draw_line(canvas_t* c, xy_t x1, xy_t y1, xy_t x2, xy_t y2);
ret_t canvas_draw_char(canvas_t* c, wchar_t chr, xy_t x, xy_t y);
ret_t canvas_draw_image_matrix(canvas_t* c, bitmap_t* img, matrix_t* matrix);
ret_t canvas_set_fps(canvas_t* c, bool_t show_fps, uint32_t fps);
ret_t canvas_set_font_manager(canvas_t* c, font_manager_t* font_manager);

ret_t canvas_begin_frame(canvas_t* c, rect_t* dirty_rect, lcd_draw_mode_t draw_mode);
ret_t canvas_end_frame(canvas_t* c);
ret_t canvas_test_paint(canvas_t* c, bool_t pressed, xy_t x, xy_t y);

/*save/restore works for awtk web only*/
ret_t canvas_save(canvas_t* c);
ret_t canvas_restore(canvas_t* c);

END_C_DECLS

#endif /*TK_CANVAS_H*/
