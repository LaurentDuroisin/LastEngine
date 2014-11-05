#ifndef ODFAEG_MOUSE
#define ODFAEG_MOUSE
namespace odfaeg {
////////////////////////////////////////////////////////////
/// \brief Defines the mouse button code for each mouse button.
///
////////////////////////////////////////////////////////////
class Mouse
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons
    ///
    ////////////////////////////////////////////////////////////
    enum Button
    {
        Left,       ///< The left mouse button
        Right,      ///< The right mouse button
        Middle,     ///< The middle (wheel) mouse button
        XButton1,   ///< The first extra mouse button
        XButton2,   ///< The second extra mouse button

        ButtonCount ///< Keep last -- the total number of mouse buttons
    };
};
}
#endif // ODFAEG_MOUSE
