#include "afr-vexu-lib/vision/vision_targeting.h"

namespace AFR::VexU::Vision {
    
    vision_targeting::vision_targeting(const std::string& name) :
        nameable(name), 
        commandable<encoder_tuple>(UPDATE_RATE, name),
        has_target_rect_(false),
        x_accum(0),
        y_accum(0),
        aim_count(0)
        {}
        
    void vision_targeting::set_value_private(encoder_tuple enc_vals, double delta_seconds) {
        if(scheduled::is_enabled()) {
           // std::cout << "Begin update function" << std::endl;
            std::cout << "Encoder vals: " << enc_vals.azimuth << " " << enc_vals.altitude << std::endl;
            for(auto it = target_rects.begin(); it != target_rects.end(); ++it) {
                it->rect.x += X_PIX_PER_TICK*(enc_vals.azimuth-last_enc_vals.azimuth);
                it->rect.y += Y_PIX_PER_TICK*(enc_vals.altitude-last_enc_vals.altitude);

                // std::cout << "new rect coords: " << it->rect.x << " " << it->rect.y << std::endl;
                
                if(it->rect.x+it->rect.width < 0 || it->rect.x >= CAM_WIDTH || 
                   it->rect.y+it->rect.height < 0 || it->rect.y >= CAM_HEIGHT) {
                    // std::cout << "Rect out of range, erasing" << std::endl;
                    target_rects.erase(it++);
                    continue;
                }
                
                bool similar = false;
                
                for(auto it2 = target_rects.begin(); it2 != target_rects.end(); ++it2) {
                    if(it != it2 && it->validity <= it2->validity && rect_in_range(it->rect, it2->rect)) {
                        similar = true;
                        break;
                    }
                }
                
                if(similar) {
                    // std::cout << "Duplicate rect, erasing" << std::endl;
                    target_rects.erase(it++);
                    continue;
                }
                
                if(it->rect.x < 0) {
                    it->rect.width += it->rect.x;
                    it->rect.x = 0;
                }
                if(it->rect.y < 0) {
                    it->rect.height += it->rect.y;
                    it->rect.y = 0;
                }
                if(it->rect.x + it->rect.width >= CAM_WIDTH) {
                    it->rect.width = CAM_WIDTH - it->rect.x;
                }
                if(it->rect.y + it->rect.height >= CAM_HEIGHT) {
                    it->rect.height = CAM_HEIGHT - it->rect.y;
                }
            }
            
            short rect_num = serial->odroid_table.read(FRAME_NUM_ADDR);
            // std::cout << "Num serial rect: " << rect_num << std::endl;
            // std::cout << "Age of the rectangle: " << pros:: millis() - serial->odroid_table.card(FRAME_NUM_ADDR) << std::endl;
            if(rect_num > 0 && pros::millis() - serial->odroid_table.card(FRAME_NUM_ADDR) <= UPDATE_RATE) {
                for(uint8_t i = 0; i < rect_num; i++) {
                    rectangle serial_rect;
                    serial_rect.x = serial->odroid_table.read(2+4*i);
                    serial_rect.y = serial->odroid_table.read(3+4*i);
                    serial_rect.width = serial->odroid_table.read(4+4*i);
                    serial_rect.height = serial->odroid_table.read(5+4*i);
                    // std::cout << "Serial rect: " << serial_rect.x << " "<< serial_rect.y << " " << serial_rect.width << " " << serial_rect.height << std::endl;
                    bool rect_found = false;
                    for(auto it = target_rects.begin(); it != target_rects.end(); ++it) {
                        if(rect_in_range(it->rect, serial_rect)) {
                            it->rect.x = serial_rect.x;
                            it->rect.y = serial_rect.y;
                            it->rect.width = serial_rect.width;
                            it->rect.height = serial_rect.height;
                            it->validity += RECURRENCE_BONUS;
                            if(it->validity > VALIDITY_MAX) {
                                it->validity = VALIDITY_MAX;
                            }
                            rect_found = true;
                            // std::cout << "Rect found in list, score: " << it->validity << std::endl;
                            break;
                        }
                    }
                    if(!rect_found) {
                        scored_rect new_rect;
                        new_rect.rect.x = serial_rect.x;
                        new_rect.rect.y = serial_rect.y;
                        new_rect.rect.width = serial_rect.width;
                        new_rect.rect.height = serial_rect.height;
                        new_rect.validity = RECURRENCE_BONUS;
                        new_rect.targeting = false;
                        target_rects.push_back(new_rect);
                        // std::cout << "Rect not found in list" << std::endl;
                    }
                }
            }
            
            scored_rect* max_score_ptr = nullptr;
            int max_score = 0;
            for(auto it = target_rects.begin(); it != target_rects.end(); ++it) {
               // std::cout << "Validity:  " << it->validity << "\t";
                it->validity--;

                if(it->validity < 0) {
                   // std::cout << "erased" << std::endl;
                    target_rects.erase(it++);
                    continue;
                }

                // std::cout << " passed \t";

                if(it->validity > VALIDITY_THRESH) {
                    int x_score = X_CENTER_WEIGHT*(X_CENTER-abs<int16_t>(X_CENTER-it->rect.x));
                    int y_score = Y_CENTER_WEIGHT*(Y_CENTER-abs<int16_t>(Y_CENTER-it->rect.y));
                    int area_score = AREA_WEIGHT*it->rect.width*it->rect.height;
                    int targeting_score = (it->targeting ? TARGETED_WEIGHT : 0);
                    int score = x_score + y_score + area_score;
                    // std::cout << " passed. Score: " << x_score << " " << y_score << " " 
                       // << area_score << " " << targeting_score << std::endl;
                    if(score > max_score) {
                        max_score = score;
                        max_score_ptr = &(*it);
                    }
                    it->targeting = false;
                }
                else {
                    std::cout << std::endl;

                }
            }
            if(max_score_ptr != nullptr) {
                std::cout << "Target rect found" << std::endl;
                current_target_rect = max_score_ptr->rect;
                max_score_ptr->targeting = true;
                has_target_rect_ = true;

                int16_t target_x = get_azimuth_target(enc_vals);
                int16_t target_y = get_altitude_target(enc_vals);

                if(abs(target_x-enc_vals.azimuth) <  AIM_COMPLETE_TOLERANCE && abs(target_y-enc_vals.altitude) <  AIM_COMPLETE_TOLERANCE) {
                    aim_count++;
                }
                else {
                    aim_count = 0;
                }

                int16_t x_err = target_x-(current_target_rect.x + current_target_rect.width/2);
                int16_t y_err = target_y-(current_target_rect.y + current_target_rect.height/2);
                x_accum += x_err*ACCUM_ERROR*delta_seconds;
                y_accum += y_err*ACCUM_ERROR*delta_seconds;
                encoder_setpoints.azimuth = enc_vals.azimuth + (x_err/X_PIX_PER_TICK) + x_accum;
                encoder_setpoints.altitude = enc_vals.altitude + (y_err/Y_PIX_PER_TICK) + y_accum;
            }
            else {
                //std::cout << "No target rect found" << std::endl;
                has_target_rect_ = false;
                aim_count = 0;
            }
            last_enc_vals = enc_vals;
        }

        encoder_tuple sample = get_encoder_setpoints();
        std::cout << "Encoder sample: " << sample.azimuth << " " << sample.altitude << std::endl;
        //std::cout << "End update function" << std::endl;
    }
    
