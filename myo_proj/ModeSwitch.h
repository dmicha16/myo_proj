#pragma once

#include <string>
#include <string.h>

class ModeSwitch
{
public:
	ModeSwitch();

	void ReadGesture(std::string);

	void Switch(std::string);
	char SendModeGesture();
	void StoreJson();
	~ModeSwitch();

private:
};
	

