#include "stdafx.h"
#include "MyoData.h"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <Windows.h>

#include <chrono>
#include <thread>

#include "ModeSwitch.h"

#define _USE_MATH_DEFINES

#include <myo\myo.hpp>
using namespace std;

MyoData::MyoData()
{
	ConnectToMyo();
	Switch();
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

void MyoData::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose) {
	currentPose = pose;
	isUnlocked = false;

	if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {

		myo->unlock(myo::Myo::unlockHold);

		myo->notifyUserAction();		
		globalGesture = currentPose.toString();			
	}
}

void MyoData::Switch() {

	int gestureNumber = ReturnGestureNumber(globalGesture);
	if (gestureNumber == 1) {
		cout << "you are in manual mode";
		manualMode();
	}
	else {
		cout << "you are in preset mode";
	}
}

int MyoData::ReturnGestureNumber(string incGesture) {

	int gestureNumber = 0;

	if (incGesture == "fist") {
		gestureNumber = 1;
		return gestureNumber;
	}
	else if (incGesture == "spread") {
		gestureNumber = 2;
		return gestureNumber;
	}
	else if (incGesture == "waveIn") {
		gestureNumber = 3;
		return gestureNumber;
	}
	else if (incGesture == "waveOut") {
		gestureNumber = 4;
		return gestureNumber;
	}
	else if (incGesture == "doubleTap") {
		gestureNumber = 5;
		return gestureNumber;
	}
	else if (incGesture == "rest") {
		gestureNumber = 6;
		return gestureNumber;
	}
	else {
		gestureNumber = 0;
		return gestureNumber;
	}

}

void MyoData::manualMode()
{	
	int gestureNumber = 0;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	bool exitVal = false;
	do {

		switch (gestureNumber) {
		case 1: cout << "you are in fist mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));			
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;

		case 2: cout << "you are in spread mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;

		case 3: cout << "you are in waveIn mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;

		case 4: cout << "you are in waveOut mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			exitVal = true;
			gestureNumber = 0;
			cout << "you are QUITTING THIS mode";
			//PresetMode(recievedGesture, isUnlocked);
			break;
		case 5: cout << "DOUBLE TAP";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;

		case 6: cout << "you are in rest mode, nothing is happening";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;
		case 7: cout << "you are in waveIn mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;
		default: cout << "you entered default mode";
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));			
			gestureNumber = ReturnGestureNumber(globalGesture);
			break;
		}
	} while (exitVal != true);
}




/*string MyoData::sendGesture(string incGesture, bool isUnlocked)
{	
	ModeSwitch ms;
	ms.Switch(incGesture, isUnlocked);
	return incGesture;
}*/

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
