#include "stdafx.h"
#include "MyoData.h"

#include <array>
#include <sstream>
#include <stdexcept>
#include <Windows.h>

#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <myo\myo.hpp>

#define MODE_MANUAL 1
#define MODE_PRESET 2
#define MODE_DEVEL 3
#define MODE_EXIT 4

#define DELAY_OF_ONE_SEC std::this_thread::sleep_for(std::chrono::milliseconds(1000));


using namespace std;
using json = nlohmann::json;
using namespace std::chrono;

MyoData::MyoData()
{
	json_id_ = 0;
	
}

int MyoData::connectToMyo()
{	
	myo::Hub hub("com.project.myo_project");

	cout << "Attempting to find a Myo..." << string(5, ' ');

	myo::Myo* myo = hub.waitForMyo(10000);

	if (!myo) {
		throw runtime_error("Unable to find a Myo!");
	}

	cout << "Connected to a Myo armband!" << std::endl << std::endl;

	hub.addListener(this);
	 
	while (true) {
		hub.run(1000 / 10);		
		mode_type_ = switchModes();

		if (mode_type_ == MODE_MANUAL || mode_type_ == MODE_PRESET || mode_type_ == MODE_DEVEL || mode_type_ == MODE_EXIT)
			break;
	}

	DELAY_OF_ONE_SEC;

	if (mode_type_ == MODE_MANUAL) {

		while (true) {
			hub.run(1000 / 10);
			mode_type_ = manualMode();

			if (mode_type_ == MODE_EXIT)
				break;			
		}
	} else if (mode_type_ == MODE_PRESET) {

		while (true) {
			hub.run(1000 / 10);
			mode_type_ = presetMode();

			if (mode_type_ == MODE_EXIT)
				break;			
		}
	} else if(mode_type_ == MODE_DEVEL) {

		while(true) {
			hub.run(1000 / 10);
			mode_type_ = developerMode();

			if(mode_type_ == MODE_EXIT)
				break;
		}
	} else if(mode_type_ == MODE_EXIT) {
		exit(0);
	}	
	else {
		cout << "You shouldn't be able to read this.";
	}

	connectToMyo();

}

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose) {
	currentPose = pose;
	isUnlocked = false;	

	myo->unlock(myo::Myo::unlockHold);
	
	myo->notifyUserAction();
}

int MyoData::returnGestureNumber(string incGesture) {	

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

int MyoData::switchModes() {
	
	gesture_number_ = 0;	
	
	switch (gesture_number_ = returnGestureNumber(currentPose.toString())) {
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

	case 5:
		std::cout << '\r';
		cout << "Quitting the program!'" << string(65, ' ');
		return MODE_EXIT;
		break;

	default:		
		std::cout << '\r';
		cout << "FIST: Manual Mode, " << "SPREAD: Preset Mode, " << "WAVEIN: Developer Mode, " << "DOUBLETAP: Quit." << string(15, ' ');
		break;
	}
}

int MyoData::manualMode() {

	gesture_number_ = 0;	
	mode_type_ = MODE_MANUAL;
		switch (gesture_number_ = returnGestureNumber(currentPose.toString())) {
		case 1:
			std::cout << '\r';
			cout << "FIST: Moving end effector: DOWN" << string(25, ' ');			
			sendJson(mode_type_, currentPose.toString());
			break;

		case 2:
			std::cout << '\r';
			cout << "SPREAD: Moving end effector: UP" << string(25, ' ');			
			sendJson(mode_type_, currentPose.toString());
			break;

		case 3:
			std::cout << '\r'; 
			cout << "WAVEIN: Moving end effector: LEFT" << string(25, ' ');			
			sendJson(mode_type_, currentPose.toString());
			break;

		case 4:
			std::cout << '\r';
			cout << "WAVEOUT: Moving end effector: RIGHT" << string(25, ' ');			
			sendJson(mode_type_, currentPose.toString());
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

int MyoData::presetMode() {

	gesture_number_ = 0;
	mode_type_ = MODE_PRESET;
	
	switch(gesture_number_ = returnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		cout << "Closing gripper." << string(55, ' ');
		sendJson(mode_type_, currentPose.toString());
		break;

	case 2:
		std::cout << '\r';
		cout << "Moving to extend." << string(55, ' ');
		sendJson(mode_type_, currentPose.toString());
		break;

	case 3:
		std::cout << '\r';
		cout << "Moving to user." << string(55, ' ');
		sendJson(mode_type_, currentPose.toString());
		break;

	case 4:
		std::cout << '\r';
		cout << "Moving home." << string(55, ' ');
		sendJson(mode_type_, currentPose.toString());
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

int MyoData::developerMode() {
	cout << "yey you made it to devel mode" << "\n";
	return MODE_EXIT;
}

void MyoData::sendJson(int p_mode, string p_gesture) {

	json_id_++;
	json pose_json_;		

	current_time_ = __TIMESTAMP__;

	pose_json_ = {
		{"id", json_id_},
		{"mode", p_mode},
		{"gesture", p_gesture},
		{"timestamp", current_time_},
	};
	
	output_json_ = pose_json_.dump();
	saveJson(output_json_);

	if(p_mode == MODE_PRESET) {
		// wait for confirmation from the robot that it has finished the operation to continue.
	}

	DELAY_OF_ONE_SEC;
}

void MyoData::saveJson(string p_output_json) {
	
	json_file.open("json_log.txt");
	json_file << p_output_json << "\n";
	
}

/*string MyoData::returnCurrTime() {

	time_t curr_time;
	tm * curr_tm;
	char date_string[100];
	char time_string[100];

	time(&curr_time);
	curr_tm = localtime(&curr_time);	
	strftime(time_string, 50, "Current time is %T", curr_tm);

	return curr_tm;
}*/

MyoData::~MyoData() {
	json_file.close();	
}
