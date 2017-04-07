#include <avrtl.h>

using namespace atl;

const atl::DigitalPin<atl::std::DigitalPortB, 2> RedLED;
const atl::DigitalPin<atl::std::DigitalPortB, 3> GreenLED;
const atl::DigitalPin<atl::std::DigitalPortB, 4> YellowLED;

void setup() {
  RedLED.Direction.AsOutput();
  GreenLED.Direction.AsOutput();
  YellowLED.Direction.AsOutput();

  RedLED.Clear();
  GreenLED.Set();
  YellowLED.Set();
}

void loop() {
  _delay_ms(1000);
  RedLED.Flip();
  GreenLED.Flip();
  _delay_ms(1000);
  GreenLED.Flip();
  YellowLED.Flip();
  _delay_ms(1000);
  YellowLED.Flip();
  RedLED.Flip();
}

