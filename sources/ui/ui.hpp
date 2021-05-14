#ifndef UI_HPP
#define UI_HPP

#include <string>
#include "platform/events.hpp"
#include "render/render_2d.hpp"

class UI{
private:
    friend class Minecraft;

    static void SetUIState(const Event &e);

    static void ResetUIState();
public:

    static bool Button(const std::string &text, Vector2i position, Vector2i size);
};

#endif //UI_HPP