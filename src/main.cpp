#include "mbed.h"

using namespace mbed;

DigitalOut myled(LED1);

int main() {
    #ifdef MBED_DEBUG
    while(1) {
        myled = 1;
        wait(1.0);
        myled = 0;
        wait(1.0);
    }
    #endif
}