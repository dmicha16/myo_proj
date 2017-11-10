#include "stdafx.h"
#include "MyoData.h"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <Windows.h>

#include <chrono>
#include <thread>

#define _USE_MATH_DEFINES

#include <myo\myo.hpp>
using namespace std;



MyoData::MyoData()
{
	//Vincent's intial commit
}

int MyoData::ConnectToMyo()
{
	try {

		myo::Hub hub("com.project.myo_project");		

		cout << "Attempting to find a Myo..." << std::endl;

		myo::Myo* myo = hub.waitForMyo(10000);

		if (!myo) {
			throw runtime_error("Unable to find a Myo!");
		}

		cout << "Connected to a Myo armband!" << std::endl << std::endl;	

		hub.addListener(this);

		bool switchMode = false;
		while (true) {
			hub.run(1000 / 100);						
			switchMode = SwitchModes();		

			if (switchMode == true)
				break;
			else
				continue;
		}

		if (switchMode == true)	{
			while (true) {
				switchMode = false;
				hub.run(1000 / 100);
				switchMode = ManualMode();

				if (switchMode == true)
					break;
				else
					continue;
			}
		}else if (switchMode == true) {
			while (true) {
				switchMode = false;
				hub.run(1000 / 1);
				switchMode = PresetMode();

				if (switchMode == true)
					break;
				else
					continue;
			}
		}		
	}
	catch (const std::exception& e) {
		cerr << "Error: " << e.what() << endl;
		cerr << "Press enter to continue.";
		cin.ignore();
		return 1;
	}

}

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose) {
	currentPose = pose;
	isUnlocked = false;	

	myo->unlock(myo::Myo::unlockHold);
	
	myo->notifyUserAction();
}

int MyoData::ReturnGestureNumber(string incGesture) {

	int gestureNumber = 0;

	if (incGesture == "fist") {
		gestureNumber = 1;
		return gestureNumber;
	}
	else if (incGesture == "fingersSpread") {
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

bool MyoData::PresetMode() {
	cout << "yey you made it to preset mode" <<  "\n";
	return true;
}

bool MyoData::SwitchModes() {
	
	int gestureNumber = 0;
	gestureNumber = 0;
	
	switch (gestureNumber = ReturnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		cout << "You choose: 'Manual Mode'" << string(14, ' ');
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return true;
		break;

	case 2:
		std::cout << '\r';
		cout << "You choose: 'Preset Mode'" << string(14, ' ');
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));		
		return false;
		break;

	default:
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << '\r';
		cout << "FIST: Manual mode, " << "SPREAD: Preset mode" << string(14, ' ');
		break;
	}
}

bool MyoData::ManualMode() {

	int gestureNumber = 0;
	gestureNumber = 0;
		switch (gestureNumber = ReturnGestureNumber(currentPose.toString())) {
		case 1:
			std::cout << '\r';
			cout << "FIST: Moving end effector: DOWN" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;

		case 2:
			std::cout << '\r';
			cout << "SPREAD: Moving end effector: UP" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;

		case 3:
			std::cout << '\r'; 
			cout << "WAVEIN: Moving end effector: LEFT" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;

		case 4:
			std::cout << '\r';
			cout << "WAVEOUT: Moving end effector: RIGHT" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));						
			break;

		case 5:
			std::cout << '\r';
			cout << "DOUBLE TAP, you are QUITTING this mode" << string(14, ' ') << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			gestureNumber = 0;
			return true;
			break;

		case 6: 
			std::cout << '\r';
			cout << "You are in REST, nothing is happening..." << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			break;		
		default:
			std::cout << '\r';
			cout << "Manual mode." << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;
		}	
}

MyoData::~MyoData()
{	
}
