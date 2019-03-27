
include(src/afr-vexu-lib/base-commandable/CMakeLists.txt)
include(src/afr-vexu-lib/base-readable/CMakeLists.txt)
include(src/afr-vexu-lib/comms/CMakeLists.txt)

set(
        afr-vexu-lib-src
        src/afr-vexu-lib/ports_list.cpp
        src/afr-vexu-lib/vision/vision_targeting.cpp
        ${base-commandable-src}
        ${base-readable-src}
        ${comms-src}
)

set(
        afr-vexu-lib-test-src
        src/afr-vexu-lib/ports_list.cpp
        src/afr-vexu-lib/vision/vision_targeting.cpp
        ${base-commandable-test-src}
        ${base-readable-test-src}
        ${comms-test-src}
)

set(
        afr-vexu-lib-V5-src
        src/afr-vexu-lib/ports_list.cpp
        src/afr-vexu-lib/vision/vision_targeting.cpp
        ${base-commandable-V5-src}
        ${base-readable-V5-src}
        ${comms-V5-src}
)
