#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <functional>
#include "platform/events.hpp"
#include "core/array_ptr.hpp"
#include "utils/rect.hpp"

using namespace StraitX;

class UI{
private:
    friend class Minecraft;

    static constexpr size_t s_FontSize = 50;

    static void UpdateUIState(const Event &e);

    static void ResetUIState();

    static bool EventMatch(std::function<bool(const Event &e)> matcher);
public:

    static bool Button(const std::string &text, Vector2i position, Vector2i size);

    static void Text(const std::string &text, Vector2i position, Vector2i size);

    static void Selector(ArrayPtr<std::string> names, int &current_index, Vector2i position, Vector2i size);

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

    std::pair<Vector2i, Vector2i> NextPosAndSize();

    bool Button(const std::string &text);

    void Selector(ArrayPtr<std::string> names, int &current_index);

    void Reset();
};

#endif //UI_HPP