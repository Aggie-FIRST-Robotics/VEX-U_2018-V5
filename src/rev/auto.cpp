#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"
#include "rev/auto.h"

namespace AFR::VexU::Rev::Auto{
    /////Commandables
    BaseCommandable::motor_commandable* ball_intake_motor = nullptr;

    /////Readables
    BaseReadable::digital_edge_detector* swallow_button = nullptr;

    /////State Controller

    state_controller<auto_meta>* auto_controller = nullptr;

    /////States
    state* zero = nullptr;
    state* grab_ball = nullptr;
    state* turn_to_cap = nullptr;
    state* turn_to_post = nullptr;
    state* go_to_post = nullptr;
    state* score_post = nullptr;
    state* turn_to_low_flag = nullptr;
    state* score_low_flag_1 = nullptr;
    state* back_off_low_flag = nullptr;
    state* turn_to_zero = nullptr;
    state* drive_to_plat = nullptr;
    state* turn_to_flag = nullptr;
    state* score_low_flag_2 = nullptr;
    state* line_up = nullptr;
    state* shoot = nullptr;
    state* end = nullptr;
    state *drive_to_zero = nullptr;

    void init(){
        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 44000}, "auto_controller"};

        zero = new state("zero");

        grab_ball = new state("grab_ball");
        turn_to_cap = new state("turn_to_cap");
        turn_to_post = new state("turn_to_post");
        go_to_post = new state("go_to_post");
        score_post = new state("score_post");

        turn_to_low_flag = new state("turn_to_low_flag");
        score_low_flag_1 = new state("score_low_flag_1");
        back_off_low_flag = new state("back_off_low_flag");
        turn_to_zero = new state("turn_to_zero");

        drive_to_plat = new state("drive_to_plat");
        drive_to_zero = new state("drive_to_zero");
        turn_to_flag = new state("turn_to_flag");
        score_low_flag_2 = new state("score_low_flag_2");

        line_up = new state("line_up");
        shoot = new state("shoot");

        end = new state("end");


        zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            std::cout << "Hey I'm in auto" << std::endl;
            Drive::drive_machine->maintain_state(Drive::autonomous);
            Drive::auto_drivetrain->enable();
            Cap::cap_arm->maintain_state(Cap::ground);
            Cap::Arm::pid_controller->set_target(0);
        }));

        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::ground;
        }), grab_ball);
        /////Timeout
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), grab_ball);
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        grab_ball->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Grab Ball" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(37, 30, 0, auto_controller->get_name());
            Shooter::Rollers::top_motor->set_operation(std::function<int16_t()>([](){
                if(Shooter::Rollers::limit_switch->is_pressed()) {
                    return 0;
                }
                else {
                    return 10000;
                }
            }), Shooter::shooter_state_controller->get_name());
            Shooter::Rollers::front_motor->set_operation(std::function<int16_t()>([](){
                if(Shooter::Rollers::limit_switch->is_pressed()) {
                    return 0;
                }
                else {
                    return 10000;
                }
            }), Shooter::shooter_state_controller->get_name());
        }));
        grab_ball->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_ball->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), turn_to_cap);
        /////Timeout
        grab_ball->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), turn_to_cap);
        grab_ball->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);

        turn_to_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Turn to cap" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(12, PI * 113.5 / 180.0, 35, 35,
                                                            auto_controller->get_name());
            Cap::Wrist::intake_motor->set_value(Cap::INTAKE_VOLTAGE, Cap::cap_arm->get_name());
        }));
        turn_to_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Trun to cap exit" << std::endl;
        }));

        turn_to_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), turn_to_post);
        /////Timeout
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), turn_to_post);
        turn_to_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);

        turn_to_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Turn to post" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 10000;
            Drive::auto_drivetrain->auto_drive_radius_angle(-23.2, PI * 110 / 180.0, 45, 45,
                                                            auto_controller->get_name());
            Cap::Arm::pid_controller->set_bounds(-8000, 8000);
            Cap::cap_arm->maintain_state(Cap::score_prime);
            Cap::Wrist::intake_motor->set_value(Cap::IDLE_VOLTAGE, Cap::cap_arm->get_name());
        }));
        turn_to_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Turn to post exit" << std::endl;
        }));

        turn_to_post->add_transition(std::function<bool()>([](){
            return Cap::limit_switch_1->is_pressed() || Cap::limit_switch_2->is_pressed();
        }), score_post);
        /////Timeout
        turn_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), score_post);
        turn_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        go_to_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "go_to_post entry" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(30.1, 85, 85, auto_controller->get_name());
        }));
        go_to_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "go_to_post exit" << std::endl;
        }));

        go_to_post->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), score_post);
        /////Timeout
        go_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), score_post);
        go_to_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        score_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Score post entry" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(1, 1, 0, auto_controller->get_name());
            Cap::cap_arm->set_state(Cap::score_prime);
        }));
        score_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Score post exit" << std::endl;
        }));

        score_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::descore_prime;
        }), turn_to_low_flag);
        /////Timeout
        score_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), turn_to_low_flag);
        score_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        turn_to_low_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "turn_to_low_flag entry" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-20, 30, 0, auto_controller->get_name());
