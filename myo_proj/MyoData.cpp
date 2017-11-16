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
using json = nlohmann::json;

MyoData::MyoData()
{	
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

		while (true) {
			hub.run(1000 / 100);						
			mode_type_ = SwitchModes();		

			if (mode_type_ == 'M' || 'P' || 'D')
				break;
			else
				continue;
		}

		if (mode_type_ == 'M')	{

			while (true) {
				hub.run(1000 / 100);
				mode_type_ = ManualMode();

				if (mode_type_ == true)
					break;
				else
					continue;
			}
		} else if (mode_type_ == 'P') {

			while (true) {
				hub.run(1000 / 1);
				mode_type_ = PresetMode();

				if (mode_type_ == true)
					break;
				else
					continue;
			}
		} else if(mode_type_ == 'D') {

			while(true) {
				hub.run(1000 / 1);
				mode_type_ = PresetMode();

				if(mode_type_ == true)
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

char MyoData::SwitchModes() {
	
	int gestureNumber = 0;
	gestureNumber = 0;
	
	switch (gestureNumber = ReturnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		cout << "You choose: 'Manual Mode'" << string(14, ' ');
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return 'M';
		break;

	case 2:
		std::cout << '\r';
		cout << "You choose: 'Preset Mode'" << string(14, ' ');
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));		
		return 'P';
		break;

	case 3:
		std::cout << '\r';
		cout << "You choose: 'Developer Mode'" << string(14, ' ');
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		return 'D';
		break;

	default:
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << '\r';
		cout << "FIST: Manual Mode, " << "SPREAD: Preset Mode" << "WAVEIN: Developer Mode" << string(14, ' ');
		break;
	}
}

char MyoData::ManualMode() {

	int gestureNumber = 0;
	gestureNumber = 0;
	mode_type_ = 'M';
		switch (gestureNumber = ReturnGestureNumber(currentPose.toString())) {
		case 1:
			std::cout << '\r';
			cout << "FIST: Moving end effector: DOWN" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			SendJson(mode_type_, currentPose.toString());
			break;

		case 2:
			std::cout << '\r';
			cout << "SPREAD: Moving end effector: UP" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			SendJson(mode_type_, currentPose.toString());
			break;

		case 3:
			std::cout << '\r'; 
			cout << "WAVEIN: Moving end effector: LEFT" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			SendJson(mode_type_, currentPose.toString());
			break;

		case 4:
			std::cout << '\r';
			cout << "WAVEOUT: Moving end effector: RIGHT" << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			SendJson(mode_type_, currentPose.toString());
			break;

		case 5:
			std::cout << '\r';
			cout << "DOUBLE TAP, you are QUITTING this mode" << string(14, ' ') << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			gestureNumber = 0;
			return 'E';
			break;

		case 6: 
			std::cout << '\r';
			cout << "You are in REST, nothing is happening..." << string(14, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(10));			

			break;		
		default:
			std::cout << '\r';
			cout << "Uninterpretable gesture." << string(25, ' ');
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;
		}	
}

char MyoData::PresetMode() {
	cout << "yey you made it to preset mode" << "\n";
	return 'E';
}

char MyoData::DeveloperMode() {
	cout << "yey you made it to devel mode" << "\n";
	return 'E';
}

void MyoData::SendJson(char p_mode, string p_gesture) {
	
	pose_json_ = {
		{"mode", p_mode},
		{"gesture", p_gesture},		
	};
	cout << pose_json_ << string(15, ' ');
}

MyoData::~MyoData()
{	
}
