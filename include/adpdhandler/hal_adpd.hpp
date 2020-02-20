#ifndef _HAL_ADPD
#define _HAL_ADPD

#include "mbed.h"
#include "mbed_error.h"
//TODO: This will hold the abstractions for reading and writing registers etc
namespace adpd
{
    /**
    * Prints a comment to the console
    *
    * Comments are prefaced by a ":"
    * 
    */
    int comment(const char* string);

    /**
    * Prints a debug message to the console. If a release build nothing is printed
    *
    * Comments are prefaced by a ":"
    *
    */
    int debug(const char* string);
    
    /**
    * Generic function for printing a message to the console
    *
    *
    */
    int log(const char* string);
}
#endif