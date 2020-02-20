#include "adpdhandler/hal_adpd.hpp"

int main() 
{
	adpd::log("Hello World");
	adpd::debug("This is a debug message");
	adpd::comment("This is a comment");
	return 0;
}