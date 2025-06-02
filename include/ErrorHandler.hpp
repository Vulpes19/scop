#pragma once

#include <stdexcept>
#include <string>

class ErrorHandler : public std::exception
{
    public:
        ErrorHandler(std::string, const char*, int);
        virtual ~ErrorHandler(void) noexcept;
        const char* what(void) const noexcept override;
        const char* getFile(void) const noexcept;
        int			getLine(void) const noexcept;
    private:
        std::string errorMsg;
        const char* fileName;
        int			line;
};