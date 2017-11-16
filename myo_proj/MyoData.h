#pragma once

#include <myo/myo.hpp>
#include <string>
#include <string.h>
#include "json.hpp"

using namespace std;


class MyoData : public myo::DeviceListener
{
public:
	MyoData();
	int ConnectToMyo();		
	int ReturnGestureNumber(string);

	int ManualMode();
	int PresetMode();
	int DeveloperMode();
	
	void SendJson(char, string); //later, add boolen gyro_stop here
	int SwitchModes();
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);

	myo::Pose currentPose;	
	bool isUnlocked;
	~MyoData();

private:
	int mode_type_;	
	int gesture_number_;
	
};



