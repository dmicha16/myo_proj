#include "stdafx.h"
#include "ModeSwitch.h"
#include <crtdbg.h>

#include <Windows.h>

#include <string>
#include <string.h>

using namespace std;

ModeSwitch::ModeSwitch()
{

}

void ModeSwitch::ReadGesture(std::string incGesture)
{
	string localGesture = incGesture;
	OutputDebugString(L"ModeSwitch::ReadGesture - ");
	// TODO: fix this and find .h
	//_RPT1(localGesture); 	
	Switch(localGesture);
}

void ModeSwitch::Switch(string localGesture)
{
	while (localGesture != "fist")
	{
		
	}

}

char ModeSwitch::SendModeGesture()
{
	return 0;
}

void ModeSwitch::StoreJson()
{
}

ModeSwitch::~ModeSwitch()
{
}
