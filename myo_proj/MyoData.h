#pragma once

#include <myo/myo.hpp>
#include <string>
#include <string.h>

class MyoData : public myo::DeviceListener
{
public:
	MyoData();
	int ConnectToMyo();
	void sendGesture(std::string);

	void print();

	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
	myo::Pose currentPose;


	~MyoData();

private:
	
};



