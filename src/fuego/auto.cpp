#include "fuego/auto.h"

namespace AFR::VexU::Fuego::Auto{
    /////Commandables
    BaseCommandable::motor_commandable* ball_intake_motor = nullptr;

    /////Readables
    BaseReadable::digital_edge_detector* swallow_button = nullptr;

    /////State Controller
    
    struct auto_meta {
        unsigned int timeout;
        unsigned int end_auto;
    };

    state_controller<auto_meta>* auto_controller = nullptr;

    /////States
    state* zero = nullptr;
    state* drive_test = nullptr;
    state* grab_tilted_cap = nullptr;
    state* stow_tilted_cap = nullptr;
    state* move_tilted_cap = nullptr;
    state* prime_tilted_cap = nullptr;
    state* score_tilted_cap = nullptr;
    state* succ_blue_cap = nullptr;
    state* slide_to_the_right = nullptr;
    state* cha_cha_real_smooth = nullptr;
    state* score_second_post = nullptr;
    state* turn_to_aim_1 = nullptr;
    state* line_up_1 = nullptr;
    state* aim_high_1 = nullptr;
    state* shoot_high_1 = nullptr;
    state* set_shooter_1 = nullptr;
    state* aim_low_1 = nullptr;
    state* shoot_low_1 = nullptr;
    state* wind_down_1 = nullptr;
    state* move_to_plat = nullptr;
    state* turn_to_plat_1 = nullptr;
    state* charge_plat_1 = nullptr;
    state* sweep_1 = nullptr;
    state* move_away_1 = nullptr;
    state* turn_to_plat_2 = nullptr;
    state* charge_plat_2 = nullptr;
    state* sweep_2 = nullptr;
    state* move_away_2 = nullptr;
    state* final_turn_1 = nullptr;
    state* get_ready = nullptr;
    state* final_turn_2 = nullptr;
    state* line_up_2 = nullptr;
    state* charge_plat_3 = nullptr;
    state* deploy_dick = nullptr;
    state* stow_dick = nullptr;
    state* zero_everything = nullptr;
    state* back_up = nullptr;
    state* turn_to_aim_2 = nullptr;
    state* aim_high_2 = nullptr;
    state* shoot_high_2 = nullptr;
    state* set_shooter_2 = nullptr;
    state* aim_low_2 = nullptr;
    state* shoot_low_2 = nullptr;
    state* wind_down_2 = nullptr;
    state* end = nullptr;

