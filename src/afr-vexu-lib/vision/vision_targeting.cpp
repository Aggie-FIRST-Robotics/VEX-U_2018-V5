#include "afr-vexu-lib/vision/vision_targeting.h"

namespace AFR::VexU::Vision {
    
    vision_targeting::vision_targeting(const std::string& name) :
        nameable(name), 
        commandable<encoder_tuple>(UPDATE_RATE, name),
        last_enc_vals(0,0),
        has_target_rect_(false)
        {}
        
    void vision_targeting::set_value_private(encoder_tuple enc_vals, double delta_seconds) {
        if(scheduled::is_enabled()) {
            for(auto it = target_rects.begin(); it != target_rects.end(); ++it) {
                it->rect.x += X_PIX_PER_TICK*(enc_vals.azimuth-last_enc_vals.azimuth);
                it->rect.y += Y_PIX_PER_TICK*(enc_vals.altitude-last_enc_vals.altitude);
                
                if(it->rect.x+it->rect.width < 0 || it->rect.x >= CAM_WIDTH || 
                   it->rect.y+it->rect.height < 0 || it->rect.x >= CAM_HEIGHT) {
                    target_rects.erase(it);
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
            if(rect_num > 0 && serial->odroid_table.card(FRAME_NUM_ADDR) <= UPDATE_RATE) {
                for(uint8_t i = 0; i < rect_num; i++) {
                    rectangle serial_rect;
                    serial_rect.x = serial->odroid_table.read(2+4*i);
                    serial_rect.y = serial->odroid_table.read(3+4*i);
                    serial_rect.width = serial->odroid_table.read(4+4*i);
                    serial_rect.height = serial->odroid_table.read(5+4*i);
                    
                    bool rect_found = false;
                    for(auto rect : target_rects) {
                        if(abs<int16_t>(rect.rect.x - serial_rect.x) < RECT_IN_RANGE_X &&
                           abs<int16_t>(rect.rect.y - serial_rect.y) < RECT_IN_RANGE_Y &&
                           abs<int16_t>(rect.rect.width - serial_rect.width) < RECT_IN_RANGE_WIDTH &&
                           abs<int16_t>(rect.rect.height - serial_rect.height) < RECT_IN_RANGE_HEIGHT) {
                            rect.rect.x = serial_rect.x;
                            rect.rect.y = serial_rect.y;
                            rect.rect.width = serial_rect.width;
                            rect.rect.height = serial_rect.height;
                            rect.validity += RECURRENCE_BONUS;
                            rect_found = true;
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
                    }
                }
            }
            
            auto max_score_it = target_rects.end();
            int max_score = 0;
            for(auto it = target_rects.begin(); it != target_rects.end(); ++it) {
                it->validity--;
                
                if(it->validity < 0) {
                    target_rects.erase(it);
                    continue;
                }
                
                if(it->validity > VALIDITY_THRESH) {
                    int score = X_CENTER_WEIGHT*(X_CENTER-abs<int16_t>(X_CENTER-it->rect.x)) +
                                Y_CENTER_WEIGHT*(Y_CENTER-abs<int16_t>(Y_CENTER-it->rect.y)) +
                                AREA_WEIGHT*it->rect.width*it->rect.height +
                                it->targeting ? TARGETED_WEIGHT : 0;
                    if(score > max_score) {
                        max_score = score;
                        max_score_it = it;
                    }
                    it->targeting = false;
                }
            }
            if(max_score_it != target_rects.end()) {
                current_target_rect = max_score_it->rect;
                max_score_it->targeting = true;
                has_target_rect_ = true;
            }
            else {
                has_target_rect_ = false;
            }
            last_enc_vals = enc_vals;
        }
    }
    
    rectangle vision_targeting::get_target_rect() {
        return current_target_rect;
    }
    
    bool vision_targeting::has_target_rect() {
        return has_target_rect_;
    }
    
    encoder_tuple vision_targeting::get_encoder_setpoints(const rectangle& rect) {
        int16_t target_x = 360;
        int16_t target_y = 270;
        encoder_tuple retval;
        retval.azimuth = (target_x-(rect.x + rect.width/2))/X_PIX_PER_TICK;
        retval.altitude = (target_y-(rect.y + rect.height/2))/Y_PIX_PER_TICK;
        return retval;
    }
    
    void vision_targeting::purge_target_list() {
        target_rects.clear();
    }
}