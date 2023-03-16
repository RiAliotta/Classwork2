#include "control_loop.h"
#include <fstream>

using namespace std;

//the goal is to implement a simple PID controller, 
//running on input value to reach the desired one

// Sense: read a value from keyboard
// Plan:  generate the correct input
// Act:   set the input

int main(int argc, char** argv) {

    double InitVal;
    double Dt;
    double Kp;

    if (argc > 4){
        InitVal = atof(argv[1]);
        Dt =  atof(argv[2]);
        Kp = atof(argv[3]);
    }
    else{
        InitVal = 1.0;
        Dt = 0.1;
        Kp = 2.5;
    }

    CONTROLLER c(2.5, InitVal, Dt);

    std::fstream state_t;
    state_t.open("TimeState.txt", ios::out);

    while(true){
        double a_time = c.get_time();
        double a_state = c.get_state();
        state_t << a_time << "\t" << a_state << std::endl;
        std::cout << a_time << "\t" << a_state << std::endl;
        usleep(Dt*1e6);
    }

    state_t.close();
    return 0;
}
