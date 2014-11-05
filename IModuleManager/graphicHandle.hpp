#ifndef ODFAEG_GRAPHIC_HANDLE
#define ODFAEG_GRAPHIC_HANDLE
namespace odfaeg {
/**
* \brief struct for the graphics handle.
*/
struct GraphicsHandle {
       /**
       * \brief the type of the handle.
       */
       enum Type {OpenGL, DirectX} type;
       /**
       * \brief the pointer to the handle.
       */
       std::inptr_t handle;
};
}
#endif // GRAPHIC_HANDLE
