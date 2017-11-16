#include "stdafx.h"
#include "MyoData.h"

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <Windows.h>

#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>


#define MODE_MANUAL 1
#define MODE_PRESET 2
#define MODE_DEVEL 3
#define MODE_EXIT 4

#define DELAY_OF_ONE_SEC std::this_thread::sleep_for(std::chrono::milliseconds(1000));

#include <myo\myo.hpp>
using namespace std;
using json = nlohmann::json;

MyoData::MyoData()
{

}

int MyoData::ConnectToMyo()
{	
	myo::Hub hub("com.project.myo_project");

	cout << "Attempting to find a Myo..." << std::endl;

	myo::Myo* myo = hub.waitForMyo(10000);

	if (!myo) {
		throw runtime_error("Unable to find a Myo!");
	}

	cout << "Connected to a Myo armband!" << std::endl << std::endl;

	hub.addListener(this);
	 
	while (true) {
		hub.run(1000 / 10);		
		mode_type_ = SwitchModes();

		if (mode_type_ == MODE_MANUAL || mode_type_ == MODE_PRESET || mode_type_ == MODE_DEVEL)
			break;
	}

	DELAY_OF_ONE_SEC;

	if (mode_type_ == MODE_MANUAL) {

		while (true) {
			hub.run(1000 / 10);
			mode_type_ = ManualMode();

			if (mode_type_ == MODE_EXIT)
				break;			
		}
	} else if (mode_type_ == MODE_PRESET) {

		while (true) {
			hub.run(1000 / 10);
			mode_type_ = PresetMode();

			if (mode_type_ == MODE_EXIT)
				break;			
		}
	} else if(mode_type_ == MODE_DEVEL) {

		while(true) {
			hub.run(1000 / 10);
			mode_type_ = PresetMode();

			if(mode_type_ == MODE_EXIT)
				break;
		}
	} else {
		cout << "You shouldn't be able to read this.";
	}
}

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose) {
	currentPose = pose;
	isUnlocked = false;	

	myo->unlock(myo::Myo::unlockHold);
	
	myo->notifyUserAction();
}

int MyoData::ReturnGestureNumber(string incGesture) {	

	int gesture_number_ = 0;

	if (incGesture == "fist") {
		gesture_number_ = 1;
		return gesture_number_;
	}
	else if (incGesture == "fingersSpread") {
		gesture_number_ = 2;
		return gesture_number_;
	}
	else if (incGesture == "waveIn") {
		gesture_number_ = 3;
		return gesture_number_;
	}
	else if (incGesture == "waveOut") {
		gesture_number_ = 4;
		return gesture_number_;
	}
	else if (incGesture == "doubleTap") {
		gesture_number_ = 5;
		return gesture_number_;
	}
	else if (incGesture == "rest") {
		gesture_number_ = 6;
		return gesture_number_;
	}
	else {		
		gesture_number_ = 0;
		return gesture_number_;
	}
}

int MyoData::SwitchModes() {
	
	int gesture_number_ = 0;	
	
	switch (gesture_number_ = ReturnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		cout << "You choose: 'Manual Mode'" << string(45, ' ');		
		return MODE_MANUAL;
		break;

	case 2:
		std::cout << '\r';
		cout << "You choose: 'Preset Mode'" << string(45, ' ');		
		return MODE_PRESET;
		break;

	case 3:
		std::cout << '\r';
		cout << "You choose: 'Developer Mode'" << string(45, ' ');		
		return MODE_DEVEL;
		break;

	default:		
		std::cout << '\r';
		cout << "FIST: Manual Mode, " << "SPREAD: Preset Mode, " << "WAVEIN: Developer Mode" << string(15, ' ');				
		break;
	}
}

int MyoData::ManualMode() {

	int gesture_number_ = 0;	
	mode_type_ = 0;
		switch (gesture_number_ = ReturnGestureNumber(currentPose.toString())) {
		case 1:
			std::cout << '\r';
			cout << "FIST: Moving end effector: DOWN" << string(25, ' ');			
			//SendJson(mode_type_, currentPose.toString());
			break;

		case 2:
			std::cout << '\r';
			cout << "SPREAD: Moving end effector: UP" << string(25, ' ');			
			//SendJson(mode_type_, currentPose.toString());
			break;

		case 3:
			std::cout << '\r'; 
			cout << "WAVEIN: Moving end effector: LEFT" << string(25, ' ');			
			//SendJson(mode_type_, currentPose.toString());
			break;

		case 4:
			std::cout << '\r';
			cout << "WAVEOUT: Moving end effector: RIGHT" << string(25, ' ');			
			//SendJson(mode_type_, currentPose.toString());
			break;

		case 5:
			std::cout << '\r';
			cout << "DOUBLE TAP, you are QUITTING this mode" << string(25, ' ') << "\n";			
			gesture_number_ = 0;
			return MODE_EXIT;
			break;

		case 6: 
			std::cout << '\r';
			cout << "You are in REST, nothing is happening..." << string(25, ' ');			
			break;		

		default:
			std::cout << '\r';
			cout << "Uninterpretable gesture." << string(25, ' ');			
			break;
		}	
}

char MyoData::PresetMode() {

	int gesture_number_ = 0;
	mode_type_ = 2;
	
	switch(gesture_number_ = ReturnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		cout << "Closing gripper." << string(55, ' ');
		SendJson(mode_type_, currentPose.toString());
		break;

	case 2:
		std::cout << '\r';
		cout << "Moving to extend." << string(55, ' ');
		SendJson(mode_type_, currentPose.toString());
		break;

	case 3:
		std::cout << '\r';
		cout << "Moving to user." << string(55, ' ');
		SendJson(mode_type_, currentPose.toString());
		break;

	case 4:
		std::cout << '\r';
		cout << "Moving home." << string(55, ' ');
		SendJson(mode_type_, currentPose.toString());
		break;

	case 5:
		std::cout << '\r';
		cout << "DOUBLE TAP, you are QUITTING this mode" << string(55, ' ') << "\n";
		gesture_number_ = 0;
		return MODE_EXIT;
		break;

	case 6:
		std::cout << '\r';
		cout << "FIST: Close the gripper, " << "SPREAD: Extend, " << "WAVEOUT: Home," << "WAVEIN: Move to user." << string(15, ' ');
		break;

	default:
		std::cout << '\r';
		cout << "Uninterpretable gesture." << string(65, ' ');
		break;
	}
}

char MyoData::DeveloperMode() {
	cout << "yey you made it to devel mode" << "\n";
	return 'E';
}

void MyoData::SendJson(char p_mode, string p_gesture) {

	json pose_json_;
	pose_json_ = {
		{"mode", p_mode},
		{"gesture", p_gesture},		
	};
	cout << pose_json_ << string(15, ' ');
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

MyoData::~MyoData() {
}
