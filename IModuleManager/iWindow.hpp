#ifndef ODFAEG_IWINDOW
#define ODFAEG_IWINDOW
namespace odfaeg {
/**
* \brief Interface for each window.
*/
class IWindow
{
     public :
          /**
          * \brief resize the window.
          */
          virtual void resize(uint32_t , uint32_t) = 0;
          /**
          * \brief set the title of the window.
          * \param reference : the title of the window.
          */
          virtual void setTitle(const std::string &) = 0;
          /**
          * \brief set the title of the window.
          * \param rvalue : the title of the window.
          */
          virtual void setTitle(std::string &&) = 0;
          /**
          * \brief get the title of the window.
          * \return reference : the title of the window.
          */
          virtual const std::string & getTitle(void)const = 0;
          /**
          * \brief get the width of the window.
          */
          virtual uint32_t getWidth(void)const = 0;
          /**
          * \brief get the height of the window.
          */
          virtual uint32_t getHeight(void)const = 0;
          /**
          * \brief switch the window to fullscreen or windowed mode.
          * \param switch to fullscreen mode (true) or windowed mode (false) ?
          */
          virtual void setFullscreen(bool) = 0;
          /**
          * \brief maximize the window.
          */
          virtual void maximize(void) = 0;
          /**
          * \brief minimize the window.
          */
          virtual void minimize(void) = 0; // TODO bool fullscreen() ou bool isFullscreen();
}
}
#endif // ODFAEG_IWINDOW
