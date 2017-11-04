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

using namespace std;

MyoData::MyoData()
{
	ConnectToMyo();
}

int MyoData::ConnectToMyo()
{
	try {

		myo::Hub hub("com.project.myo_project");

		cout << "Attempting to find a Myo..." << std::endl;

		myo::Myo* myo = hub.waitForMyo(10000);

		if (!myo) {
			throw runtime_error("Unable to find a Myo!");
		}

		cout << "Connected to a Myo armband!" << std::endl << std::endl;

		myo->setStreamEmg(myo::Myo::streamEmgEnabled);		

		hub.addListener(this);

		while (1) {			
			hub.run(1000 / 1);
			print();
		}
	}
	catch (const std::exception& e) {
		cerr << "Error: " << e.what() << endl;
		cerr << "Press enter to continue.";
		cin.ignore();
		return 1;
	}

} 

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
	currentPose = pose;
	isUnlocked = false;

	if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {

		myo->unlock(myo::Myo::unlockHold);

		myo->notifyUserAction();

		string poseString = currentPose.toString();

		sendGesture(poseString, isUnlocked);
	}
	else {		
		myo->unlock(myo::Myo::unlockTimed);

		string poseString = currentPose.toString();

		sendGesture(poseString, isUnlocked);
		//cout << '[' << poseString << string(14 - poseString.size(), ' ') << ']' << '\n';
	}
}



string MyoData::sendGesture(string incGesture, bool isUnlocked)
{	
	ModeSwitch ms;
	ms.Switch(incGesture, isUnlocked);
	return incGesture;
}

string MyoData::returnCurrentGesture(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
	string currentGesture = pose.toString();
	return currentGesture;
}

void MyoData::print()
{	
	std::cout << '\r'; // moves cursor to the beggining of the line	

	if (1) {
		std::string poseString = currentPose.toString();

		std::cout << '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
	}
	/*else {		
		std::cout << '[' << std::string(8, ' ') << ']' << "[?]" << '[' << std::string(14, ' ') << ']';
	}*/

	//std::cout << std::flush;
}


MyoData::~MyoData()
{
}
