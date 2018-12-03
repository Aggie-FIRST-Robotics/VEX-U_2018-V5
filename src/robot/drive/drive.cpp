#include "drive/drive.h"


drive::drive(const std::int_32 &topleftmotorport_, const std::int_32 &toprightmotorport_,
             const std::int_32 &bottomleftmotorport_, const std::int_32 &bottomrightmotorport_) {
    topleftmotorport = topleftmotor_;
    bottomleftmotorport = bottomleftmotor_;
    toprightmotorport = toprightmotor_;
    bottomrightmotorport = bottomrightmotor_;

};

void init() {
    topleftmotor = new AFR::VexU::BaseCommandable::motor_commandable(topleftmotorport, E_MOTOR_GEARSET_36, true,
                                                                     E_MOTOR_BRAKE_BRAKE, nullptr);
    toprightmotor = new AFR::VexU::BaseCommandable::motor_commandable(toprightmotorport, E_MOTOR_GEARSET_36, true,
                                                                      E_MOTOR_BRAKE_BRAKE, nullptr);
    bottomleftmotor = new AFR::VexU::BaseCommandable::motor_commandable(bottomleftmotor, E_MOTOR_GEARSET_36, true,
                                                                        E_MOTOR_BRAKE_BRAKE, nullptr);
    bottomrightmotor = new AFR::VexU::BaseCommandable::motor_commandable(bottomrightmotorport, E_MOTOR_GEARSET_36, true,
                                                                         E_MOTOR_BRAKE_BRAKE, nullptr);
}

void arcadedrive(const std::int_32 &leftpower_, const std::int_32 &rightpower_) {

    topleftmotor.move(rightpower_ - leftpower_);
    bottomleftmotor.move(rightpower_ - leftpower_);
    toprightmotor.move(rightpower_ + leftpower_);
    bottomrightmotor.move(rightpower_ + leftpower_);


}
