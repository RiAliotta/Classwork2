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
    double Ki;
    double Kd;

    if (argc > 5){
        InitVal = atof(argv[1]);
        Dt =  atof(argv[2]);
        Kp = atof(argv[3]);
        Ki = atof(argv[4]);
        Kd = atof(argv[5]);
    }
    else{
        InitVal = 1.0;
        Dt = 0.1;
        Kp = 0.25;
        Ki = 1;
        Kd = 0.01;
    }

    CONTROLLER c(2.5, InitVal, Dt);

    std::fstream state_t;
    state_t.open("TimeState.txt", ios::out);

    while(c.get_run()){
        double a_time = c.get_time();
        double a_state = c.get_state();
        state_t << a_time << "\t" << a_state << std::endl;
        std::cout << a_time << "\t" << a_state << std::endl;
        usleep(Dt*1e6);
    }

    state_t.close();
    return 0;
}
