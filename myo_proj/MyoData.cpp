#include "stdafx.h"
#include "MyoData.h"

#include <array>
#include <sstream>
#include <stdexcept>
#include <Windows.h>

#include <chrono>
#include <thread>
#include <iomanip>
#include <ratio>

#define DATA_LENGTH 255
#define DATA_LENGTH_OF_1 1

#define MODE_MANUAL 1
#define MODE_PRESET 2
#define MODE_DEVEL 3
#define MODE_EXIT 4
#define COM6 "\\\\.\\COM7"		
#define DELAY_OF_ONE_SEC std::this_thread::sleep_for(std::chrono::milliseconds(1000))

using namespace std;
using json = nlohmann::json;
using namespace std::chrono;

MyoData::MyoData()
{
	json_id_ = 0;
	output_json_file.open("output_json_file.txt");
	inc_json_file.open("inc_json_file.txt");	
	arduino_obj_ = new SerialPort(COM6);

	now_construct = time(nullptr);

	string mode;	
	cout << "Press 'd' and 'Enter' to go into developer mode. \n";
	cin >> mode;

	if (mode == "d")
	{
		int myo_mode;
		cout << "myo mode: ";
		cin >> myo_mode;

		string gesture;
		cout << "gesture: ";
		cin >> gesture;

		populateJson(myo_mode, gesture);
	}
	else
		connectToMyo();	
	
	//cout << COM6 << " is connected: " << arduino_obj_->isConnected() << "\n";	
}

int MyoData::connectToMyo()
{	
	myo::Hub hub("com.project.myo_project");

	cout << "\r";
	cout << "Attempting to find a Myo..." << string(50, ' ');

	myo::Myo* myo = hub.waitForMyo(10000);

	if (!myo) {
		throw runtime_error("Unable to find a Myo!");
	}

	cout << "\r";
	cout << "Connected to a Myo armband!" << string(50, ' ');

	hub.addListener(this);

	DELAY_OF_ONE_SEC;
	
	while (1) {
		hub.run(1000 / 25);		
		mode_type_ = switchModes();

		if (mode_type_ == MODE_MANUAL || mode_type_ == MODE_PRESET || mode_type_ == MODE_DEVEL || mode_type_ == MODE_EXIT)
			break;
	}

	DELAY_OF_ONE_SEC;

	if (mode_type_ == MODE_MANUAL || mode_type_ == MODE_PRESET || mode_type_ == MODE_DEVEL) {

		if (mode_type_ == MODE_MANUAL) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = manualMode();

				if (mode_type_ == MODE_EXIT)
					break;
			}
		}
		else if (mode_type_ == MODE_PRESET) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = presetMode();

				if (mode_type_ == MODE_EXIT)
					break;
			}
		}
		else if (mode_type_ == MODE_DEVEL) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = developerMode();

				if (mode_type_ == MODE_EXIT)
					break;
			}			
		}
		
		connectToMyo();		
	} 
	
	else {
		exit(0);
	}
}

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose) {
	currentPose = pose;
	isUnlocked = false;	

	myo->unlock(myo::Myo::unlockHold);
	
	myo->notifyUserAction();
}

