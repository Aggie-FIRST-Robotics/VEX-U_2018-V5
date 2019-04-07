#ifndef VEX_U_2018_V5_VISION_TARGETING_H
#define VEX_U_2018_V5_VISION_TARGETING_H

#include <list>
#include <iostream>


#include "afr-lib/commandable.h"
#include "afr-lib/nameable.h"
#include "afr-lib/defines.h"
#include "afr-lib/state.h"
#include "afr-vexu-lib/comms/serial_manager.h"

namespace AFR::VexU::Vision {
    
    struct encoder_tuple {
        double azimuth;
        double altitude;
        encoder_tuple() : azimuth(0), altitude(0) {}
        encoder_tuple(double az, double alt) : azimuth(az), altitude(alt) {}
    };
    
    struct rectangle {
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
        rectangle() : x(0), y(0), width(0), height(0) {}
    };
    
    class vision_targeting : public commandable<encoder_tuple>, public virtual nameable {
        struct scored_rect {
            rectangle rect;
            int validity;
            bool targeting;
            
            scored_rect() : rect(), validity(0), targeting(false) {}
        };
        
        static constexpr uint8_t FRAME_NUM_ADDR = 1;
        static constexpr int64_t UPDATE_RATE = 10;
        static constexpr int CAM_WIDTH = 720;
        static constexpr int CAM_HEIGHT = 540;
        static constexpr double X_PIX_PER_TICK = -1.8;
        static constexpr double Y_PIX_PER_TICK = -1.6;
        static constexpr int RECT_IN_RANGE_X = 30;
        static constexpr int RECT_IN_RANGE_Y = 30;
        static constexpr int RECT_IN_RANGE_WIDTH = 10;
        static constexpr int RECT_IN_RANGE_HEIGHT = 10;
        static constexpr int RECURRENCE_BONUS = 50;
        static constexpr int VALIDITY_MAX = 200;
        static constexpr int VALIDITY_THRESH = 100;
        static constexpr int X_CENTER_WEIGHT = 10;
        static constexpr int Y_CENTER_WEIGHT = 10;
        static constexpr int AREA_WEIGHT = 1;
        static constexpr int TARGETED_WEIGHT = 10000;
        static constexpr int X_CENTER = 275;
        static constexpr int Y_CENTER = 160;
        static constexpr int ACCUM_ERROR = 0;
        
        std::list<scored_rect>  target_rects;
        encoder_tuple last_enc_vals;
        encoder_tuple encoder_setpoints;
        rectangle current_target_rect;
        bool has_target_rect_;
        double x_accum;
        double y_accum;
        
        void set_value_private(encoder_tuple enc_vals, double delta_seconds) override;
        bool rect_in_range(const rectangle& r1, const rectangle& r2);
        
    public:
        vision_targeting(const std::string& name);
        
        rectangle get_target_rect();    
        bool has_target_rect();
        encoder_tuple get_encoder_setpoints();
        void set_encoder_setpoints(const encoder_tuple& new_setpoints);
        void purge_target_list();
    };
}

#endif //VEX_U_2018_V5_VISION_TARGETING_H