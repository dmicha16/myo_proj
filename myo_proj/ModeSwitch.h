#pragma once

#include <string>
#include <string.h>

using namespace std;

class ModeSwitch
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
	

