#include "stdafx.h"
#include "ModeSwitch.h"
#include <crtdbg.h>

#include <Windows.h>

#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>  

#include <chrono>
#include <thread>

#include <myo\myo.hpp>
using namespace std;

ModeSwitch::ModeSwitch()
{

}

int ModeSwitch::ReturnGestureNumber(string incGesture, bool isUnlocked) {

	int gestureNumber = 0;

	if (incGesture == "fist"){
		gestureNumber = 1;
		return gestureNumber;
	}
	else if (incGesture == "spread"){
		gestureNumber = 2;
		return gestureNumber;
	}
	else if (incGesture == "waveIn") {
		gestureNumber = 3;
		return gestureNumber;
	}
	else if (incGesture == "waveOut") {
		gestureNumber = 4;
		return gestureNumber;
	}
	else if (incGesture == "doubleTap") {
		gestureNumber = 5;
		return gestureNumber;
	}
	else if (incGesture == "rest") {
		gestureNumber = 6;
		return gestureNumber;
	}
	else {
		gestureNumber = 0;
		return gestureNumber;
	}	
	
}

void ModeSwitch::Switch(int gestureNumber, bool localIsUnlocked)
{	
	
}

void ModeSwitch::PresetMode(string recievedGesture, bool isUnlocked) {	
	int gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);
	myo::Pose pose;
	if (gestureNumber == 1) {
		ManualMode(recievedGesture, isUnlocked);
	} else {		
		cout << "you are in preset mode";
	}
}
void ModeSwitch::ManualMode(string recievedGesture, bool isUnlocked){
	cout << "you are in manual mode";

	if (isUnlocked == false) {

		bool exitGesture = false;
		int gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);
		do
		{			
			cout << gestureNumber;			
			int gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);
			switch (gestureNumber) {
			case 1: cout << "you are in fist mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));								
				goto reset;
				break;
			case 2: cout << "you are in spread mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				break;
			case 3: cout << "you are in waveIn mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				break;
			case 4: cout << "you are in waveOut mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				exitGesture = true;
				gestureNumber = 0;
				PresetMode(recievedGesture, isUnlocked);
				break;
			case 5: cout << "DOUBLE TAP";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				break;
			default: cout << "you are in rest mode, nothing is happening";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				break;
			}		
			reset:
			gestureNumber = ReturnGestureNumber(recievedGesture, isUnlocked);

		} while (exitGesture == false);
		
	}
	//Switch(gestureNumber, isUnlocked);
}

char ModeSwitch::SendModeGesture() {
	return 0;
}

void ModeSwitch::StoreJson() {
}

ModeSwitch::~ModeSwitch(){
}
