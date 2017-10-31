#pragma once

#include <string>
#include <string.h>

using namespace std;

class ModeSwitch
{
public:
	ModeSwitch();

	void ReadGesture(string, bool);

	void Switch(string, bool);
	char SendModeGesture();
	void StoreJson();
	~ModeSwitch();

private:
};
	

