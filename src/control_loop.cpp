#include "control_loop.h"

//We can use the class constructor to set parameters
CONTROLLER::CONTROLLER(double Kp, double InitVal, double dt) {

    _Kp = Kp;
    _dt = dt;
    CONTROLLER::set_xdes(InitVal);
    CONTROLLER::set_time(0);
    CONTROLLER::system_start();

    boost::thread loop_t (&CONTROLLER::loop, this);
    boost::thread usin_t (&CONTROLLER::user_input, this);
}


//Sense: get input to change the state of our System
void CONTROLLER::set_xdes(double x) {
    
    _Ref = x;

}


//Random initial value
void CONTROLLER::system_start() {
    
    srand(time(NULL));
    _State = 0.01*(rand()%100);
    _run = true;

}

void CONTROLLER::user_input() {

    std::cout << "User Connection Enabled...\n";
    std::cout << "Any non numeric input will terminate the program...\n";
    std::cout << "Initial reference: " << _Ref << "\n";
    string desired;
    double value;

    while(_run){

        try{
            std::cin >> desired;
            value = std::stod(desired);
            CONTROLLER::set_xdes(value);
        }catch(std::invalid_argument){

            cout << "Terminating Program...\n";
            CONTROLLER::kill();

        }
        
    } 

}

void CONTROLLER::kill(){

    _run = 0;

}

void CONTROLLER::loop() {

    std::cout << "Control Loop Engaged...\n";

    CONTROLLER::system_start();

    double e;
    double up;
    double ui;
    double ud;

    while(_run){

        e = _Ref - _State;
        up = _Kp*e;
        ui = _Ki*e;
        ud = _Kd*e;
        _State += up*_dt + ui/2*_dt*_dt + ud;
        _time += _dt;

        usleep(_dt*1e6);
    }


}

void CONTROLLER::set_time(double t){

    _time = t;

}

double CONTROLLER::get_state(){

    return _State;

}

double CONTROLLER::get_time(){

    return _time;

}

bool CONTROLLER::get_run(){

    return _run;

}