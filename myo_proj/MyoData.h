#pragma once

#include <myo/myo.hpp>
#include <string>
#include <string.h>
//#include "json.hpp"

using namespace std;


class MyoData : public myo::DeviceListener
{
public:
	MyoData();
	int ConnectToMyo();		
	int ReturnGestureNumber(string);

	char ManualMode();
	char PresetMode();
	char DeveloperMode();
	
	//void SendJson(char, string); //later, add boolen gyro_stop here
	char SwitchModes();
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);

	myo::Pose currentPose;	
	bool isUnlocked;
	~MyoData();

private:
	char mode_type_;	
	
};



