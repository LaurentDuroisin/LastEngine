#ifndef ODFAEG_JOYSTICK
#define ODFAEG_JOYSTICK
namespace odfaeg {
////////////////////////////////////////////////////////////
/// \brief Defines the joystick buttons and axis code for each joystick button and axis.
///
////////////////////////////////////////////////////////////
class Joystick
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Constants related to joysticks capabilities
    ///
    ////////////////////////////////////////////////////////////
    enum
    {
        Count       = 8,  ///< Maximum number of supported joysticks
        ButtonCount = 32, ///< Maximum number of supported buttons
        AxisCount   = 8   ///< Maximum number of supported axes
    };

    ////////////////////////////////////////////////////////////
    /// \brief Axes supported by SFML joysticks
    ///
    ////////////////////////////////////////////////////////////
    enum Axis
    {
        X,    ///< The X axis
        Y,    ///< The Y axis
        Z,    ///< The Z axis
        R,    ///< The R axis
        U,    ///< The U axis
        V,    ///< The V axis
        PovX, ///< The X axis of the point-of-view hat
        PovY  ///< The Y axis of the point-of-view hat
    };
};
}
#endif // ODFAEG_JOYSTICK

