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
		double curr_left_dist = left_wheel_function_();
		double curr_right_dist = right_wheel_function_();
		double curr_angle = gyro_function_() - start_angle;
		std::cout << "Left diastance remaining: " << left_wheel_dist_target - curr_left_dist << std::endl;
		std::cout << "Right diastance remaining: " << right_wheel_dist_target - curr_right_dist << std::endl;
		std::cout << "Radians travelled: " << curr_angle << std::endl;
		std::cout << "Radians left: " << angle_target - curr_angle << std::endl;
		std::cout << "Current Left Velocity Target: " << curr_left_wheel_vel_target << std::endl;
		std::cout << "Current Right Velocity Target: " << curr_right_wheel_vel_target << std::endl;
		if(abs(left_wheel_dist_target-curr_left_dist) < DONE_THRESH && 
			abs(right_wheel_dist_target-curr_right_dist) < DONE_THRESH) {
			at_target = true;
		}
		else {
			at_target = false;
		}

		double left_wheel_PID_target;
		double right_wheel_PID_target;

		if(abs(left_wheel_dist_target) > abs(curr_left_dist) || abs(right_wheel_dist_target) > abs(curr_right_dist)) {
			if(abs(left_wheel_dist_target-curr_left_dist) < TRANS_THRESH) {
				std::cout << "Left wheel PID: ( " << abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH << " ) * ( " << left_wheel_vel_target-left_vel_final << " ) + " << left_vel_final << " = " << (abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*(left_wheel_vel_target-left_vel_final) + left_vel_final << std::endl;
				std::cout << "Right wheel PID: ( " << abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH << " ) * ( " << left_wheel_vel_target-left_vel_final << " ) + " << right_vel_final << " = " << (abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH)*(right_wheel_vel_target-right_vel_final) + right_vel_final << std::endl;
				if(left_wheel_vel_target == left_vel_final) {
					left_wheel_PID_target = left_vel_final;
				}
				else {
					left_wheel_PID_target = 
						(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
						(left_wheel_vel_target-left_vel_final) + left_vel_final;
				}
				if(right_wheel_vel_target == right_vel_final) {
					right_wheel_PID_target = right_vel_final;
				}
				else {
					right_wheel_PID_target = 
						(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
						(right_wheel_vel_target-right_vel_final) + right_vel_final;
				}
			}
			else{
				left_wheel_PID_target = left_wheel_vel_target;
				right_wheel_PID_target = right_wheel_vel_target;
			}
		}
		else {
			left_wheel_PID_target = left_vel_final;
			right_wheel_PID_target = right_vel_final;
		}

		left_wheel_PID_target *= DIST_ERROR_GAIN;
		right_wheel_PID_target *= DIST_ERROR_GAIN;

		std::cout << "Left wheel PID: " << left_wheel_PID_target << std::endl;
		std::cout << "Right wheel PID: " << right_wheel_PID_target << std::endl;

		if(left_wheel_dist_target > right_wheel_dist_target) {
			if(radius_ > 0) {
				double left_wheel_angle_gain = abs(radius_ + (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				double right_wheel_angle_gain = abs(radius_ - (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				std::cout << "Left wheel angle gain: " << left_wheel_angle_gain << std::endl;
				std::cout << "Right wheel angle gain: " << right_wheel_angle_gain << std::endl;
				curr_left_wheel_vel_target = left_wheel_PID_target + left_wheel_angle_gain;
				if(radius_ > (robot_width_/2)) {
					curr_right_wheel_vel_target = right_wheel_PID_target + right_wheel_angle_gain;
				}
				else {
					curr_right_wheel_vel_target = right_wheel_PID_target - right_wheel_angle_gain;
				}
			}
			else {
				double left_wheel_angle_gain = abs(abs(radius_) - (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				double right_wheel_angle_gain = abs((radius_) + (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				std::cout << "Left wheel angle gain: " << left_wheel_angle_gain << std::endl;
				std::cout << "Right wheel angle gain: " << right_wheel_angle_gain << std::endl;
				curr_right_wheel_vel_target = right_wheel_PID_target - right_wheel_angle_gain;
				if(abs(radius_) > (robot_width_/2)) {
					curr_left_wheel_vel_target = left_wheel_PID_target - left_wheel_angle_gain;
				}
				else {
					curr_left_wheel_vel_target = left_wheel_PID_target + left_wheel_angle_gain;
				}
			}
		}
		else if (left_wheel_dist_target < right_wheel_dist_target){
			if(radius_ > 0) {
				double left_wheel_angle_gain = abs(radius_ + (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				double right_wheel_angle_gain = abs(radius_ - (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				std::cout << "Left wheel angle gain: " << left_wheel_angle_gain << std::endl;
				std::cout << "Right wheel angle gain: " << right_wheel_angle_gain << std::endl;
				curr_left_wheel_vel_target = left_wheel_PID_target - left_wheel_angle_gain;
				if(radius_ > (robot_width_/2.0)) {
					curr_right_wheel_vel_target = right_wheel_PID_target - right_wheel_angle_gain;
				}
				else {
					curr_right_wheel_vel_target = right_wheel_PID_target + right_wheel_angle_gain;
				}
			}
			else {
				double left_wheel_angle_gain = abs(abs(radius_) - (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				double right_wheel_angle_gain = abs((radius_) + (robot_width_/2.0))*abs(curr_angle - angle_target)*ANG_ERROR_GAIN;
				std::cout << "Left wheel angle gain: " << left_wheel_angle_gain << std::endl;
				std::cout << "Right wheel angle gain: " << right_wheel_angle_gain << std::endl;
				curr_right_wheel_vel_target = right_wheel_PID_target + right_wheel_angle_gain;
				if(abs(radius_) > (robot_width_/2.0)) {
					curr_left_wheel_vel_target = left_wheel_PID_target + left_wheel_angle_gain;
				}
				else {
					curr_left_wheel_vel_target = left_wheel_PID_target - left_wheel_angle_gain;
				}
			}
		}
		else {
			// double curr_target_angle = (curr_right_dist/right_wheel_dist_target)*(angle_target);
			curr_right_wheel_vel_target = right_wheel_PID_target;
			curr_left_wheel_vel_target = left_wheel_PID_target;
			std::cout << "Driving in a straight line" << std::endl;
		}

		// if(abs(left_wheel_vel_target) > abs(right_wheel_vel_target)) {
		// 	double curr_target_angle = (curr_left_dist/left_wheel_dist_target)*(angle_target);
		// 	double curr_right_wheel_dist_target = (curr_left_dist/left_wheel_dist_target)*(right_wheel_dist_target);
			
		// 	double left_wheel_vel_target_set;
		// 	double right_wheel_vel_target_set;
		// 	if(abs(left_wheel_dist_target-curr_left_dist) < TRANS_THRESH) {
		// 		left_wheel_vel_target_set = 
		// 			(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
		// 			(left_wheel_vel_target-left_vel_final) + left_vel_final;
		// 		right_wheel_vel_target_set = 
		// 			(abs(left_wheel_dist_target-curr_left_dist)/TRANS_THRESH)*
		// 			(right_wheel_vel_target-right_vel_final) + right_vel_final;
		// 	}
		// 	else{
		// 		left_wheel_vel_target_set = left_wheel_vel_target;
		// 		right_wheel_vel_target_set = right_wheel_vel_target;
		// 	}

		// 	curr_left_wheel_vel_target = left_wheel_vel_target_set;
		// 	curr_right_wheel_vel_target = right_wheel_vel_target_set + 
		// 		DIST_ERROR_GAIN*(curr_right_wheel_dist_target - curr_right_dist) +
		// 		ANG_ERROR_GAIN*(curr_target_angle-curr_angle);
		// }
		// else if (abs(left_wheel_vel_target) < abs(right_wheel_vel_target)){
		// 	double curr_target_angle = (curr_right_dist/right_wheel_dist_target)*(angle_target);
		// 	double curr_left_wheel_dist_target = (curr_right_dist/right_wheel_dist_target)*(left_wheel_dist_target);


		// 	double left_wheel_vel_target_set;
		// 	double right_wheel_vel_target_set;
		// 	if(abs(right_wheel_dist_target-curr_right_dist) < TRANS_THRESH) {
		// 		left_wheel_vel_target_set = 
		// 			(abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH)*
		// 			(left_wheel_vel_target-left_vel_final) + left_vel_final;
		// 		right_wheel_vel_target_set = 
		// 			(abs(right_wheel_dist_target-curr_right_dist)/TRANS_THRESH)*
		// 			(right_wheel_vel_target-right_vel_final) + right_vel_final;
		// 	}
		// 	else{
		// 		left_wheel_vel_target_set = left_wheel_vel_target;
		// 		right_wheel_vel_target_set = right_wheel_vel_target;
		// 	}

		// 	curr_right_wheel_vel_target = right_wheel_vel_target;
		// 	curr_left_wheel_vel_target = left_wheel_vel_target + 
		// 		DIST_ERROR_GAIN*(curr_left_wheel_dist_target - curr_left_dist) -
		// 		ANG_ERROR_GAIN*(curr_target_angle-curr_angle);
		// }
		// else {

		// }
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

	void auto_drive::set_reset_function(const std::function<void()>& rst_function) {
		rst_function_ = rst_function;
	}

	void auto_drive::auto_drive_dist(double distance, double max_vel, double final_vel, const std::string& caller) {
		if(!gyro_function_ || !left_wheel_function_ || !right_wheel_function_) {
			std::cout << "A sensor function for auto drive was not defined." << std::endl;
			return;
		}
		if(max_vel <= 0 || final_vel < 0) {
			std::cout << "Invalid target velocities." << std::endl;
			return;
		}
		if(distance == 0) {
			std::cout << "Cannot set distance to 0" << std::endl;
			return;
		}

		radius_ = 0;
		left_wheel_dist_target = distance;
		right_wheel_dist_target = distance;
		if(distance > 0) {
			left_wheel_vel_target = max_vel;
			right_wheel_vel_target = max_vel;
			left_vel_final = final_vel;
			right_vel_final = final_vel;
		}
		else {
			left_wheel_vel_target = -max_vel;
			right_wheel_vel_target = -max_vel;
			left_vel_final = -final_vel;
			right_vel_final = -final_vel;
		}

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

		rst_function_();
		start_angle = gyro_function_();
		angle_target = start_angle;
	}

	void auto_drive::auto_drive_radius_angle(double radius, double angle, double max_vel, double final_vel, const std::string& caller) {
		if(!gyro_function_ || !left_wheel_function_ || !right_wheel_function_) {
			std::cout << "A sensor function for auto drive was not defined." << std::endl;
			return;
		}
		if(max_vel <= 0 || final_vel < 0) {
			std::cout << "Invalid target velocities." << std::endl;
			return;
		}
		radius_ = radius;

		double max_angular_velocity;
		double final_angular_velocity;
		if(radius == 0) {
			left_wheel_dist_target = -(robot_width_/2.0)*angle;
			right_wheel_dist_target = (robot_width_/2.0)*angle;
			if(angle > 0) {
				std::cout << "Radius is 0 and the angle is POSITIVE" << std::endl;
				left_wheel_vel_target = -max_vel;
				right_wheel_vel_target = max_vel;
				left_vel_final = -final_vel;
				right_vel_final = final_vel;
			}
			else {
				std::cout << "Radius is 0 and the angle is NEGATIVE" << std::endl;
				left_wheel_vel_target = max_vel;
				right_wheel_vel_target = -max_vel;
				left_vel_final = final_vel;
				right_vel_final = -final_vel;
			}
		}
		else if(radius > 0) {
			left_wheel_dist_target = -(radius + (robot_width_/2.0))*angle;
			max_angular_velocity = max_vel/(radius + (robot_width_/2.0));
			final_angular_velocity = final_vel/(radius + (robot_width_/2.0));
			if(radius <= robot_width_/2.0) {
				right_wheel_dist_target = ((robot_width_/2.0) - radius)*angle;
				if(angle > 0) {
					std::cout << "Radius is POSITIVE and SMALLER THEN HALF THE ROBOT, the angle is POSITIVE" << std::endl;
					left_wheel_vel_target = -max_vel;
					right_wheel_vel_target = max_angular_velocity*((robot_width_/2.0) - radius);
					left_vel_final = -final_vel;
					right_vel_final = final_angular_velocity*((robot_width_/2.0) - radius);
				}
				else {
					std::cout << "Radius is POSITIVE and SMALLER THER HALF THE ROBOT, the angle is NEGATIVE" << std::endl;
					left_wheel_vel_target = max_vel;
					right_wheel_vel_target = -max_angular_velocity*((robot_width_/2.0) - radius);
					left_vel_final = final_vel;
					right_vel_final = -final_angular_velocity*((robot_width_/2.0) - radius);
				}
			}
			else {
				right_wheel_dist_target = -(radius - (robot_width_/2.0))*angle;
				if(angle > 0) {
					std::cout << "Radius is POSITIVE and the angle is POSITIVE" << std::endl;
					left_wheel_vel_target = -max_vel;
					right_wheel_vel_target = -max_angular_velocity*(radius - (robot_width_/2.0));
					left_vel_final = -final_vel;
					right_vel_final = -final_angular_velocity*(radius - (robot_width_/2.0));
				}
				else {
					std::cout << "Radius is POSITIVE and the angle is NEGATIVE" << std::endl;
					left_wheel_vel_target = max_vel;
					right_wheel_vel_target = max_angular_velocity*(radius - (robot_width_/2.0));
					left_vel_final = final_vel;
					right_vel_final = final_angular_velocity*(radius - (robot_width_/2.0));
				}
			}
		}
		else {
			right_wheel_dist_target = (abs(radius) + (robot_width_/2.0))*angle;
			max_angular_velocity = max_vel/(abs(radius) + (robot_width_/2.0));
			final_angular_velocity = final_vel/(abs(radius) + (robot_width_/2.0));
			if(abs(radius) <= robot_width_/2.0) {
				left_wheel_dist_target = -((robot_width_/2.0) - abs(radius))*angle;
				if(angle > 0) {
					std::cout << "Radius is NEGATIVE and SMALLER THEN HALF THE ROBOT, the angle is POSITIVE" << std::endl;
					right_wheel_vel_target = max_vel;
					left_wheel_vel_target = -max_angular_velocity*((robot_width_/2.0) - abs(radius));
					right_vel_final = final_vel;
					left_vel_final = -final_angular_velocity*((robot_width_/2.0) - abs(radius));
				}
				else {
					std::cout << "Radius is NEGATIVE and SMALLER THEN HALF THE ROBOT, the angle is NEGATIVE" << std::endl;
					right_wheel_vel_target = -max_vel;
					left_wheel_vel_target = max_angular_velocity*((robot_width_/2.0) - abs(radius));
					right_vel_final = -final_vel;
					left_vel_final = final_angular_velocity*((robot_width_/2.0) - abs(radius));
				}
			}
			else {
				left_wheel_dist_target = (abs(radius) - (robot_width_/2.0))*angle;
				if(angle > 0) {
					std::cout << "Radius is NEGATIVE and the angle is POSITIVE" << std::endl;
					right_wheel_vel_target = max_vel;
					left_wheel_vel_target = max_angular_velocity*(abs(radius) - (robot_width_/2.0));
					right_vel_final = final_vel;
					left_vel_final = final_angular_velocity*(abs(radius) - (robot_width_/2.0));
				}
				else {
					std::cout << "Radius is NEGATIVE and the angle is NEGATIVE" << std::endl;
					right_wheel_vel_target = -max_vel;
					left_wheel_vel_target = -max_angular_velocity*(abs(radius) - (robot_width_/2.0));
					right_vel_final = -final_vel;
					left_vel_final = -final_angular_velocity*(abs(radius) - (robot_width_/2.0));
				}
			}
		}
		std::cout << "Left wheel distance to travel: " << left_wheel_dist_target << std::endl;
		std::cout << "Right wheel distance to travel: " << right_wheel_dist_target << std::endl;
		std::cout << "Left wheel MAX velocity: " << left_wheel_vel_target << std::endl;
		std::cout << "Right wheel MAX velocity: " << right_wheel_vel_target << std::endl;
		std::cout << "Left wheel FINAL velocity: " << left_vel_final << std::endl;
		std::cout << "Right wheel FINAL velocity: " << right_vel_final << std::endl;

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

		rst_function_();
		start_angle = gyro_function_();
		angle_target = start_angle + angle;
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