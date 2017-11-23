# A C++ interface between the Myo armband and Arduino

Basic useful feature list:

 * Gesture based control
 * Real time evaluation of the gestures
 * Writing to serial port
 * Population Json with gesture based information


### Adding the SDK to a Visual Studio Project:

- Installed the Myo SDK for Windows.
- [Put it into a easy-to-find location](https://developer.thalmic.com/downloads)
- Installed Myo Connect
- [Installed GitHub extension in VS](https://visualstudio.github.com/)
- 
    After you've installed the github extenstion you'll have to:
    - Go to the Team Explorer
    - Sign into Github
    - Clone this repository    
- After you've cloned the repository you'll have to link it with the SDK
- This link, a bit down shows what has to loaded into the project to make it work with the SDK
  https://developer.thalmic.com/docs/api_reference/platform/the-sdk.html
  - You'll have to right click on the project, where you see the c++ files
  	- Properites
  	- C/C++ -> Additional Include Directories
    	- Add the *include* directory of the SDK
  - Linker -> General
  	- Add the *lib* directory of the SDK
  - Linker -> Input
   	- If the *lib* file is missing add it from the SDK, but it shouldn't.
    The DLL file should also be in your project folder if you clone from GitHub.   
 


### Stuff used to make this:

 * [JSON for Modern C++](https://github.com/nlohmann/json) for Jsons!
 * [Serial port](https://github.com/manashmndl/SerialPort) for easy serial port implementation!
