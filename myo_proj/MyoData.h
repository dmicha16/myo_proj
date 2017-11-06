#pragma once

#include <myo/myo.hpp>
#include <string>
#include <string.h>

using namespace std;



class MyoData : public myo::DeviceListener
{
public:
	MyoData();
	int ConnectToMyo();
	//string sendGesture(string, bool);	
	void print();
	int ReturnGestureNumber(string);
	void ManualMode();

	string globalGesture;

	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
	void Switch();
	myo::Pose currentPose;	
	bool isUnlocked;
	~MyoData();

private:
	
};



