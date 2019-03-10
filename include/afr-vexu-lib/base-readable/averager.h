#ifndef VEX_U_2018_V5_AVERAGER_H
#define VEX_U_2018_V5_AVERAGER_H

#include "afr-lib/defines.h"
#include "afr-lib/operation.h"
#include <deque>

namespace AFR::VexU::BaseReadable{

    template <class T>
    class averager : public operation<T> {
        std::deque<T> values;
        size_t avg_length_;

    public:
        averager(std::function<T()> averaged_operation, size_t avg_length, const std::string& name)
            : nameable(name),
              operation<T>(averaged_operation, name),
              avg_length_(avg_length) {}
              
        double get_average_value() {
            values.push_back(operation<T>::get_function()());
            while(values.size() > avg_length_) {
                values.pop_front();
            }
            
            T sum = 0;
            for(T val : values) {
                sum += val;
            }
            
            return static_cast<double>(sum)/static_cast<double>(values.size());
        }
    };


}
#endif //VEX_U_2018_V5_AVERAGER_H
