#include "adpdhandler/hal_adpd.hpp"

mbed::Serial comport(USBTX, USBRX); //!< Serial port object, for the F401RE this is connected to the onboard usb port

int adpd::comment(const char* string)
{
	int error = comport.printf(":%s\r\n",string);
	return error;
}

int adpd::debug(const char* string)
{
	int error = 0;
#ifndef NDEBUG
	error = comport.printf("%s\r\n", string);
#endif
	return error;
}

int adpd::log(const char* string)
{
	int error = comport.printf("%s\r\n", string);
	return error;
}