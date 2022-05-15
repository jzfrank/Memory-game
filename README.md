# Memory-game
Card games that test memory.

This project is for Software Engineering at ETHz

## 1. Compile instructions

### 1.1 Set up
To set up, we recommend using Ubuntu 20.4, which could be settled up using a virtual machine.
Then you need to install clion and wxwidgets.
Execute the following commands in a console:
1. `sudo apt-get update`
2. `sudo apt-get install build-essential` followed by `sudo reboot`
3. if on virtual machine : install guest-additions (https://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm) and then `sudo reboot`
4. `sudo snap install clion --classic` this installs the latest stable CLion version
5. `sudo apt-get install libwxgtk3.0-gtk3-dev` this installs wxWidgets (GUI library used in this project)

### 1.2 Compile Code
1. Open Clion
2. Click `File > Open...` and there select the **/sockpp** folder of this project
3. Click `Build > Build all in 'Debug'`
4. Wait until sockpp is compiled (from now on you never have to touch sockpp again ;))
5. Click `File > Open...` select the **/cse-lama-example-project** folder
6. Click `Build > Build all in 'Debug'`
7. Wait until Lama-server, Lama-client and Lama-tests are compiled

## 2. Run the Game
1. Open a console in the project folder, navigate into "cmake-build-debug" `cd cmake-build-debug`
2. Run server `./Lama-server`
3. In new consoles run as many clients as you want players `./Lama-client`


Then you should be good to go: open this project in clion, build and run. 