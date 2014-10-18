#ifndef IEXCEPTION_H
#define IEXCEPTION_H

#include <exception>
#include <execinfo.h>
#include <vector>
#include <string>
#include <iostream>

#define THROW_ARGS __FILE__, __LINE__, __func__

namespace LE
{
    class IException : std::exception
    {
    public :
        enum ExceptionType{OTHER};
        typedef std::uint32_t ExceptionCode;

        virtual const std::string & function(void) const = 0;
        virtual std::size_t line(void) const = 0;
        virtual const std::string & file(void) const = 0;
        virtual const char * what(void) const noexcept = 0;
        virtual const std::vector<std::string> & stacktrace(void) const = 0;
        virtual ExceptionType type(void) const = 0;
        virtual std::uint32_t code(void) const = 0;
    };

    template<IException::ExceptionType>
    class IExceptionTyped : public IException
    {
    };

    template<IException::ExceptionType t_type, IException::ExceptionCode t_code>
    class Exception : public IExceptionTyped<t_type>
    {
    public :
        Exception(const std::string & message, std::string && file, std::size_t line, std::string && function);
        Exception(std::string && message, std::string && file, std::size_t line, std::string && function);

        virtual ~Exception(void) = default;

        virtual const std::string & function(void) const{ return m_function; }
        virtual std::size_t line(void) const{ return m_line; }
        virtual const std::string & file(void) const{ return m_file; }
        virtual const char * what(void) const noexcept{ return m_message.c_str(); }
        virtual const std::vector<std::string> & stacktrace(void) const { return m_stacktrace; }
        virtual IException::ExceptionType type(void) const{ return t_type; }
        virtual IException::ExceptionCode code(void) const{ return t_code; }
        void current_stacktrace(std::vector<std::string> & v);
    private :
        const std::string m_message;
        const std::string m_file;
        const std::size_t m_line;
        const std::string m_function;
        std::vector<std::string> m_stacktrace;
    };

    template<IException::ExceptionType t_type, IException::ExceptionCode t_code>
    Exception<t_type, t_code>::Exception(const std::string & message, std::string && file, std::size_t line, std::string && function)
        : m_message(message), m_file(std::move(file)), m_line(line), m_function(std::move(function))
    {
        current_stacktrace(m_stacktrace);
    }

    template<IException::ExceptionType t_type, IException::ExceptionCode t_code>
    Exception<t_type, t_code>::Exception(std::string && message, std::string && file, std::size_t line, std::string && function)
        : m_message(message), m_file(std::move(file)), m_line(line), m_function(std::move(function))
    {
        current_stacktrace(m_stacktrace);
    }


    template<IException::ExceptionType t_type, IException::ExceptionCode t_code>
    void Exception<t_type, t_code>::current_stacktrace(std::vector<std::string> & v)
    {
        #ifdef __GNU_LIBRARY__
                void * buffer[8];
                std::size_t size = backtrace(buffer, 8);
                char ** symbols = backtrace_symbols(buffer, size);
                v.reserve(size);
                for( std::size_t i = 2; i < size; ++i)
                    v.push_back(symbols[i]);
        #endif
    }
}

inline std::ostream & operator<<(std::ostream & stream, LE::IException & e)
{
    stream << "Exception code " << e.type() << "x" << e.code() << " : " << e.what() << std::endl
           << e.file() << " on line " << e.line() << " in function " << e.function() << std::endl
           << "Stack trace : " << std::endl;

    for(const auto & line : e.stacktrace() )
        stream << line << std::endl;

    stream << "End of stack trace.";
}

#endif // IEXCEPTION_H
