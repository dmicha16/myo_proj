#include "stdafx.h"
#include "ModeSwitch.h"
#include <crtdbg.h>

#include <Windows.h>

#include <string>
#include <string.h>
#include <iostream>

using namespace std;

ModeSwitch::ModeSwitch()
{

}

void ModeSwitch::ReadGesture(string incGesture)
{
	string localGesture = incGesture;
	OutputDebugString(L"ModeSwitch::ReadGesture - ");
	// TODO: fix this and find .h
	//_RPT1(localGesture); 	
	Switch(localGesture);
}

void ModeSwitch::Switch(string localGesture)
{
	// TODO: Not sure if it's actually giving 'locked', gotta look into that
	if (localGesture == "locked")
	{
		
	}

	string mode = "preset";

	if (mode == "preset")
	{
		cout << "you are in preset mode";
	}
	else
	{
		cout << "you are in preset mode";
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