int MyoData::returnGestureNumber(string p_inc_gesture) {	

	int gesture_number_ = 0;

	if (p_inc_gesture == "fist") {
		gesture_number_ = 1;
		return gesture_number_;
	}
	else if (p_inc_gesture == "fingersSpread") {
		gesture_number_ = 2;
		return gesture_number_;
	}
	else if (p_inc_gesture == "waveIn") {
		gesture_number_ = 3;
		return gesture_number_;
	}
	else if (p_inc_gesture == "waveOut") {
		gesture_number_ = 4;
		return gesture_number_;
	}
	else if (p_inc_gesture == "doubleTap") {
		gesture_number_ = 5;
		return gesture_number_;
	}
	else if (p_inc_gesture == "rest") {
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
		cout << "You choose: 'Manual Mode'" << string(55, ' ');		
		return MODE_MANUAL;
		break;

	case 2:
		std::cout << '\r';
		cout << "You choose: 'Preset Mode'" << string(55, ' ');		
		return MODE_PRESET;
		break;

	/*case 3:
		std::cout << '\r';
		cout << "You choose: 'Developer Mode'" << string(55, ' ');		
		return MODE_DEVEL;
		break;*/

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
			populateJson(mode_type_, currentPose.toString());
			break;

		case 2:
			std::cout << '\r';
			cout << "SPREAD: Moving end effector: UP" << string(25, ' ');			
			populateJson(mode_type_, currentPose.toString());
			break;

		case 3:
			std::cout << '\r'; 
			cout << "WAVEIN: Moving end effector: LEFT" << string(25, ' ');			
			populateJson(mode_type_, currentPose.toString());
			break;

		case 4:
			std::cout << '\r';
			cout << "WAVEOUT: Moving end effector: RIGHT" << string(25, ' ');			
			populateJson(mode_type_, currentPose.toString());
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
			//populateJson(mode_type_, currentPose.toString());
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
		cout << "Closing gripper." << string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 2:
		std::cout << '\r';
		cout << "Moving to extend." << string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 3:
		std::cout << '\r';
		cout << "Moving to user." << string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 4:
		std::cout << '\r';
		cout << "Moving home." << string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
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
	cout << "yey you made it to devel mode";
	return MODE_EXIT;
}

void MyoData::populateJson(int p_mode, string p_gesture) {

	json_id_++;
	json pose_json_;			

	//int local_gesture_number = returnGestureNumber(p_gesture);

	pose_json_ = {
		{ "id", json_id_ },
		{ "mode", p_mode },
		{ "gesture", p_gesture }
	};

	output_json_ = pose_json_.dump();	

	if (p_mode == MODE_MANUAL) {

		saveJson(output_json_);
		sendToSerial(output_json_);
	}
	else if (p_mode == MODE_PRESET) {

		string response_from_robot;
		bool empty_response = false;

		saveJson(output_json_);
		sendToSerial(output_json_);

		for (size_t i = 0; i < 500; i++) {

			//DELAY_OF_ONE_SEC;
			cout << '\r';
			cout << "Waiting for response from the robot.." << string(55, ' ');
		
			response_from_robot = recieveFromSerial();

			if (response_from_robot != "") {
				stringstream response;
				response << response_from_robot;

				try {
					json incoming_json = json::parse(response);
					OutputDebugString(L"populateJson -> Successful parsing to Json \n");
					cout << incoming_json["from_arduino"] << "\n";

					if (incoming_json["from_arduino"] == true) {
						if (incoming_json["action_status"] == true) {
							cout << "\r";
							cout << "Response is ok! \n" << string(50, ' ');
							empty_response = true;

							//connectToMyo();

							OutputDebugString(L"Successfully parsed the incoming Json");
							exit(0);
						}
						else {
							cout << '\r';
							cout << "Robot has not finished working yet!" << string(55, ' ');
						}
					}
				}
				catch (const std::exception&) {
					cout << "\r";
					cout << "it didnt parse bruv" << string(55, ' ');
				}
			}	
		} 

		if (!empty_response) {
			cout << '\r';
			cout << "No response from the robot! We gotta quit bro..." << string(35, ' ');
			
			DELAY_OF_ONE_SEC;
			DELAY_OF_ONE_SEC;
			exit(0);
		}
	}	
}

void MyoData::saveJson(string p_json) {
	
	output_json_file << p_json << "\n";
}

void MyoData::saveIncJson(string p_json) {

	inc_json_file << p_json << "\n";
}

void MyoData::sendToSerial(string p_output_json) {

	//char *output_serial_ = _strdup(p_output_json.c_str());
	char *output_serial_ = &p_output_json[0];

	if (arduino_obj_->isConnected()) {

		bool has_written = arduino_obj_->writeSerialPort(output_serial_, DATA_LENGTH);
		
		if (has_written) {
			OutputDebugString(L"MyoData::sendToSerial -> Data sent \n");
			now_serial_read = time(nullptr);
		}
		else {
			OutputDebugString(L"MyoData::sendToSerial -> Data not sent \n");
		}	
	}
}

string MyoData::recieveFromSerial() {

	char recieved_char[DATA_LENGTH_OF_1];

	string received_string;
	string complete_string;
	if (arduino_obj_->isConnected()) {	

		int has_read = arduino_obj_->readSerialPort(recieved_char, DATA_LENGTH_OF_1);
		received_string.assign(recieved_char, DATA_LENGTH_OF_1);

		if (received_string == "{") {

			complete_string.append(received_string);

			do {
				has_read = arduino_obj_->readSerialPort(recieved_char, DATA_LENGTH_OF_1);

				received_string.assign(recieved_char, DATA_LENGTH_OF_1);
				complete_string.append(received_string);

				if (has_read) {
					//OutputDebugString(L"MyoData::recieveFromSerial -> Data recieved \n");

				}
				else {
					//OutputDebugString(L"MyoData::recieveFromSerial -> Data not recieved \n");
				}

			} while (recieved_char[0] != '}');

			saveIncJson(complete_string);
			stringstream msg;
			msg << "MyoData::recieveFromSerial -> " << complete_string << "\n";
			OutputDebugStringA(msg.str().c_str());
			return complete_string;
		}
		else {
			cout << "\r";
			cout << "shits fucked" << string(55, ' ');
		}
	}
	//return "{'from_arduino':false,'message':'this is a message','action_status':false,'counter':47,'servo 1 position':467}";
	return "";
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
	inc_json_file.close();
	output_json_file.close();
}
