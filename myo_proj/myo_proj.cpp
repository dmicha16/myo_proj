// myo_proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <myo\myo.hpp>
#include "MyoData.h"
#include <Windows.h>

using namespace std;

int main()
{		
	MyoData m;
	m.connectToMyo();
    return 0;
}