    rectangle vision_targeting::get_target_rect() {
        return current_target_rect;
    }
    
    bool vision_targeting::has_target_rect() {
        return has_target_rect_;
    }

    void vision_targeting::set_encoder_setpoints(const encoder_tuple& new_setpoints) {
        encoder_setpoints.altitude = new_setpoints.altitude;
        encoder_setpoints.azimuth = new_setpoints.azimuth;
    }
    
    encoder_tuple vision_targeting::get_encoder_setpoints() {
        return encoder_setpoints;
    }
    
    void vision_targeting::purge_target_list() {
        target_rects.clear();
        x_accum = 0;
        y_accum = 0;
        aim_count = 0;
    }
    
    bool vision_targeting::rect_in_range(const rectangle& r1, const rectangle& r2) {
        return abs<int16_t>(r1.x - r2.x) < RECT_IN_RANGE_X &&
            abs<int16_t>(r1.y - r2.y) < RECT_IN_RANGE_Y &&
            abs<int16_t>(r1.width - r2.width) < RECT_IN_RANGE_WIDTH &&
            abs<int16_t>(r1.height - r2.height) < RECT_IN_RANGE_HEIGHT;
    }

    bool vision_targeting::aiming_complete() {
        return aim_count >  AIM_COMPLETE_COUNT;
    }

    double vision_targeting::get_azimuth_target(encoder_tuple enc_vals) {
        return 275;
    }

    double vision_targeting::get_altitude_target(encoder_tuple enc_vals) {
        return 160 + 2*(140-current_target_rect.height);
    }
}