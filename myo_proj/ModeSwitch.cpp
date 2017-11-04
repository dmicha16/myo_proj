#include "stdafx.h"
#include "ModeSwitch.h"
#include <crtdbg.h>

#include <Windows.h>

#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdexcept>

#include <chrono>
#include <thread>
#include "MyoData.h"
#define _USE_MATH_DEFINES

#include <myo\myo.hpp>
using namespace std;

ModeSwitch::ModeSwitch()
{

}

int ModeSwitch::ReturnGestureNumber(string incGesture) {

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

void ModeSwitch::Switch(string recievedGesture, bool isUnlocked)
{
	int gestureNumber = ReturnGestureNumber(recievedGesture);
	if (gestureNumber == 1) {
		cout << "you are in manual mode";
		ManualMode(isUnlocked);
		
	}
	else {
		cout << "you are in preset mode";
		PresetMode(recievedGesture, isUnlocked);
	}
}
void ModeSwitch::ManualMode(bool isUnlocked){
	
	bool exitGesture = false;	
	do
	{		
		if (isUnlocked == false) {						

			myo::Pose pose;
			string newGesture;				
			int gestureNumber = 0;

			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			cout << gestureNumber;
			switch (gestureNumber) {
			case 1: cout << "you are in fist mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));				
				gestureNumber = ReturnGestureNumber(newGesture);
				break;

			case 2: cout << "you are in spread mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);
				break;

			case 3: cout << "you are in waveIn mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);
				break;

			case 4: cout << "you are in waveOut mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				exitGesture = true;
				gestureNumber = 0;
				cout << "you are QUITTING THIS mode";
				//PresetMode(recievedGesture, isUnlocked);
				break;

			case 5: cout << "DOUBLE TAP";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);
				break;

			case 6: cout << "you are in rest mode, nothing is happening";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);
				break;

			case 7: cout << "you are in waveIn mode";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);
				break;
			default: cout << "there are no gestures given";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				gestureNumber = ReturnGestureNumber(newGesture);

				myo::Pose pose;
				newGesture = pose.toString();
				break;
			}
		}
	} while (exitGesture == false);		
}
void ModeSwitch::PresetMode(string recievedGesture, bool isUnlocked) {

}

char ModeSwitch::SendModeGesture() {
	return 0;
}

void ModeSwitch::StoreJson() {
}

ModeSwitch::~ModeSwitch(){
}
