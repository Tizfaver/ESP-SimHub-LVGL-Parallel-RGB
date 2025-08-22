#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>

class SHCustomProtocol {
private:

public:
	void setup() { }

	void loop() { 
		delay(50); 
	}

	void read() { //New data string is coming, do whatever you need with this string.
		String newStringData = FlowSerialReadStringUntil('\n');
	}

	void idle() { }
};

#endif