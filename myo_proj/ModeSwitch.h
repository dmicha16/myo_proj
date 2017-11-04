#pragma once

#include <string>
#include <string.h>
#include <myo\myo.hpp>

using namespace std;

class ModeSwitch : public myo::DeviceListener
{
public:
	ModeSwitch();

	int ReturnGestureNumber(string);	

	void Switch(string, bool);
	void PresetMode(string, bool);
	void ManualMode(bool);
	char SendModeGesture();
	void StoreJson();
	~ModeSwitch();

private:
};
	

