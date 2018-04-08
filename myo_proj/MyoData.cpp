#include "stdafx.h"
#include "MyoData.h"

using json = nlohmann::json;

MyoData::MyoData() {
	json_id_ = 0;
	output_json_file.open("output_json_file.txt");
	inc_json_file.open("inc_json_file.txt");	
	arduino_obj_ = new SerialPort(COM6);

	std::string mode;	
	std::cout << "Press 'd' and 'Enter' to go into developer mode. \n";
	std::cin >> mode;

	if (mode == "d") {
		int myo_mode;
		std::cout << "myo mode: ";
		std::cin >> myo_mode;

		std::string gesture;
		std::cout << "gesture: ";
		std::cin >> gesture;

		populateJson(myo_mode, gesture);
	}
	else
		connectToMyo();		
	//cout << COM6 << " is connected: " << arduino_obj_->isConnected() << "\n";	
}

int MyoData::connectToMyo() {

	myo::Hub hub("com.project.myo_project");
	for (size_t i = 0; i < 3; i++) {		
		std::cout << "\r";
		std::cout << "Attempting to find a Myo..." << std::string(50, ' ');
		myo::Myo* myo = hub.waitForMyo(10000);

		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}
	}	

	std::cout << "\r";
	std::cout << "Connected to a Myo armband!" << std::string(50, ' ');
	hub.addListener(this);

	DELAY(1000);
	
	while (1) {
		hub.run(1000 / 25);		
		mode_type_ = switchModes();

		if (mode_type_ == MANUAL || mode_type_ == PRESET || mode_type_ == DEVEL || mode_type_ == EXIT)
			break;
	}

	DELAY(1000);

	if (mode_type_ == MANUAL || mode_type_ == PRESET || mode_type_ == DEVEL) {

		if (mode_type_ == MANUAL) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = manualMode();

				if (mode_type_ == EXIT)
					break;
			}
		}
		else if (mode_type_ == PRESET) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = presetMode();

				if (mode_type_ == EXIT)
					break;
			}
		}
		else if (mode_type_ == DEVEL) {

			while (true) {
				hub.run(1000 / 20);
				mode_type_ = developerMode();

				if (mode_type_ == EXIT)
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

int MyoData::returnGestureNumber(std::string p_inc_gesture) {

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
		std::cout << "You choose: 'Manual Mode'" << std::string(55, ' ');
		return MANUAL;
		break;

	case 2:
		std::cout << '\r';
		std::cout << "You choose: 'Preset Mode'" << std::string(55, ' ');
		return PRESET;
		break;

	/*case 3:
		std::cout << '\r';
		cout << "You choose: 'Developer Mode'" << string(55, ' ');		
		return DEVEL;
		break;*/

	case 5:
		std::cout << '\r';
		std::cout << "Quitting the program!'" << std::string(65, ' ');
		return EXIT;
		break;

	default:		
		std::cout << '\r';
		std::cout << "FIST: Manual Mode, " << "SPREAD: Preset Mode, " << "WAVEIN: Developer Mode, " << "DOUBLETAP: Quit." << std::string(15, ' ');
		break;
	}
}

int MyoData::manualMode() {

	gesture_number_ = 0;	
	mode_type_ = MANUAL;
		switch (gesture_number_ = returnGestureNumber(currentPose.toString())) {
		case 1:
			std::cout << '\r';
			std::cout << "FIST: Moving end effector: DOWN" << std::string(25, ' ');
			populateJson(mode_type_, currentPose.toString());
			break;

		case 2:
			std::cout << '\r';
			std::cout << "SPREAD: Moving end effector: UP" << std::string(25, ' ');
			populateJson(mode_type_, currentPose.toString());
			break;

		case 3:
			std::cout << '\r'; 
			std::cout << "WAVEIN: Moving end effector: LEFT" << std::string(25, ' ');
			populateJson(mode_type_, currentPose.toString());
			break;

		case 4:
			std::cout << '\r';
			std::cout << "WAVEOUT: Moving end effector: RIGHT" << std::string(25, ' ');
			populateJson(mode_type_, currentPose.toString());
			break;

		case 5:
			std::cout << '\r';
			std::cout << "DOUBLE TAP, you are QUITTING this mode" << std::string(25, ' ') << "\n";
			gesture_number_ = 0;
			return EXIT;
			break;

		case 6: 
			std::cout << '\r';
			std::cout << "You are in REST, nothing is happening..." << std::string(25, ' ');
			//populateJson(mode_type_, currentPose.toString());
			break;		

		default:
			std::cout << '\r';
			std::cout << "Uninterpretable gesture." << std::string(25, ' ');
			break;
		}	
}

int MyoData::presetMode() {

	gesture_number_ = 0;
	mode_type_ = PRESET;
	
	switch(gesture_number_ = returnGestureNumber(currentPose.toString())) {
	case 1:
		std::cout << '\r';
		std::cout << "Closing gripper." << std::string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 2:
		std::cout << '\r';
		std::cout << "Moving to extend." << std::string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 3:
		std::cout << '\r';
		std::cout << "Moving to user." << std::string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 4:
		std::cout << '\r';
		std::cout << "Moving home." << std::string(65, ' ');
		populateJson(mode_type_, currentPose.toString());
		break;

	case 5:
		std::cout << '\r';
		std::cout << "DOUBLE TAP, you are QUITTING this mode" << std::string(55, ' ') << "\n";
		gesture_number_ = 0;
		return EXIT;
		break;

	case 6:
		std::cout << '\r';
		std::cout << "FIST: Close the gripper, " << "SPREAD: Extend, " << "WAVEOUT: Home," << "WAVEIN: Move to user." << std::string(15, ' ');
		break;

	default:
		std::cout << '\r';
		std::cout << "Uninterpretable gesture." << std::string(65, ' ');
		break;
	}
}

int MyoData::developerMode() {
	std::cout << "yey you made it to devel mode";
	return EXIT;
}

void MyoData::populateJson(int p_mode, std::string p_gesture) {

	json_id_++;
	json pose_json;			

	//int local_gesture_number = returnGestureNumber(p_gesture);

	pose_json = {
		{ "id", json_id_ },
		{ "mode", p_mode },
		{ "gesture", p_gesture }
	};

	output_json_ = pose_json.dump();	

	if (p_mode == MANUAL) {

		saveJson(output_json_);
		sendToSerial(output_json_);
	}
	else if (p_mode == PRESET) {

		std::string response_from_robot;
		bool empty_response = false;

		saveJson(output_json_);
		sendToSerial(output_json_);

		for (size_t i = 0; i < 5; i++) {

			DELAY(1000);
			std::cout << '\r';
			std::cout << "Waiting for response from the robot.." << std::string(55, ' ');
			response_from_robot = recieveFromSerial();
			saveIncJson(response_from_robot);
			//char *inc_json_char = &response_from_robot[0];

			std::stringstream response;
			response << response_from_robot;
			OutputDebugString(L"PopulateJson response: \n");
			OutputDebugStringA(response.str().c_str());

			json incoming_json = json::parse(response);
			OutputDebugString(L"populateJson -> Successful parsing to Json \n");

			if (incoming_json["action_status"] == "true") {
				std::cout << "\r";
				std::cout << "Response is ok! \n" << std::string(50, ' ');
				empty_response = true;
				
				connectToMyo();
			}
		}
		if (!empty_response) {
			std::cout << '\r';
			std::cout << "No response from the robot! We gotta quit bro..." << std::string(35, ' ');
			
			DELAY(2000);
			exit(0);
		}
	}	
}

void MyoData::saveJson(std::string p_json) {
	
	output_json_file << p_json << "\n";
}

void MyoData::saveIncJson(std::string p_json) {

	inc_json_file << p_json << "\n";
}

void MyoData::sendToSerial(std::string p_output_json) {

	//char *output_serial_ = _strdup(p_output_json.c_str());
	char *output_serial_ = &p_output_json[0];

	if (arduino_obj_->isConnected()) {

		bool has_written = arduino_obj_->writeSerialPort(output_serial_, DATA_LENGTH);

		if (has_written) {
			OutputDebugString(L"MyoData::sendToSerial -> Data sent \n");			
		}			
		else {
			OutputDebugString(L"MyoData::sendToSerial -> Data not sent \n");			
		}
	}
}

std::string MyoData::recieveFromSerial() {

	char recieved_char[DATA_LENGTH];

	std::string received_string;

	if (arduino_obj_->isConnected()) {

		int has_read = arduino_obj_->readSerialPort(recieved_char, DATA_LENGTH);

		received_string.assign(recieved_char, DATA_LENGTH);
		int counter = 1;

		if (has_read) {			
			OutputDebugString(L"MyoData::recieveFromSerial -> Data recieved \n");
			if (counter == 1)
			{
				std::stringstream ss;
				ss << received_string;
				OutputDebugStringA(ss.str().c_str());
				return received_string;
			}
		}
		else {
			OutputDebugString(L"MyoData::recieveFromSerial -> Data not recieved \n");
			return "";
		}		
	}
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
