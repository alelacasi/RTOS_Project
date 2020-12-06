# COEN320-Project
RTOS scheduler

//README file must contain detailed instructions to compile, execute and test the code in the remote real-time workstations
We will assume the user knows how to connect & use Open QNX

How to compile: Once QNX is open please make sure that the VM is also running. Make sure to connect QNX to the VM by opening the QNX system information and making sure the QNX target containt the correct IP of the desired VM. Once this step is completed, right click on the file called COEN320-Project and go to properties. From here go to QNX C/C++ Project, then to build variants, and make sure that X86 (Little Endian) is checked. Press OK. Then you will need to right clicj on the project again and go to clean project, wait until it is finished, and then right click on the project for the last time and select Build Project. This will make sure the code is compiled properly and it is ready to execute.

How to execute: Once it has been properly compiled, to run this program you can use the debugger or the run. Whicherver you choose, choose the second drop down option, which says Debug Configurations or Run Configurations depending on which was chosen. Once this is done a window will open, click on the option C/C++ QNX QConn (IP) and select new launch configuration if no configuration has been set. To make a new configuration select the project with the browse option in the Project: section, then choose the _g option in the C/C++ Application: section using the search project. Once this is done, make sure the correct IP of the VM is chosen in Target Options. Finally, click Apply and then Run. The program will now execute using the run or debug option.

How to test: