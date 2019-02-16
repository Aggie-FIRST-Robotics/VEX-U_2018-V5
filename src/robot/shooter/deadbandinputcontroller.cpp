/*#include "robot/shooter/deadbandinputcontroller.h"

#include "afr-vexu-lib/base-action/dead_band_action.h"
namespace AFR::VexU::Robot::Shooter{
    BaseAction::dead_band_action<double, int16_t>* dead_band_azimuth;
    deadbandinputcontroller::deadbandinputcontroller(AFR::VexU::scheduled_update_t update_period,
                                                     AFR::VexU::commandable *commandable, double bottom_threshold,
                                                     double top_threshold, AFR::VexU::readable *value_pointer,
                                                     int16_t below_value, int16_t above_value,
                                                     const std::string &name): action(update_period, commandable, name) {

    dead_band_azimuth = new BaseAction::dead_band_action<double, int16_t>{update_period, commandable, -90, 90, value_pointer, -6000, 6000, name};






    }










}*/