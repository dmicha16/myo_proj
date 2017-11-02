#pragma once

#include <string>
#include <string.h>

using namespace std;

class ModeSwitch
{
public:
	ModeSwitch();

	int ReturnGestureNumber(string);

	void Switch(int, bool);
	void PresetMode(string, bool);
	void ManualMode(string, bool);
	char SendModeGesture();
	void StoreJson();
	~ModeSwitch();

private:
};
	

