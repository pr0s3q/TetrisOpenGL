#include "GLFW/glfw3.h"

#include "KeyboardManager.h"

//---------------------------------------------------------------

KeyboardManager::KeyboardManager()
    : m_pressedKeys(7)
{
    m_pressedKeys.insert({ GLFW_KEY_W, false });
    m_pressedKeys.insert({ GLFW_KEY_S, false });
    m_pressedKeys.insert({ GLFW_KEY_A, false });
    m_pressedKeys.insert({ GLFW_KEY_D, false });
    m_pressedKeys.insert({ GLFW_KEY_L, false });
    m_pressedKeys.insert({ GLFW_KEY_Q, false });
    m_pressedKeys.insert({ GLFW_KEY_E, false });
}

//---------------------------------------------------------------

bool KeyboardManager::IsPressed(const int key)
{
    return m_pressedKeys[key];
}

//---------------------------------------------------------------

void KeyboardManager::SetPressedToFalse(const int key)
{
    m_pressedKeys[key] = false;
}

//---------------------------------------------------------------

void KeyboardManager::SetPressedToTrue(const int key)
{
    m_pressedKeys[key] = true;
}

//---------------------------------------------------------------
