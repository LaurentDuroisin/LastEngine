#ifndef ODFAEG_SYSTEM_EVENT
#define ODFAEG_SYSTEM_EVENT
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "keyboard.hpp"
#include "mouse.hpp"
#include "joystick.hpp"
namespace odfaeg {
////////////////////////////////////////////////////////////
/// \brief Defines a system event and its parameters
///
////////////////////////////////////////////////////////////
class SystemEvent {
    ////////////////////////////////////////////////////////////
    /// \brief Size events parameters (Resized)
    ///
    ////////////////////////////////////////////////////////////
    struct SizeEvent
    {
        unsigned int width;  ///< New width, in pixels
        unsigned int height; ///< New height, in pixels
    };

    ////////////////////////////////////////////////////////////
    /// \brief Keyboard event parameters (KeyPressed, KeyReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct KeyEvent
    {
        Keyboard::Key code;    ///< Code of the key that has been pressed
    };

    ////////////////////////////////////////////////////////////
    /// \brief Text event parameters (TextEntered)
    ///
    ////////////////////////////////////////////////////////////
    struct TextEvent
    {
        Uint32 unicode; ///< UTF-32 unicode value of the character
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse move event parameters (MouseMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseMoveEvent
    {
        int x; ///< X position of the mouse pointer, relative to the left of the owner window
        int y; ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons events parameters
    ///        (MouseButtonPressed, MouseButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseButtonEvent
    {
        Mouse::Button button; ///< Code of the button that has been pressed
        int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
        int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse wheel events parameters (MouseWheelMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseWheelEvent
    {
        int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
        int x;     ///< X position of the mouse pointer, relative to the left of the owner window
        int y;     ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick connection events parameters
    ///        (JoystickConnected, JoystickDisconnected)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickConnectEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick axis move event parameters (JoystickMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickMoveEvent
    {
        unsigned int   joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        Joystick::Axis axis;       ///< Axis on which the joystick moved
        float          position;   ///< New position on the axis (in range [-100 .. 100])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick buttons events parameters
    ///        (JoystickButtonPressed, JoystickButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickButtonEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        unsigned int button;     ///< Index of the button that has been pressed (in range [0 .. Joystick::ButtonCount - 1])
    };

    enum Type {
         NoEvent,                ///< No events are generated.
         WindowClosed,           ///< The window requested to be closed (no data)
         WindowResized,          ///< The window was resized (data in event.size)
         LostFocus,              ///< The window lost the focus (no data)
         GainedFocus,            ///< The window gained the focus (no data)
         TextEntered,            ///< A character was entered (data in event.text)
         KeyPressed,             ///< A key was pressed (data in event.key)
         KeyReleased,            ///< A key was released (data in event.key)
         MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel)
         MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
         MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
         MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
         MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
         MouseLeft,              ///< The mouse cursor left the area of the window (no data)
         JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
         JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
         JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
         JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
         JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)

         Count                   ///< Keep last -- the total number of event types
    };
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Type type; ///< Type of the event
    union
    {
        SizeEvent            size;            ///< Size event parameters (Event::Resized)
        KeyEvent             key;             ///< Key event parameters (Event::KeyPressed, Event::KeyReleased)
        TextEvent            text;            ///< Text event parameters (Event::TextEntered)
        MouseMoveEvent       mouseMove;       ///< Mouse move event parameters (Event::MouseMoved)
        MouseButtonEvent     mouseButton;     ///< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
        MouseWheelEvent      mouseWheel;      ///< Mouse wheel event parameters (Event::MouseWheelMoved)
        JoystickMoveEvent    joystickMove;    ///< Joystick move event parameters (Event::JoystickMoved)
        JoystickButtonEvent  joystickButton;  ///< Joystick button event parameters (Event::JoystickButtonPressed, Event::JoystickButtonReleased)
        JoystickConnectEvent joystickConnect; ///< Joystick (dis)connect event parameters (Event::JoystickConnected, Event::JoystickDisconnected)
    };
};
}
#endif // ODFAEG_SYSTEM_EVENT

