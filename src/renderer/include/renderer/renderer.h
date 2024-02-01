#pragma once
#include <utils/utils.h>

namespace wind {
class Renderer {
public:
    static void clear(ivec4 color);
    static void drawRectangle(vec4 rect, vec4 color);
};

} // namespace wind