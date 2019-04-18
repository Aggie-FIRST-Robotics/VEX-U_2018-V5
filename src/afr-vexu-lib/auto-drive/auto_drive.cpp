#include "afr-vexu-lib/auto-drive/auto_drive.h"

namespace AFR::VexU::AutoDrive {

	auto_drive::auto_drive(double robot_width, double p_term, double i_term, double d_term, const std::string& name) : 
		scheduled(UPDATE_PERIOD, name),
		nameable(name),
		robot_width_(robot_width),
		left_wheel_pid(nullptr),
		right_wheel_pid(nullptr)
	{
		left_wheel_pid = new BaseAction::pid_action<double, int16_t>
			(UPDATE_PERIOD, p_term, i_term, d_term, -12000, 12000, -12000, 12000, 0, 0, 0, name+"-left-pid");
		right_wheel_pid = new BaseAction::pid_action<double, int16_t>
			(UPDATE_PERIOD, p_term, i_term, d_term, -12000, 12000, -12000, 12000, 0, 0, 0, name+"-right-pid");
	}

	void auto_drive::update_private(double delta_seconds) {
		if(!gyro_function_ || !left_wheel_function_ || !right_wheel_function_) {
			return;
		}
		double curr_left_dist = left_wheel_function_() - left_start_dist;
		double curr_right_dist = right_wheel_function_() - right_start_dist;
		double curr_angle = gyro_function_() - start_angle;
		std::cout << "Left dist: " << curr_left_dist << "\tRight dist: " << curr_right_dist << "\tAngle: " << curr_angle << std::endl;
		if(abs(left_wheel_dist_target-curr_left_dist) < DONE_THRESH && 
			abs(right_wheel_dist_target-curr_right_dist) < DONE_THRESH) {
			at_target = true;
		}
		else {
			at_target = false;
		}

		if(abs(left_wheel_vel_target) > abs(right_wheel_vel_target)) {
			double curr_target_angle = (curr_left_dist/left_wheel_dist_target)*(angle_target);
			double curr_right_wheel_dist_target = (curr_left_dist/left_wheel_dist_target)*(right_wheel_dist_target);
			
			double left_wheel_vel_target_set;
			double right_wheel_vel_target_set;
			if(abs(left_wheel_dist_target-curr_left_dist) < TRANS_THRESH) {
				left_wheel_vel_target_set = 
					(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
					(left_wheel_vel_target-left_vel_final) + left_vel_final;
				right_wheel_vel_target_set = 
					(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
					(right_wheel_vel_target-right_vel_final) + right_vel_final;
			}
			else{
				left_wheel_vel_target_set = left_wheel_vel_target;
				right_wheel_vel_target_set = right_wheel_vel_target;
			}

			curr_left_wheel_vel_target = left_wheel_vel_target_set;
			curr_right_wheel_vel_target = right_wheel_vel_target_set + 
				DIST_ERROR_GAIN*(curr_right_wheel_dist_target - curr_right_dist) +
				ANG_ERROR_GAIN*(curr_target_angle-curr_angle);
		}
		else {
			double curr_target_angle = (curr_right_dist/right_wheel_dist_target)*(angle_target);
			double curr_left_wheel_dist_target = (curr_right_dist/right_wheel_dist_target)*(left_wheel_dist_target);


			double left_wheel_vel_target_set;
			double right_wheel_vel_target_set;
			if(abs(right_wheel_dist_target-curr_right_dist) < TRANS_THRESH) {
				left_wheel_vel_target_set = 
					(abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH)*
					(left_wheel_vel_target-left_vel_final) + left_vel_final;
				right_wheel_vel_target_set = 
					(abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH)*
					(right_wheel_vel_target-right_vel_final) + right_vel_final;
			}
			else{
				left_wheel_vel_target_set = left_wheel_vel_target;
				right_wheel_vel_target_set = right_wheel_vel_target;
			}

			curr_right_wheel_vel_target = right_wheel_vel_target;
			curr_left_wheel_vel_target = left_wheel_vel_target + 
				DIST_ERROR_GAIN*(curr_left_wheel_dist_target - curr_left_dist) -
				ANG_ERROR_GAIN*(curr_target_angle-curr_angle);
		}
	}

	void auto_drive::set_gyro_function(const std::function<double()>& gyro_function) {
		gyro_function_ = gyro_function;
	}

	void auto_drive::set_left_wheel_function(const std::function<double()>& left_wheel_function) {
		left_wheel_function_ = left_wheel_function;
	}

	void auto_drive::set_right_wheel_function(const std::function<double()>& right_wheel_function) {
		right_wheel_function_ = right_wheel_function;
	}

	void auto_drive::set_left_wheel_vel_function(const std::function<double()>& left_wheel_vel_function) {
		left_wheel_vel_function_ = left_wheel_vel_function;
	}

	void auto_drive::set_right_wheel_vel_function(const std::function<double()>& right_wheel_vel_function) {
		right_wheel_vel_function_ = right_wheel_vel_function;
	}

	void auto_drive::auto_drive_dist(double left_distance, double right_distance, double max_vel, double final_vel, const std::string& caller) {
		if(!gyro_function_ || !left_wheel_function_ || !right_wheel_function_) {
			std::cout << "A sensor function for auto drive was not defined." << std::endl;
			return;
		}
		if(max_vel <= 0 || final_vel < 0) {
			std::cout << "Invalid target velocities." << std::endl;
			return;
		}

		left_start_dist = left_wheel_function_();
		right_start_dist = right_wheel_function_();
		start_angle = gyro_function_();

		left_wheel_dist_target = left_distance;
		right_wheel_dist_target = right_distance;

		if(abs(left_distance) > abs(right_distance)) {

			if(left_distance > 0) {
				left_wheel_vel_target = max_vel;
				left_vel_final = final_vel;
			}
			else {
				left_wheel_vel_target = -max_vel;
				left_vel_final = -final_vel;
				
			}
			right_wheel_vel_target = max_vel*right_distance/left_distance;
			right_vel_final = final_vel*right_distance/left_distance;
		}
		else {

			if(right_distance > 0) {
				right_wheel_vel_target = max_vel;
				right_vel_final = final_vel;
			}
			else {
				right_wheel_vel_target = -max_vel;
				right_vel_final = -final_vel;
				
			}
			left_wheel_vel_target = max_vel*left_distance/right_distance;
			left_vel_final = final_vel*left_distance/right_distance;
		}

		angle_target = (right_distance-left_distance)/robot_width_;

		curr_left_wheel_vel_target = left_wheel_vel_target;
		curr_right_wheel_vel_target = right_wheel_vel_target;

		left_wheel_pid->set_target(std::function<double()>([this]() {
			return curr_left_wheel_vel_target;
		}));

		right_wheel_pid->set_target(std::function<double()>([this]() {
			return curr_right_wheel_vel_target;
		}));

		left_wheel_pid->set_operation(left_wheel_vel_function_, caller);
		right_wheel_pid->set_operation(right_wheel_vel_function_, caller);
	}

	double auto_drive::left_drive_function() {
		return curr_left_wheel_vel_target;
	}

	double auto_drive::right_drive_function() {
		return curr_right_wheel_vel_target;
	}

	int16_t auto_drive::left_wheel_motor_val() {
		return left_wheel_pid->get_pid_value();
	}

	int16_t auto_drive::right_wheel_motor_val() {
		return right_wheel_pid->get_pid_value();
	}

	bool auto_drive::is_complete() {
		return at_target;
	}

	void auto_drive::on_enable() {
		left_wheel_pid->enable();
		right_wheel_pid->enable();
	}

	void auto_drive::on_disable() {
		left_wheel_pid->disable();
		right_wheel_pid->disable();
	}
}