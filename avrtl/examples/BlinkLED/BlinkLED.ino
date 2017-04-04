#include <avrtl.h>

using namespace atl;

constexpr Pin RedLED = Pin(atl::std::PortB, 3);
constexpr Pin GreenLED = Pin(atl::std::PortB, 4);

void setup() {
    RedLED.Direction = Output;
    RedLED.Set();

    GreenLED.Direction = Output;
    GreenLED.Clear();
}

void loop() {
   _delay_ms(1000);
   RedLED.Flip();
   GreenLED.Flip(); 
}

