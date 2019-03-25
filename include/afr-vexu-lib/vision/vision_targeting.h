#ifndef VEX_U_2018_V5_VISION_TARGETING_H
#define VEX_U_2018_V5_VISION_TARGETING_H

#include <list>

#include "afr-lib/commandable.h"
#include "afr-lib/nameable.h"
#include "afr-lib/defines.h"
#include "afr-vexu-lib/comms/serial_manager.h"

namespace AFR::VexU::Vision {
    
    struct encoder_tuple {
        double azimuth;
        double altitude;
        
        encoder_tuple(double az, double alt) : azimuth(az), altitude(alt) {}
    };
    
    struct rectangle {
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
    };
    
    class vision_targeting : public commandable<encoder_tuple>, public virtual nameable {
        struct scored_rect {
            rectangle rect;
            int validity;
            bool targeting;
        };
        
        static constexpr uint8_t FRAME_NUM_ADDR = 1;
        static constexpr int64_t UPDATE_RATE = 10;
        static constexpr int CAM_WIDTH = 720;
        static constexpr int CAM_HEIGHT = 540;
        static constexpr double X_PIX_PER_TICK = 0.5091820;
        static constexpr double Y_PIX_PER_TICK = 0.7202381;
        static constexpr int RECT_IN_RANGE_X = 30;
        static constexpr int RECT_IN_RANGE_Y = 30;
        static constexpr int RECT_IN_RANGE_WIDTH = 10;
        static constexpr int RECT_IN_RANGE_HEIGHT = 10;
        static constexpr int RECURRENCE_BONUS = 30;
        static constexpr int VALIDITY_THRESH = 100;
        static constexpr int X_CENTER_WEIGHT = 10;
        static constexpr int Y_CENTER_WEIGHT = 1;
        static constexpr int AREA_WEIGHT = 1;
        static constexpr int TARGETED_WEIGHT = 500;
        static constexpr int X_CENTER = 360;
        static constexpr int Y_CENTER = 270;
        
        std::list<scored_rect>  target_rects;
        encoder_tuple last_enc_vals;
        rectangle current_target_rect;
        bool has_target_rect_;
        
        void set_value_private(encoder_tuple enc_vals, double delta_seconds) override;
        
    public:
        vision_targeting(const std::string& name);
        
        rectangle get_target_rect();    
        bool has_target_rect();
        static encoder_tuple get_encoder_setpoints(const rectangle& rect);
    }
}

#endif //VEX_U_2018_V5_VISION_TARGETING_H