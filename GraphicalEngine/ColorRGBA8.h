#pragma once
#include <SDL\SDL.h>

namespace GraphicalEngine
{
  struct ColorRGBA8
  {
    ColorRGBA8() : r(0), g(0), b(0), a(0) { }

    ColorRGBA8(const Uint8& _colorForAll)
    {
      r = _colorForAll;
      g = _colorForAll;
      b = _colorForAll;
      a = _colorForAll;
    }
    //custom colored constructor
    ColorRGBA8(const Uint8& _r, const Uint8& _g, const Uint8& _b, const Uint8& _a)
    {
      //custom
      r = _r;
      g = _g;
      b = _b;
      a = _a;
    }

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
  };
}
