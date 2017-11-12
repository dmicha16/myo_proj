# myo_proj

What's needed to use this on Windows:
- Installed Visual Studio
  - You'll need these packages installed as well (they are from the installer itself, but can be later put in aswell:
    - Universal Windows Development
    - Desktop development with C++
- Installed the Myo SDK for Windows.
  Put it into a easy-to-find location
  https://developer.thalmic.com/downloads
- Installed Myo Connect
- Installed GitHub extension in VS
  https://visualstudio.github.com/
    Not-that-straight-forward but it’s really powerful
    After you've installed the github extenstion you'll have to:
    - Go to the Team Explored
    - Sign into Github
    - Clone this repository    
- After you've cloned the repository you'll have to link it with the SDK
  This link, a bit down shows what has to loaded into the project to make it work with the SDK
  https://developer.thalmic.com/docs/api_reference/platform/the-sdk.html
  - You'll have to right click on the project, where you see the c++ files
  - Properites
  - C/C++ -> Additional Include Directories
    Add the *include* directory of the SDK
  - Linker -> General
    Add the *lib* directory of the SDK
  - Linker -> Input
    If the *lib* file is missing add it from the SDK, but it shouldn't.
    The DLL file should also be in your project folder if you clone from GitHub.
    
 After all these steps, try building or compiling the code and see if it works!

