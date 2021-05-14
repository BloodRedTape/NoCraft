#ifndef UI_HPP
#define UI_HPP

#include <string>
#include "platform/events.hpp"
#include "utils/rect.hpp"

using namespace StraitX;

class UI{
private:
    friend class Minecraft;

    static void SetUIState(const Event &e);

    static void ResetUIState();
public:

    static bool Button(const std::string &text, Vector2i position, Vector2i size);
};

class VerticalLayout{
private:
    Vector2i m_LayoutOrigin;
    Vector2i m_LayoutSize;
    Vector2i m_ButtonSize;
    s32 m_ButtonDistance;
    s32 m_CurrentIndex;
public:
    VerticalLayout(Vector2i layout_origin, Vector2i layout_size, Vector2i button_size, s32 button_distance);

    bool Button(const std::string &text);

    void Reset();
};

#endif //UI_HPP