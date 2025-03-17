#include "ErrorHandler.hpp"

ErrorHandler::ErrorHandler(std::string errorMsg, const char* fileName, int line) : errorMsg(errorMsg), fileName(fileName), line(line)
{}

ErrorHandler::~ErrorHandler(void) noexcept
{}

const char* ErrorHandler::what(void) const noexcept
{
	return (errorMsg.c_str());
}

const char* ErrorHandler::getFile(void) const noexcept
{
	return (fileName);
}

int	ErrorHandler::getLine(void) const noexcept
{
	return (line);
}