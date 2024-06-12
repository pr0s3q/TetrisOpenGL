#pragma once

//--------------------------------------------------------------

enum class Key
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ROTATE,
    DEBUG_KEY_1,
    ESC
};

//---------------------------------------------------------------

#ifdef _DEBUG

inline const char* KeyToString(const Key key)
{
    switch (key)
    {
        case Key::UP:
            return "UP";
        case Key::DOWN:
            return "DOWN";
        case Key::LEFT:
            return "LEFT";
        case Key::RIGHT:
            return "RIGHT";
        case Key::ROTATE:
            return "ROTATE";
        case Key::DEBUG_KEY_1:
            return "DEBUG_KEY_1";
        case Key::ESC:
            return "ESC";
    }
}

#endif
