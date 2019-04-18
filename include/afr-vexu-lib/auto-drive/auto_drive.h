#ifndef VEX_U_2018_V5_AUTO_DRIVE_H
#define VEX_U_2018_V5_AUTO_DRIVE_H

#include <functional>
#include <iostream>

#include "afr-lib/nameable.h"
#include "afr-lib/scheduled.h"
#include "afr-lib/defines.h"
#include "afr-vexu-lib/base-action/pid_action.h"

namespace AFR::VexU::AutoDrive {

	class auto_drive : public scheduled, public virtual nameable {

		static constexpr int UPDATE_PERIOD = 10;
		static constexpr double DIST_ERROR_GAIN = 1;
		static constexpr double ANG_ERROR_GAIN = 0;
		static constexpr double TRANS_THRESH = 8;
		static constexpr double DONE_THRESH = 0.5;

		BaseAction::pid_action<double, int16_t>* left_wheel_pid;
		BaseAction::pid_action<double, int16_t>* right_wheel_pid;

		std::function<double()> gyro_function_;
		std::function<double()> left_wheel_function_;
		std::function<double()> right_wheel_function_;
			std::function<double()> left_wheel_vel_function_;
		std::function<double()> right_wheel_vel_function_;
		
		double robot_width_;

		double left_start_dist;
		double right_start_dist;
		double start_angle;

		double left_wheel_vel_target;
		double right_wheel_vel_target;
		double left_wheel_dist_target;
		double right_wheel_dist_target;
		double angle_target;
		double left_vel_final;
		double right_vel_final;

		double curr_left_wheel_vel_target;
		double curr_right_wheel_vel_target;

		bool at_target;

		double left_drive_function();
		double right_drive_function();
		void on_enable() override;
		void on_disable() override;
		void update_private(double delta_seconds) override;

	public:

		auto_drive(double robot_width, double p_term, double i_term, double d_term, const std::string& name);
		void set_gyro_function(const std::function<double()>& gyro_function);
		void set_left_wheel_function(const std::function<double()>& left_wheel_function);
		void set_right_wheel_function(const std::function<double()>& right_wheel_function);
		void set_left_wheel_vel_function(const std::function<double()>& left_wheel_vel_function);
		void set_right_wheel_vel_function(const std::function<double()>& right_wheel_vel_function);

		void auto_drive_dist(double left_distance, double right_distance, double max_vel, double final_vel, const std::string& caller);
		void auto_drive_dist_angle(double wheel_dist, double angle, double max_vel);
		void auto_drive_radius_angle(double radius, double angle, double max_vel);

		int16_t left_wheel_motor_val();
		int16_t right_wheel_motor_val();
		bool is_complete();

	};

}

#endif //VEX_U_2018_V5_AUTO_DRIVE_H