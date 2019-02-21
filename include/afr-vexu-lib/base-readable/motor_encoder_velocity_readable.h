//
// Created by aamhi on 2/20/2019.
//

#ifndef VEX_U_2018_V5_MOTOR_ENCODER_VELOCITY_READABLE_H
#define VEX_U_2018_V5_MOTOR_ENCODER_VELOCITY_READABLE_H
//
// Created by aamhi on 2/20/2019.
//

#include "afr-vexu-lib/defines.h"
#include "afr-vexu-lib/readable.h"
#include <deque>

namespace AFR::VexU::BaseReadable{


    class motor_encoder_velocity_readable : public readable{
        port_t port_;
        double scale_factor;
        double current_distance;
        double old_distance;
        double current_velocity;
        double temp_velocity;
        std::deque<double> velocities;
        static constexpr int max = 30;

        void update_private(const double& delta_seconds) override;

    public:
        motor_encoder_velocity_readable(port_t port, double scale_factor, const std::string& name);


        double get_actual_velocity();

        double get_scaled_velocity();


        std::any get_value() override;
    };


}
#endif //VEX_U_2018_V5_MOTOR_ENCODER_VELOCITY_READABLE_H