//            Drive::auto_drivetrain->auto_drive_radius_angle(-8, -PI * 102 / 180.0, 45, 0, auto_controller->get_name());
            Cap::Arm::pid_controller->set_bounds(-12000, 12000);
        }));
        turn_to_low_flag->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "turn_to_low_flag exit" << std::endl;
        }));

        turn_to_low_flag->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
//        }), score_low_flag_1);
        }), end);
        /////Timeout
        turn_to_low_flag->add_transition(std::function<bool()>([](){
            if(pros::millis() > auto_controller->metadata().timeout){
                std::cout << "turn_to_low_flag timeout" << std::endl;
                return true;
            }
            return false;
//        }), score_low_flag_1);
        }), end);
        turn_to_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        score_low_flag_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "score_low_flag_1 entry" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-43, 50, 0, auto_controller->get_name());
            Cap::cap_arm->set_state(Cap::ground);
            Cap::Arm::pid_controller->set_target(Cap::ARM_GROUND_POSITION + 1250);

        }));
        score_low_flag_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "score_low_flag_1 exit" << std::endl;
        }));

        score_low_flag_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), back_off_low_flag);
        /////Timeout
        score_low_flag_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), back_off_low_flag);
        score_low_flag_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);

        back_off_low_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "back_off_low_flag exit" << std::endl;
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(30, 50, 0, auto_controller->get_name());
            Cap::Arm::pid_controller->set_target(Cap::ARM_GROUND_POSITION);

        }));
        back_off_low_flag->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        back_off_low_flag->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), turn_to_zero);
        /////Timeout
        back_off_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), turn_to_zero);
        back_off_low_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);

        turn_to_zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(0, PI * 217.0 / 180.0, 50, 0,
                                                            auto_controller->get_name());
        }));
        turn_to_zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_zero->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), drive_to_zero);
        /////Timeout
        turn_to_zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), drive_to_zero);
        turn_to_zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);

        drive_to_zero->set_on_state_entry(std::function<void(state *)>([](state *prev_state) {
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(1, 1, 0, auto_controller->get_name());
        }));
        drive_to_zero->set_on_state_exit(std::function<void(state *)>([](state *next_state) {

        }));

        /////Timeout
        drive_to_zero->add_transition(std::function<bool()>([]() {
            return pros::millis() > auto_controller->metadata().end_auto - 3000;
        }), shoot);
        drive_to_zero->add_transition(std::function<bool()>([]() {
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        drive_to_plat->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-48.5, 50, 0, auto_controller->get_name());
        }));
        drive_to_plat->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        drive_to_plat->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), turn_to_flag);
        /////Timeout
        drive_to_plat->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), turn_to_flag);
        drive_to_plat->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        turn_to_flag->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(0, PI * 105.0 / 180.0, 100, 100,
                                                            auto_controller->get_name());
        }));
        turn_to_flag->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_flag->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), score_low_flag_2);
        /////Timeout
        turn_to_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), score_low_flag_2);
        turn_to_flag->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        score_low_flag_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(21, 50, 50, auto_controller->get_name());
        }));
        score_low_flag_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_low_flag_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), line_up);
        /////Timeout
        score_low_flag_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), line_up);
        score_low_flag_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        line_up->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(-37.5, PI * 57.5 / 180.0, 100, 0,
                                                            auto_controller->get_name());

        }));
        line_up->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        line_up->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }), shoot);
        /////Timeout
        line_up->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), shoot);
        line_up->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);


        shoot->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::shooter_state_controller->metadata().is_double = true;
            Shooter::Altitude::pid->set_target(Shooter::ALTITUDE_HIGH_TARGET + 20);
            Shooter::shooter_state_controller->set_state(Shooter::cock);
        }));
        shoot->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot->add_transition(std::function<bool()>([](){
            return Shooter::shooter_state_controller->get_current_state() == Shooter::set_point;
        }), end);
        /////Timeout
        shoot->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }), end);
        shoot->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }), end);











        /////END
        end->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->disable();
        }));
        end->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));


        auto_controller->add_state(zero);
        auto_controller->add_state(grab_ball);
        auto_controller->add_state(turn_to_cap);
        auto_controller->add_state(turn_to_post);
        auto_controller->add_state(go_to_post);
        auto_controller->add_state(score_post);
        auto_controller->add_state(turn_to_low_flag);
        auto_controller->add_state(score_low_flag_1);
        auto_controller->add_state(back_off_low_flag);
        auto_controller->add_state(turn_to_zero);
        auto_controller->add_state(drive_to_plat);
        auto_controller->add_state(turn_to_flag);
        auto_controller->add_state(score_low_flag_2);
        auto_controller->add_state(line_up);
        auto_controller->add_state(shoot);
        auto_controller->add_state(end);

        auto_controller->set_state(zero);
    }

    void destroy() {

    }

    void reset() {
        auto_controller->set_state(zero);
    }
}
#pragma clang diagnostic pop