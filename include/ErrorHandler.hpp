#pragma once

#include <stdexcept>

class ErrorHandler : public std::exception
{
    public:
        ErrorHandler(std::string, const char*, int);
        virtual ~ErrorHandler(void) noexcept;
        const char* what(void) const noexcept override;
        const char* getFile(void) const noexcept;
        int			getLine(void) const noexcept;
    private:
        const char* errorMsg;
        const char* fileName;
        int			line;
};