include(src/rev/cap/arm/CMakeLists.txt)
include(src/rev/cap/wrist/CMakeLists.txt)

set(
        rev-cap-src
        ${rev-arm-src}
        ${rev-wrist-src}
)

set(
        rev-cap-test-src
        ${rev-arm-test-src}
        ${rev-wrist-test-src}
)

set(
        rev-cap-V5-src
        ${rev-arm-V5-src}
        ${rev-wrist-V5-src}
        src/rev/cap/cap.cpp
)
