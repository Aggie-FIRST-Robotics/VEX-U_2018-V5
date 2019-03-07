
#ifndef VEX_U_2018_V5_PID_H
#define VEX_U_2018_V5_PID_H
#include "afr-vexu-lib/readable.h"
#include "afr-vexu-lib/action.h"
#include "targetable.h"
//min max -12000, +12000 imin imax -6000, 6000

namespace AFR::VexU::BaseAction{
    template<typename Read_T, typename Write_T>
    class pid_action : public targetable<Read_T>{
        double _p_value;
        double _i_value;
        double _d_value;
        Write_T _min_value;
        Write_T _max_value;
        Write_T _min_i_value;
        Write_T _max_i_value;
        Write_T _offset;
        readable* _value_pointer;
        Read_T _set_point;

        double last_error;
        Read_T last_value;
        double i_term;
        bool running;
        Read_T read_value_;
        Write_T pid_value_;
        Write_T disabled_value_;

        void set_value_private(Read_T value, const double& delta_seconds){
            read_value_ = value;
            double error = static_cast<double>(_set_point - value);
            double p_term = _p_value * error;

            double d_term;

            //Only calculate i and d terms if reasonable time delta and enabled
            if(running && delta_seconds > 0.001){
                i_term += i_term * error * delta_seconds;

                //clamp i value
                if(i_term > _max_i_value){
                    i_term = _max_i_value;
                }
                else if(i_term < _min_i_value){
                    i_term = _min_i_value;
                }

                d_term = static_cast<double>(last_value) - 
                    static_cast<double>(value) * _d_value / delta_seconds;
            }
            else{
                d_term = 0;
                running = true;
            }
            double write_value = p_term + i_term + d_term + _offset;

            //clamp write value
            if(write_value > _max_value){
                write_value = _max_value;
            }
            else if(write_value < _min_value){
                write_value = _min_value;
            }

            last_value = value;
            pid_value_ = static_cast<Write_T>(write_value);
        }

    public:

        bool is_in_range(Read_T tolerance) override {
            return abs(read_value_ - _set_point) <= abs(tolerance) && running;
        }

        Read_T get_target(){
            return _set_point;
        }

        void set_pid_constants(double p_value, double i_value, double d_value){
            _p_value = p_value;
            _i_value = i_value;
            _d_value = d_value;
        }

        void set_bounds(Write_T min_value, Write_T max_value){
            _min_value = min_value;
            _max_value = max_value;
        }

        void set_i_bounds(Write_T min_i_value, Write_T max_i_value){
            _min_i_value = min_i_value;
            _max_i_value = max_i_value;
        }

        void set_offset(Write_T offset){
            _offset = offset;
        }
        
        void set_disabled_value(Write_T disabled_value) {
            disabled_value_ = disabled_value;
        }
        
        void on_disable() override {
            running = false;
            pid_value_ = disabled_value_;
        }
        
        Write_T get_pid_value() {
            return pid_value_;
        }

        /**
         * Creates a PID action
         * @param update_period passed to scheduled
         * @param commandable passed to action
         * @param p_value P constant
         * @param i_value I constant
         * @param d_value D constant
         * @param min_value minimum allowable value
         * @param max_value maximum allowable value
         * @param min_i_value minimun allowable I term
         * @param max_i_value maximum allowable I term
         * @param offset offset for calculated output
         * @param value_ptr the pointer to the value to be copied every update
         * @param set_point target value for controller
         * @param name error_t value if error encountered
         */
        pid_action(scheduled_update_t update_period, double p_value,
            double i_value, double d_value, Write_T min_value, Write_T max_value,
            Write_T min_i_value, Write_T max_i_value, Write_T offset, Write_T disabled_value,
            Read_T set_point, const std::string& name) :
                targetable<Read_T>(update_period, set_point, name), 
                _p_value(p_value), 
                _i_value(i_value),
                _d_value(d_value), 
                _min_value(min_value), 
                _max_value(max_value), 
                _min_i_value(min_i_value),
                _max_i_value(max_i_value), 
                _offset(offset),  
                _set_point(set_point),
                last_error(0), 
                last_value(0), 
                i_term(0), 
                running(false), 
                read_value_(0), 
                pid_value_(disabled_value),
                disabled_value_(disabled_value)
                {}
    };




}

#endif
