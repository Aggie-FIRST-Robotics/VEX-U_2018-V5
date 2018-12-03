//
// Created by aamhi on 11/30/2018.
//
#include <afr-vexu-lib/base-commandable/motor_commandable.h>

#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H
#endif //VEX_U_2018_V5_DRIVE_H

namespace AFR::VexU::drive {


    class drive {

    public:
        std::int32 topleftmotorport, toprightmotorport, bottomleftmotorport, bottomrightmotorport;

        drive(const std::int_32 &topleftmotorport_, const std::int_32 &toprightmotorport_,
              const std::int_32 &bottomleftmotorport_, const std::int_32 &bottomrightmotorport_);

        static void init();

        static void arcadedrive(const std::int_32 &leftpower_, const std::int_32 &rightpower_);

    private:
        AFR::VexU::BaseCommandable::motor_commandable topleftmotor;
        AFR::VexU::BaseCommandable::motor_commandable toprightmotor;
        AFR::VexU::BaseCommandable::motor_commandable bottomleftmotor;
        AFR::VexU::BaseCommandable::motor_commandable bottomrightmotor;


    };


}
