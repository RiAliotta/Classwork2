#include "control_loop.h"

//We can use the class constructor to set parameters
CONTROLLER::CONTROLLER(double Kp, double InitVal, double dt) {

    _Kp = Kp;
    _dt = dt;
    CONTROLLER::set_xdes(InitVal);
    CONTROLLER::set_time(0);

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

}

void CONTROLLER::user_input() {

    std::cout << "User Connection Enabled...\n";
    double desired;

    while(true){

        std::cin >> desired;
        CONTROLLER::set_xdes(desired);

    } 

}

void CONTROLLER::loop() {

    std::cout << "Control Loop Engaged...\n";

    CONTROLLER::system_start();

    double e;
    double up;
    double ui;
    double ud;

    while(true){

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