    void init(){
        auto_controller = new state_controller<auto_meta>{UPDATE_PERIOD, {0, pros::millis() + 44000}, "auto_controller"};

        //Score Cap #1
        zero = new state("zero");
        grab_tilted_cap = new state("grab_tilted_cap");
        stow_tilted_cap = new state("stow_tiletd_cap");
        move_tilted_cap = new state("move_tilted_cap");
        prime_tilted_cap = new state("prime_tilted_cap");
        score_tilted_cap = new state("score_tilted_cap");

        //Score Cap #2
        succ_blue_cap = new state("succ_blue_cap");
        slide_to_the_right = new state("slide_to_the_right");
        cha_cha_real_smooth = new state("cha_cha_real_smooth");
        score_second_post = new state("score_second_post");

        //Shoot Close 2 Flags
        turn_to_aim_1 = new state("turn_to_aim_1");
        line_up_1 = new state("line_up_1");
        aim_high_1 = new state("aim_high_1");
        shoot_high_1 = new state("shoot_high_1");
        set_shooter_1 = new state("set_shooter_1");
        aim_low_1 = new state("aim_low_1");
        shoot_low_1 = new state("shoot_low_1");
        wind_down_1 = new state("wind_down_1");

        //Grab Balls off Platform
        move_to_plat = new state("move_to_plat");
        turn_to_plat_1 = new state("turn_to_plat_1");
        charge_plat_1 = new state("charge_plat_1");
        sweep_1 = new state("sweep_1");
        move_away_1 = new state("move_away_1");
        turn_to_plat_2 = new state("turn_to_plat_2");
        charge_plat_2 = new state("charge_plat_2");
        sweep_2 = new state("sweep_2");
        move_away_2 = new state("move_away_2");

        //Drive up the Platform
        final_turn_1 = new state("final_turn_1");
        final_turn_2 = new state("final_turn_2");
        get_ready = new state("get_ready");
        line_up_2 = new state("line_up_2");
        charge_plat_3 = new state("charge_plat_3");
        deploy_dick = new state("deploy_dick");
        stow_dick = new state("stow_dick");
        zero_everything = new state("zero_everything");

        //Shoot the last 2 Flags
        back_up = new state("back_up");
        turn_to_aim_2 = new state("turn_to_aim_2");
        aim_high_2 = new state("aim_high_2");
        shoot_high_2 = new state("shoot_high_2");
        set_shooter_2 = new state("set_shooter_2");
        aim_low_2 = new state("aim_low_2");
        shoot_low_2 = new state("shoot_low_2");
        wind_down_2 = new state("wind_down_2");

        end = new state("end");










        Drive::drive_machine->maintain_state(Drive::autonomous);
        /////Zero
        zero->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
            // return false;
        }),grab_tilted_cap);
        /////Timeout
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),grab_tilted_cap);
        zero->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Grab Tilted Cap
        grab_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->maintain_state(Cap::angled_pickup);
            BallIntake::ball_intake_controller->maintain_state(BallIntake::swallow);
            Drive::auto_drivetrain->auto_drive_dist(37, 50, 50, auto_controller->get_name());
        }));
        grab_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),stow_tilted_cap);
        /////Timeout
        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),stow_tilted_cap);
        grab_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Grab Tilted Cap
        stow_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::Arm::pid_controller->set_bounds(1000,-1000);
            Cap::cap_arm->set_state(Cap::store);
            Cap::Wrist::pid_controller->set_target(Cap::wrist_flip_target());
            Drive::auto_drivetrain->auto_drive_dist(10, 50, 0, auto_controller->get_name());
        }));
        stow_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        stow_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),move_tilted_cap);
        /////Timeout
        stow_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),move_tilted_cap);
        stow_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);


        /////Move Tilted Cap
        move_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(12.25,Drive::PI*115.0/180.0,50,50,auto_controller->get_name());
        }));
        move_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::Arm::pid_controller->set_bounds(12000,-12000);
        }));

        move_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),prime_tilted_cap);
        /////Timeout
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),prime_tilted_cap);
        move_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        /////Prime Tilted Cap
        prime_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->maintain_state(Cap::score_prime);
            Drive::auto_drivetrain->auto_drive_dist(-10, 50, 50, auto_controller->get_name());
        }));
        prime_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        prime_tilted_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),score_tilted_cap);
        /////Timeout
        prime_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_tilted_cap);

        /////Score Tilted Cap
        score_tilted_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::score_prime);

        }));
        score_tilted_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_tilted_cap->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),succ_blue_cap);
        /////Timeout
        score_tilted_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),succ_blue_cap);



























        /////Suck Blue Cap
        succ_blue_cap->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            BallIntake::ball_intake_controller->maintain_state(BallIntake::choke);
            Cap::cap_arm->set_state(Cap::ground);
            Drive::auto_drivetrain->auto_drive_radius_angle(FUEGO_WIDTH/2.0 - 1,-Drive::PI*150.0/180.0,60,60,auto_controller->get_name());
            Cap::Wrist::intake_motor->set_value(Cap::INTAKE_VOLTAGE, Cap::cap_arm->get_name());
        }));
        succ_blue_cap->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::cap_arm->set_state(Cap::angled_pickup);
        }));

        succ_blue_cap->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),slide_to_the_right);
        /////Timeout
        succ_blue_cap->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),slide_to_the_right);

        /////Slide to the right
        slide_to_the_right->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(17,Drive::PI*37.0/180.0,70,70,auto_controller->get_name());
        }));
        slide_to_the_right->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        slide_to_the_right->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),cha_cha_real_smooth);
        /////Timeout
        slide_to_the_right->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),cha_cha_real_smooth);

        /////cha_cha_real_smooth
        cha_cha_real_smooth->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
            Cap::cap_arm->maintain_state(Cap::score_prime);
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-30, 50, 20, auto_controller->get_name());
        }));
        cha_cha_real_smooth->set_on_state_exit(std::function<void(state*)>([](state* next_state){
             
        }));

        cha_cha_real_smooth->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),score_second_post);
        /////Timeout
        cha_cha_real_smooth->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),score_second_post);

        /////Score second post
        score_second_post->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::score_prime);
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
        }));
        score_second_post->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        score_second_post->add_transition(std::function<bool()>([](){
            return Cap::cap_arm->get_current_state() == Cap::store;
        }),turn_to_aim_1);
        /////Timeout
        score_second_post->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_aim_1);
































        /////Turn to aim 1
        turn_to_aim_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(FUEGO_WIDTH/2.0 - 1,-Drive::PI*120.0/180.0,100,0,auto_controller->get_name());
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_HIGH_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            
        }));
        turn_to_aim_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_aim_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),line_up_1);
        /////Timeout
        turn_to_aim_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),line_up_1);

        /////Line up for shot
        line_up_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 1000;
            Drive::auto_drivetrain->auto_drive_dist(17.5, 100, 100, auto_controller->get_name());
        }));
        line_up_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        line_up_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),move_to_plat);
        /////Timeout
        line_up_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),move_to_plat);

        /////Move to the platform
        move_to_plat->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::drive_machine->maintain_state(Drive::autonomous);
            Drive::auto_drivetrain->auto_drive_dist(-40, 50, 0, auto_controller->get_name());
        }));
        move_to_plat->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        move_to_plat->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),aim_high_1);
        /////Timeout
        move_to_plat->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_high_1);

        /////Aim High 1
        aim_high_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_high_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_high_1->add_transition(std::function<bool()>([](){
            return Shooter::Flywheel::pid_controller->is_in_range(10) && Shooter::vision->aiming_complete();
        }),shoot_high_1);
        /////Timeout
        aim_high_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_high_1);

        /////Shoot High 1
        shoot_high_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 500;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_high_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot_high_1->add_transition(std::function<bool()>([](){
            return false;
        }),set_shooter_1);
        /////Timeout
        shoot_high_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),set_shooter_1);

        /////Set Turret 1
        set_shooter_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_MID_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
        }));
        set_shooter_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        set_shooter_1->add_transition(std::function<bool()>([](){
            return Shooter::Hood::pid->is_in_range(50) && Shooter::Turret::pid->is_in_range(100);
        }),aim_low_1);
        /////Timeout
        set_shooter_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_low_1);

        /////Aim Low 1
        aim_low_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_low_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_low_1->add_transition(std::function<bool()>([](){
            return Shooter::Flywheel::pid_controller->is_in_range(10) && Shooter::vision->aiming_complete();
        }),shoot_low_1);
        /////Timeout
        aim_low_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_low_1);

        /////Shoot High 1
        shoot_low_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_low_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot_low_1->add_transition(std::function<bool()>([](){
            return Shooter::shooter_state_controller->get_current_state() == Shooter::spin_up && Shooter::Loader::dead_band->is_in_range(Shooter::LOADER_TOLERANCE);
        }),wind_down_1);
        /////Timeout
        shoot_low_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),wind_down_1);

        /////Wind down 1
        wind_down_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 1000;
        }));
        wind_down_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Shooter::shooter_state_controller->maintain_state(Shooter::rest);
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = 0;
            Shooter::turret_state_controller->metadata().turret_set_point = 0;
        }));

        /////Timeout
        wind_down_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_plat_1);



































        /////Turns the robot to face the plate
        turn_to_plat_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(0,Drive::PI*115.0/180.0,50,50,auto_controller->get_name());
        }));
        turn_to_plat_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_plat_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),charge_plat_1);
        /////Timeout
        turn_to_plat_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),charge_plat_1);

        /////Positions tobot to get the first ball
        charge_plat_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(15, 50, 0, auto_controller->get_name());
            Cap::cap_arm->maintain_state(Cap::ball_prime);
            BallIntake::ball_intake_controller->maintain_state(BallIntake::swallow);
        }));
        charge_plat_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        charge_plat_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),sweep_1);
        /////Timeout
        charge_plat_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),sweep_1);

        /////Pulls arm down
        sweep_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->maintain_state(Cap::ball_sweep);
        }));
        sweep_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        sweep_1->add_transition(std::function<bool()>([](){
            return Cap::Elbow::pid_controller->is_in_range(Cap::PID_TOLERANCE) && Cap::Arm::pid_controller->is_in_range(Cap::PID_TOLERANCE);
        }),move_away_1);
        /////Timeout
        sweep_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),move_away_1);

        /////Moves back to intake the ball
        move_away_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_dist(-22, 15, 0, auto_controller->get_name());
        }));
        move_away_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        move_away_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),turn_to_plat_2);
        /////Timeout
        move_away_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_plat_2);

        /////Turns to the platform at an angle
        turn_to_plat_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(0,Drive::PI*125.0/180.0,30,30,auto_controller->get_name());
        }));
        turn_to_plat_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_plat_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),charge_plat_2);
        /////Timeout
        turn_to_plat_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),charge_plat_2);

        /////Charges the plate to pick up the ball
        charge_plat_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(18.5,-Drive::PI*106.0/180.0,50,0,auto_controller->get_name());
            Cap::cap_arm->set_state(Cap::ball_prime);
        }));
        charge_plat_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        charge_plat_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),sweep_2);
        /////Timeout
        charge_plat_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),sweep_2);
        /////Shoot High 1
        sweep_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::ball_sweep);
        }));
        sweep_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        sweep_2->add_transition(std::function<bool()>([](){
            return Cap::Elbow::pid_controller->is_in_range(Cap::PID_TOLERANCE) && Cap::Arm::pid_controller->is_in_range(Cap::PID_TOLERANCE);
        }),move_away_2);
        /////Timeout
        sweep_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),move_away_2);
        /////Shoot High 1
        move_away_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(-15, 15, 0, auto_controller->get_name());
        }));
        move_away_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Cap::cap_arm->set_state(Cap::zero_arm);
        }));

        move_away_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),final_turn_1);
        /////Timeout
        move_away_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),final_turn_1);


























        final_turn_1->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_radius_angle(0,-Drive::PI*110.0/180.0,70,0,auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        final_turn_1->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        final_turn_1->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),get_ready);
        /////Timeout
        final_turn_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),get_ready);
        final_turn_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        get_ready->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(14.5, 50, 0, auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        get_ready->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        get_ready->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),final_turn_2);
        /////Timeout
        get_ready->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),final_turn_2);
        get_ready->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        final_turn_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_radius_angle(0,-Drive::PI*110.0/180.0,70,0,auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        final_turn_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        final_turn_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),line_up_2);
        /////Timeout
        final_turn_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),line_up_2);
        final_turn_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        line_up_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(18, 80, 800, auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 1000;
        }));
        line_up_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        line_up_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),charge_plat_3);
        /////Timeout
        line_up_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),charge_plat_3);
        line_up_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        charge_plat_3->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(-7.5, 100, 100, auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        charge_plat_3->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        charge_plat_3->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),deploy_dick);
        /////Timeout
        charge_plat_3->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),deploy_dick);
        charge_plat_3->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        deploy_dick->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(-23.5, 100, 100, auto_controller->get_name());
            Cap::cap_arm->maintain_state(Cap::dick);
            Shooter::shooter_state_controller->maintain_state(Shooter::walk);
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        deploy_dick->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        deploy_dick->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),stow_dick);
        /////Timeout
        deploy_dick->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),stow_dick);
        deploy_dick->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        stow_dick->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(-15, 100, 100, auto_controller->get_name());
            Cap::cap_arm->maintain_state(Cap::ascend);
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        stow_dick->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        stow_dick->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),zero_everything);
        /////Timeout
        stow_dick->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),zero_everything);
        stow_dick->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);

        zero_everything->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            Drive::auto_drivetrain->auto_drive_dist(-25, 100, 100, auto_controller->get_name());
            auto_controller->metadata().timeout = pros::millis() + 5000;
        }));
        zero_everything->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        zero_everything->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),back_up);
        /////Timeout
        zero_everything->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),back_up);
        zero_everything->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().end_auto;
        }),end);




















        /////Back up
        back_up->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Cap::cap_arm->set_state(Cap::zero_arm);
            Drive::auto_drivetrain->auto_drive_dist(7.5, 15, 0, auto_controller->get_name());
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_HIGH_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            
        }));
        back_up->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        back_up->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),turn_to_aim_2);
        /////Timeout
        back_up->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),turn_to_aim_2);

        /////Turn to aim 2
        turn_to_aim_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Drive::auto_drivetrain->auto_drive_radius_angle(0,Drive::PI*45.0/180.0,100,0,auto_controller->get_name());
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_HIGH_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            
        }));
        turn_to_aim_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        turn_to_aim_2->add_transition(std::function<bool()>([](){
            return Drive::auto_drivetrain->is_complete();
        }),aim_high_2);
        /////Timeout
        turn_to_aim_1->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_high_2);


        /////Aim High 2
        aim_high_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            BallIntake::ball_intake_controller->set_state(BallIntake::choke);
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_high_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_high_2->add_transition(std::function<bool()>([](){
            return Shooter::Flywheel::pid_controller->is_in_range(10) && Shooter::vision->aiming_complete();
        }),shoot_high_2);
        /////Timeout
        aim_high_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_high_2);

        /////Shoot High 1
        shoot_high_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 500;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_high_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot_high_2->add_transition(std::function<bool()>([](){
            return false;
        }),set_shooter_2);
        /////Timeout
        shoot_high_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),set_shooter_2);

        /////Set Turret 1
        set_shooter_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = Shooter::HOOD_MID_TARGET;
            Shooter::turret_state_controller->metadata().turret_set_point = Shooter::TURRET_MID_TARGET;
            Shooter::shooter_state_controller->maintain_state(Shooter::spin_up);
        }));
        set_shooter_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        set_shooter_2->add_transition(std::function<bool()>([](){
            return Shooter::Hood::pid->is_in_range(50) && Shooter::Turret::pid->is_in_range(100);
        }),aim_low_2);
        /////Timeout
        set_shooter_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),aim_low_2);

        /////Aim Low 1
        aim_low_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::turret_state_controller->maintain_state(Shooter::auto_aim);
        }));
        aim_low_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        aim_low_2->add_transition(std::function<bool()>([](){
            return Shooter::Flywheel::pid_controller->is_in_range(10) && Shooter::vision->aiming_complete();
        }),shoot_low_2);
        /////Timeout
        aim_low_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),shoot_low_2);

        /////Shoot High 1
        shoot_low_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 5000;
            Shooter::shooter_state_controller->set_state(Shooter::fire);
        }));
        shoot_low_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));

        shoot_low_2->add_transition(std::function<bool()>([](){
            return Shooter::shooter_state_controller->get_current_state() == Shooter::spin_up && Shooter::Loader::dead_band->is_in_range(Shooter::LOADER_TOLERANCE);
        }),wind_down_2);
        /////Timeout
        shoot_low_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),wind_down_2);

        /////Wind down 1
        wind_down_2->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            auto_controller->metadata().timeout = pros::millis() + 1000;
        }));
        wind_down_2->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Shooter::shooter_state_controller->maintain_state(Shooter::rest);
            Shooter::turret_state_controller->maintain_state(Shooter::set_point);
            Shooter::turret_state_controller->metadata().hood_set_point = 0;
            Shooter::turret_state_controller->metadata().turret_set_point = 0;
        }));

        /////Timeout
        wind_down_2->add_transition(std::function<bool()>([](){
            return pros::millis() > auto_controller->metadata().timeout;
        }),end);

        /////END
        end->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            
        }));
        end->set_on_state_exit(std::function<void(state*)>([](state* next_state){

        }));




















        auto_controller->add_state(zero);
        auto_controller->add_state(grab_tilted_cap);
        auto_controller->add_state(move_tilted_cap);
        auto_controller->add_state(prime_tilted_cap);
        auto_controller->add_state(score_tilted_cap);
        auto_controller->add_state(succ_blue_cap);
        auto_controller->add_state(slide_to_the_right);
        auto_controller->add_state(cha_cha_real_smooth);
        auto_controller->add_state(end);

        auto_controller->set_state(zero);
    }

    void destroy() {
        
    }
}