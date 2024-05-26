#include <AccelStepper.h>
#include <DMXSerial.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

AccelStepper stepper3(AccelStepper::FULL2WIRE, 2, 3);
Adafruit_NeoPixel pixels(1, 6, NEO_RGB + NEO_KHZ800);

// This Example receives the 3 values starting with this channel:
const int startChannel = 1;


void setup()
{

	stepper3.setMaxSpeed(150.0);
	stepper3.setAcceleration(100.0);
	stepper3.move(-1000);

	DMXSerial.init(DMXReceiver);
	DMXSerial.maxChannel(5);

	pixels.begin();
	pixels.show(); // Initialize all pixels to 'off'
}

void loop()
{
	pixels.setPixelColor(0, pixels.Color(
															DMXSerial.read(startChannel),
															DMXSerial.read(startChannel + 1),
															DMXSerial.read(startChannel + 2)));
	pixels.show();
	stepper3.moveTo(DMXSerial.read(startChannel + 3)*4);
	stepper3.run();

}

// End.