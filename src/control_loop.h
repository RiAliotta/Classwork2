#include <iostream>
#include <stdlib.h>
#include "boost/thread.hpp"

using namespace std;

class CONTROLLER {
    public:
        CONTROLLER(double gain, double Init, double Dt);
        
        void user_input();
        void loop();                //Main loop function        
        void system_start();       //start the system
        void set_xdes(double x);   //member to set the desired value
        void set_time(double t);
        double get_state();
        double get_time();

    private:

        double _Kp;
        double _Ki;
        double _Kd;
        double _State;
        double _Ref;
        double _u;
        double _time;
        double _dt;
};
