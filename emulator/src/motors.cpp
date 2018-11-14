#include <unordered_map>
#include <pros/motors.hpp>


#include "pros/motors.hpp"

#include "emulator/emulator.h"

namespace pros{
    using namespace AFR::VexU::Emulator;

#define CHECK_ACCESS_ERROR(x, y)\
    if((x) == nullptr){         \
    errno = EACCES;             \
    return y;                   \
}

    motor_data* check_port(uint8_t port){
        if(port < 1 || port > 21){
            throw emulator_error{"Invalid port: " + std::to_string(port)};
        }
        if(!main_emulator.is_initialized()){
            throw emulator_error{"Emulator not initialized"};
        }
        if(typeid(main_emulator.get_port(port)).hash_code() != typeid(motor_data).hash_code()){
            throw emulator_error("Port " + std::to_string(port) + " is not a motor, is" +
                                 typeid(main_emulator.get_port(port)).name());
        }
        auto* data = dynamic_cast<motor_data*>(main_emulator.get_port(port));
        if(data->flags & E_MOTOR_FLAGS_BUSY){
            return nullptr;
        }
        return data;
    }

    int bound_value(int value, int max, int min){
        if(value > max){
            return max;
        }
        if(value < min){
            return min;
        }
        return value;
    }

    Motor::Motor(const uint8_t port, const motor_gearset_e_t gearset, const bool reverse,
                 const motor_encoder_units_e_t encoder_units) : _port(port){
        auto* data = check_port(port);
        if(data == nullptr){
            errno = EACCES;
        }
        else{
            data->gearset = gearset;
            data->reversed = reverse;
            data->encoder_units = encoder_units;
        }
    }

    Motor::Motor(const std::uint8_t port, const motor_gearset_e_t gearset, const bool reverse) : Motor(port, gearset,
                                                                                                       reverse,
                                                                                                       E_MOTOR_ENCODER_DEGREES){}

    Motor::Motor(const std::uint8_t port, const motor_gearset_e_t gearset) : Motor(port, gearset, false){}

    Motor::Motor(const std::uint8_t port, const bool reverse) : Motor(port, E_MOTOR_GEARSET_18, reverse){}

    Motor::Motor(const std::uint8_t port) : Motor(port, false){}

    std::int32_t Motor::operator=(std::int32_t voltage) const{
        return move(voltage);
    }

    std::int32_t Motor::move(std::int32_t voltage) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->target_voltage = static_cast<int16_t>(bound_value(voltage, 127, -127) * 12000 / 127);
        return 1;
    }

    std::int32_t Motor::move_absolute(const double position, const std::int32_t velocity) const{
        throw emulator_error{"Should not use Motor::move_absolute"};
    }

    std::int32_t Motor::move_relative(const double position, const std::int32_t velocity) const{
        throw emulator_error{"Should not use Motor::move_relative"};
    }

    std::int32_t Motor::move_velocity(const std::int32_t velocity) const{
        throw emulator_error{"Should not use Motor::move_velocity"};
    }

    std::int32_t Motor::move_voltage(const std::int32_t voltage) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->target_voltage = static_cast<int16_t>(bound_value(voltage, -12000, 12000));
        return 1;
    }

    std::int32_t Motor::modify_profiled_velocity(const std::int32_t velocity) const{
        throw emulator_error{"Should not use Motor::modify_profiled_velocity"};
    }

    double Motor::get_target_position() const{
        throw emulator_error{"Should not use Motor::get_target_position"};
    }

    std::int32_t Motor::get_target_velocity() const{
        throw emulator_error{"Should not use Motor::get_target_velocity"};
    }

    double Motor::get_actual_velocity() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR_F)
        return data->velocity;
    }

    std::int32_t Motor::get_current_draw() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->current_draw;
    }

    std::int32_t Motor::get_direction() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        if(data->reversed){
            return data->actual_voltage > 0 ? -1 : 1;
        }
        return data->actual_voltage < 0 ? -1 : 1;
    }

    double Motor::get_efficiency() const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::is_over_current() const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::is_stopped() const{
        errno = ENOSYS;
        return PROS_ERR;
    }

    std::int32_t Motor::get_zero_position_flag() const{
        errno = ENOSYS;
        return PROS_ERR;
    }

    std::uint32_t Motor::get_faults() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->faults;
    }

    std::uint32_t Motor::get_flags() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->flags;
    }

    std::int32_t Motor::get_raw_position(std::uint32_t* const timestamp) const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::is_over_temp() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->flags & E_MOTOR_FAULT_MOTOR_OVER_TEMP ? 1 : 0;
    }

    double Motor::get_position() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR_F)
        return data->position;
    }

    double Motor::get_power() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR_F)
        return data->actual_voltage / 1000.0 * data->current_draw / 1000.0;
    }

    double Motor::get_temperature() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR_F)
        return data->temperature;
    }

    double Motor::get_torque() const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::get_voltage() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->actual_voltage;
    }

    std::int32_t Motor::set_zero_position(const double position) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->position = data->position - position;
        return 1;
    }

    std::int32_t Motor::tare_position() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->position = 0;
        return 1;
    }

    std::int32_t Motor::set_brake_mode(const motor_brake_mode_e_t mode) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->brake_mode = mode;
        return 1;
    }

    std::int32_t Motor::set_current_limit(const std::int32_t limit) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->current_limit = limit;
        return 1;
    }

    std::int32_t Motor::set_encoder_units(const motor_encoder_units_e_t units) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->encoder_units = units;
        return 1;
    }

    std::int32_t Motor::set_gearing(const motor_gearset_e_t gearset) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->gearset = gearset;
        return 1;
    }

    motor_pid_s_t Motor::convert_pid(double kf, double kp, double ki, double kd){
        throw emulator_error{"Unsupported function"};
    }

    motor_pid_full_s_t
    Motor::convert_pid_full(double kf, double kp, double ki, double kd, double filter, double limit, double threshold,
                            double loopspeed){
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::set_pos_pid(const motor_pid_s_t pid) const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::set_pos_pid_full(const motor_pid_full_s_t pid) const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::set_vel_pid(const motor_pid_s_t pid) const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::set_vel_pid_full(const motor_pid_full_s_t pid) const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::set_reversed(const bool reverse) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->reversed = reverse;
        return 1;
    }

    std::int32_t Motor::set_voltage_limit(const std::int32_t limit) const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        data->voltage_limit = limit;
        return 1;
    }

    motor_brake_mode_e_t Motor::get_brake_mode() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, E_MOTOR_BRAKE_INVALID)
        return data->brake_mode;
    }

    std::int32_t Motor::get_current_limit() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->current_limit;
    }

    motor_encoder_units_e_t Motor::get_encoder_units() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, E_MOTOR_ENCODER_INVALID)
        return data->encoder_units;
    }

    motor_gearset_e_t Motor::get_gearing() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, E_MOTOR_GEARSET_INVALID)
        return data->gearset;
    }

    motor_pid_full_s_t Motor::get_pos_pid() const{
        throw emulator_error{"Unsupported function"};
    }

    motor_pid_full_s_t Motor::get_vel_pid() const{
        throw emulator_error{"Unsupported function"};
    }

    std::int32_t Motor::is_reversed() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->reversed ? 1 : 0;
    }

    std::int32_t Motor::get_voltage_limit() const{
        auto* data = check_port(_port);
        CHECK_ACCESS_ERROR(data, PROS_ERR)
        return data->voltage_limit;
    }

#undef CHECK_ACCESS_ERROR
}
