#include <avrtl.h>

using namespace atl;

constexpr Pin RedLED = Pin(atl::std::PortB, 2);
constexpr Pin GreenLED = Pin(atl::std::PortB, 3);
constexpr Pin YellowLED = Pin(atl::std::PortB, 4);

void setup() {
  RedLED.Direction = atl::Output;
  GreenLED.Direction = atl::Output;
  YellowLED.Direction = atl::Output;

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

