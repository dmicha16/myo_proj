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

void ModeSwitch::ReadGesture(string incGesture, bool isUnlocked)
{
	string localGesture = incGesture;

	bool localIsUnlocked = isUnlocked;

	// TODO: fix this and find .h
	//_RPT1(localGesture); 	
	Switch(localGesture, localIsUnlocked);
}

void ModeSwitch::Switch(string localGesture, bool localIsUnlocked)
{
	cout << "do i get here yo";
	int gestureNumber = 0;
	cout << "this is what I got: " << localGesture << "\n";
	if (localGesture == "fist")
	{
		gestureNumber = 1;
	}
	else if (localGesture == "spread")
	{
		gestureNumber = 2;
	}
	else if (localGesture == "waveIn")
	{
		gestureNumber = 3;
	}
	else if (localGesture == "waveOut")
	{
		gestureNumber = 4;
	}

	//cout << localGesture << "\n";
	if (localIsUnlocked == false)
	{
		cout << "entered the normal if";
		switch (gestureNumber)
		{
		case 1: cout << "you are in fist mode \n";
			break;
		case 2: cout << "you are in spread mode \n";
			break;
		case 3: cout << "you are in waveIn mode \n";
			break;
		case 4: cout << "you are in waveOut mode \n";
			break;
		default:
			break;
		}
	}
	else
	{
		cout << "entered else";
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
