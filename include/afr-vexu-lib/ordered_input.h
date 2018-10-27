//
// Created by Buzzec on 10/26/2018.
//

#ifndef VEX_U_2018_V5_ORDERED_INPUT_H
#define VEX_U_2018_V5_ORDERED_INPUT_H

#include "readable.h"
#include <string>

namespace AFR::VexU{
    template<typename T>
    class ordered_input : public readable<T>{
    public:
        ordered_input(int order, readable<T> input);
        std::string get_order();
        readable<T> get_input();

    private:
        int order;
        readable<T> input;
    };

    template<typename T>
    ordered_input<T>::ordered_input(int order, readable<T> input)
            : order(order), input(input){}

    template<typename T>
    std::string ordered_input<T>::get_order(){
        return order;
    }

    template<typename T>
    readable<T> ordered_input<T>::get_input(){
        return input;
    }

}

#endif //VEX_U_2018_V5_ORDERED_INPUT_H
