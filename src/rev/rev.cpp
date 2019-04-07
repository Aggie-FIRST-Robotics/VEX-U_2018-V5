
#include "rev/rev.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Rev{
    void init_robot(){
        try{
            init_lib();
            init_afr_vexu_lib();
            serial->enqueue_write(ODROID_ID,0,1);
            Shooter::init();
            Drive::init();
            BallIntake::init();
            Cap::init();
        }

        catch(std::exception& e){
            std::cerr << "Init error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"Init error"};
        }
        std::cout << "Initialization Complete" << std::endl;
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void op_control(){
        while(true){
            scheduled::update_all();
            pros::delay(1);
        }
    }

    void disabled_robot(){

    }

    void destroy(){
        destroy_lib();
        destroy_afr_vexu_lib();
//        BaseReadable::destroy_battery();
//        BaseReadable::destroy_competition();
        //BaseReadable::destroy_controllers();
//        destroy_ports_list();

//        Drive::destroy();
        //Cap::destroy();
        //BallIntake::destroy();
//        Shooter::destroy();

    }

    void restart(){
//        destroy();
//        init_robot();
    }
}

#pragma clang diagnostic pop
