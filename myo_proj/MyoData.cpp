#include "stdafx.h"
#include "MyoData.h"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <Windows.h>

#include "ModeSwitch.h"

#define _USE_MATH_DEFINES

#include <myo\myo.hpp>


MyoData::MyoData()
{
	//std::array<int8_t, 8> emgSamples;	
	
	ConnectToMyo();

}

int MyoData::ConnectToMyo()
{
	try {

		myo::Hub hub("com.project.myo_project");

		std::cout << "Attempting to find a Myo..." << std::endl;

		myo::Myo* myo = hub.waitForMyo(10000);

		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

		myo->setStreamEmg(myo::Myo::streamEmgEnabled);

		OutputDebugString(L"Before MyoData collector is constructed\n");
		// TODO: What the shit is this and why is it not working?
		//MyoData collector;
		OutputDebugString(L"After MyoData collector is constructed\n");

		hub.addListener(this);

		while (1) {
			OutputDebugString(L"Debug while loop\n");
			hub.run(1000 / 20);
			print();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}

} 

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
	currentPose = pose;

	if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {

		myo->unlock(myo::Myo::unlockHold);

		myo->notifyUserAction();
	}
	else {		
		myo->unlock(myo::Myo::unlockTimed);

		std::string poseString = currentPose.toString();

		sendGesture(poseString);
		std::cout << '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
	}
}

void MyoData::sendGesture(std::string incGesture)
{
	ModeSwitch ms;
	ms.ReadGesture(incGesture);	
}

void MyoData::print()
{	
	std::cout << '\r';

	bool thing = true;

	if (thing == true) {
		std::string poseString = currentPose.toString();

		std::cout << '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
	}
	else {		
		std::cout << '[' << std::string(8, ' ') << ']' << "[?]" << '[' << std::string(14, ' ') << ']';
	}

	std::cout << std::flush;
}


MyoData::~MyoData()
{
}
