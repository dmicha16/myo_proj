#pragma once

#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <array>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>
#include <ratio>

#include "json.hpp"
#include "SerialPort.h"
#include <myo/myo.hpp>

#define DATA_LENGTH 255
#define DELAY(delay) std::this_thread::sleep_for(std::chrono::milliseconds(delay))

#define USE_WINDOWS_H

#define COM6 "\\\\.\\COM7"

#ifdef USE_WINDOWS_H
#include <Windows.h>
#endif

#ifdef LOGGING
#include "Logger.h"
#endif 

enum Modes { MANUAL = 1, PRESET = 2, DEVEL = 3, EXIT = 4 };


class MyoData : public myo::DeviceListener
{
public:

	MyoData();	
	int connectToMyo();
	~MyoData();

private:
	
	int returnGestureNumber(std::string  p_inc_gesture);
	int manualMode();
	int presetMode();
	int developerMode();
	int switchModes();

	void populateJson(int p_mode, std::string p_gesture);
	void saveJson(std::string p_json);
	void saveIncJson(std::string p_json);
	void sendToSerial(std::string p_output_json);

	std::string recieveFromSerial();
	void onPose(myo::Myo*, uint64_t, myo::Pose);

	myo::Pose currentPose;	
	bool isUnlocked;
	int mode_type_;	
	int gesture_number_;
	int json_id_;	
	std::string output_json_;
	std::string current_time_;
	char* port_name_;	
	SerialPort *arduino_obj_;	
	std::ofstream output_json_file;
	std::ofstream inc_json_file;
	
};



