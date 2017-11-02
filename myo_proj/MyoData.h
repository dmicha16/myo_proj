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
	void sendGesture(string, bool);

	void print();

	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
	myo::Pose currentPose;	
	bool isUnlocked;
	~MyoData();

private:
	
};



