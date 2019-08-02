#pragma once

#include "types.h"

namespace agge {

enum bits_per_pixel { bpp32 = 32, bpp24 = 24, bpp16 = 16, bpp8 = 8 };

#pragma pack(push, 1)
struct pixel32_rgba {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
  pixel32_rgba() : r(0), g(0), b(0), a(0) {
  }
  pixel32_rgba(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) : r(rr), g(gg), b(bb), a(aa) {
  }
};

struct pixel32_abgr {
  uint8_t a;
  uint8_t b;
  uint8_t g;
  uint8_t r;
  pixel32_abgr() : a(0), b(0), g(0), r(0) {
  }
  pixel32_abgr(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) : a(aa), b(bb), g(gg), r(rr) {
  }
};

struct pixel32_bgra {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
  pixel32_bgra() : b(0), g(0), r(0), a(0) {
  }
  pixel32_bgra(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) : b(bb), g(gg), r(rr), a(aa) {
  }
};

struct pixel32_argb {
  uint8_t a;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  pixel32_argb() : a(0), r(0), g(0), b(0) {
  }
  pixel32_argb(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) : a(aa), r(rr), g(gg), b(bb) {
  }
};

struct pixel24_rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  pixel24_rgb() : r(0), g(0), b(0) {
  }
  pixel24_rgb(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr), g(gg), b(bb) {
  }
};

struct pixel24_bgr {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  pixel24_bgr() : b(0), g(0), r(0) {
  }
  pixel24_bgr(uint8_t rr, uint8_t gg, uint8_t bb) : b(bb), g(gg), r(rr) {
  }
};

struct pixel16_bgr565 {
  uint16_t b : 5;
  uint16_t g : 6;
  uint16_t r : 5;

  pixel16_bgr565() : b(0), g(0), r(0) {
  }
  pixel16_bgr565(uint8_t rr, uint8_t gg, uint8_t bb) : b(bb), g(gg), r(rr) {
  }
};

struct pixel16_rgb565 {
  uint16_t r : 5;
  uint16_t g : 6;
  uint16_t b : 5;

  pixel16_rgb565() : r(0), g(0), b(0) {
  }
  pixel16_rgb565(uint8_t rr, uint8_t gg, uint8_t bb) : r(rr), g(gg), b(bb) {
  }
};

struct pixel8 {
  uint8_t a;
  pixel8() : a(0) {
  }
  pixel8(uint8_t aa) : a(aa) {
  }
};
#pragma pack(pop)

#include "pixel_a.h"
#include "pixel_set_a.h"
#include "pixel_convert.h"

template <typename PixelTargetT, typename PixelSrcT>
inline void pixel_blend(PixelTargetT& t, const PixelSrcT& s, uint8_t a) {
  if (a > 0xf4) {
    if (sizeof(t) == sizeof(s) || sizeof(t) == 4) {
      t.r = s.r;
      t.g = s.g;
      t.b = s.b;
    } else {
      t.r = s.r >> 3;
      t.g = s.g >> 2;
      t.b = s.b >> 3;
    }
  } else if (a > 0x01) {
    uint8_t m_a = 0xff - a;
    if (sizeof(t) == 2) {
      if (sizeof(s) == 2) {
        t.r = s.r;
        t.g = s.g;
        t.b = s.b;
      } else {
        t.r = (s.r * a + (t.r << 3) * m_a) >> 11;
        t.g = (s.g * a + (t.g << 2) * m_a) >> 10;
        t.b = (s.b * a + (t.b << 3) * m_a) >> 11;
      }
    } else if (sizeof(s) == 2) {
      if (sizeof(t) == 2) {
        t.r = s.r;
        t.g = s.g;
        t.b = s.b;
      } else {
        t.r = ((s.r << 3) * a + t.r * m_a) >> 11;
        t.g = ((s.g << 2) * a + t.g * m_a) >> 10;
        t.b = ((s.b << 3) * a + t.b * m_a) >> 11;
      }
    } else {
      t.r = (s.r * a + t.r * m_a) >> 8;
      t.g = (s.g * a + t.g * m_a) >> 8;
      t.b = (s.b * a + t.b * m_a) >> 8;
    }
  }
}

template <>
inline void pixel_blend(pixel16_bgr565& t, const pixel32_rgba& s, uint8_t a) {
  if (a > 0xf4) {
    t.r = s.r >> 3;
    t.g = s.g >> 2;
    t.b = s.b >> 3;
  } else if (a > 0x01) {
    uint8_t m_a = 0xff - a;
    t.r = (s.r * a + (t.r << 3) * m_a) >> 11;
    t.g = (s.g * a + (t.g << 2) * m_a) >> 10;
    t.b = (s.b * a + (t.b << 3) * m_a) >> 11;
  }
}

}  // namespace agge
