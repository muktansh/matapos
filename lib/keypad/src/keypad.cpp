#include<keypad.h>
#include<stdio.h>
#include<vector>
#include<unistd.h>
#include<fcntl.h>


#include<iostream>
#include<thread>
#include<pigpio.h>

void NumpadDriver::wake(int data_pin)
{
    std::thread keypadthread(&NumpadDriver::readNumpad, this);

    keypadthread.join();
    //return 1;
}

// Callback registrations

void NumpadDriver::KeypadCallbacks(NumpadCallback* np)
{
    NumpadCallback.push_back(np);
}
//Add function to go back and forward.

//Callback functions


void NumpadDriver::forwards(forwardCallback* bck)
{
    forwardCallback.push_back(np);
      #ifdef DEBUG
		std::cout << std::endl << "forward button has been pressed" << std::endl;
	#endif
    //forward = 1; 

}

void backwards(backCallback* fwd)
{
    backCallback.push_back(np);
    #ifdef DEBUG    
		std::cout << std::endl << "back button has been pressed" << std::endl;
	#endif

}

void NumpadDriver::readNumpad()
{
    std::vector<long unsigned int> data;

    long unsigned int lookup[4][3] = {{1,2,3},{4,5,6},{7,8,9},{10,0,11}};
    int r1 = 7 ,r2 = 9 ,r3 = 11, r4 = 13 ,c1 = 15,c2 = 17 ,c3 = 19;
    
    if (gpioInitialise()<0)
    {
        std::cout << "Keypad cannot be initialised";
       // return(0);
    }
    
    gpioSetMode(r1, PI_INPUT);
    gpioSetMode(r2, PI_INPUT);
    gpioSetMode(r3, PI_INPUT);
    gpioSetMode(c1, PI_INPUT);
    gpioSetMode(c2, PI_INPUT);
    gpioSetMode(c3, PI_INPUT);
    gpioSetMode(r4, PI_INPUT);

    //Setting Pull Down Resistor
    gpioSetPullUpDown(r1, PI_PUD_UP);
    gpioSetPullUpDown(r2, PI_PUD_UP);
    gpioSetPullUpDown(r3, PI_PUD_UP);
    gpioSetPullUpDown(c1, PI_PUD_UP);
    gpioSetPullUpDown(c2, PI_PUD_UP);
    gpioSetPullUpDown(c3, PI_PUD_UP);
    gpioSetPullUpDown(r4, PI_PUD_UP);

    // Setting up the interupts
    gpioSetISRFunc(r4, EITHER_EDGE, 0, interuptHandler);
    gpioSetISRFunc(c1, EITHER_EDGE, 0, interuptHandler);
    gpioSetISRFunc(c3, EITHER_EDGE, 0, interuptHandler);

    while (1){
        if (gpioRead(7) == 0)
        {
            if (gpioRead(c1) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c2) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c3) == 0)
            {
                data.push_back(lookup[0][0]);
            }
        }
        else if (gpioRead(r2) == 0)
        {
            if (gpioRead(c1) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c2) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c3) == 0)
            {
                data.push_back(lookup[0][0]);
            }
        }
        else if (gpioRead(r3) == 0)
        {
            if (gpioRead(c1) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c2) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c3) == 0)
            {
                data.push_back(lookup[0][0]);
            }
        }
        else if (gpioRead(r4) == 0)
        {
            if (gpioRead(c1) == 0)
            {
                break;
            }
            else if (gpioRead(c2) == 0)
            {
                data.push_back(lookup[0][0]);
            }
            else if (gpioRead(c3) == 0)
            {
                break;
            }
        }
        else
        {
            data[0] = 0;
        }
    }
    for (auto  : NumpadCallback)
    {
        data->nums(data);
    }

}




void stop()
{
    gpioTerminate();
}