#pragma once

#include <myo/myo.hpp>
#include <string>
#include <string.h>
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;


class MyoData : public myo::DeviceListener
{
public:

	MyoData();	
	int connectToMyo();
	~MyoData();

private:
	
	int returnGestureNumber(string);

	int manualMode();
	int presetMode();
	int developerMode();

	void sendJson(int, string);
	void saveJson(string);

	int switchModes();
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);

	myo::Pose currentPose;
	
	bool isUnlocked;

	int mode_type_;	
	int gesture_number_;
	int json_id_;
	string output_json_;

	ofstream json_file;

	
	
};



