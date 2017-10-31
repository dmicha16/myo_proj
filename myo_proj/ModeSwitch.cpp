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

int ModeSwitch::ReturnGestureNumber(string incGesture, bool isUnlocked)
{
	int gestureNumber = 0;
	if (incGesture == "fist")
	{
		gestureNumber = 1;
	}
	else if (incGesture == "spread")
	{
		gestureNumber = 2;
	}
	else if (incGesture == "waveIn")
	{
		gestureNumber = 3;
	}
	else if (incGesture == "waveOut")
	{
		gestureNumber = 4;
	}
	else if (incGesture == "doubleTap")
	{
		gestureNumber = 5;
	}
	
	return gestureNumber;
}

void ModeSwitch::Switch(int gestureNumber, bool localIsUnlocked)
{	
	
}

void ModeSwitch::PresetMode(string recievedGesture, bool isUnlocked)
{	
	int gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);

	if (gestureNumber == 1)
	{
		ManualMode(recievedGesture, isUnlocked);
	}
	else
	{
		cout << "you are in preset mode \n";
	}
}
void ModeSwitch::ManualMode(string recievedGesture, bool isUnlocked)
{
	cout << "you are in manual mode, what would you like to do? \n"
		<< " ;";	 

	int gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);

	if (isUnlocked == false)
	{
		switch (gestureNumber)
		{
		case 1: cout << "you are in fist mode \n";			
			//PresetMode(recievedGesture, isUnlocked);
			break;
		case 2: cout << "you are in quitting this mode \n";
			gestureNumber = 0;
			break;
		case 3: cout << "you are in waveIn mode \n";
			break;
		case 4: cout << "you are in waveOut mode \n";		
			break;				
		default:
			break;
		}
	}

	//Switch(gestureNumber, isUnlocked);
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
