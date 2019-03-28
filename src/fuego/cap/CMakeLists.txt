include(src/fuego/cap/arm/CMakeLists.txt)
include(src/fuego/cap/elbow/CMakeLists.txt)
include(src/fuego/cap/wrist/CMakeLists.txt)

message(WARNING Hello ${fuego-arm-V5-src})

set(
        fuego-cap-src
        ${fuego-arm-src}
        ${fuego-elbow-src}
        ${fuego-wrist-src}
)

set(
        fuego-cap-test-src
        ${fuego-arm-test-src}
        ${fuego-elbow-test-src}
        ${fuego-wrist-test-src}
)

set(
        fuego-cap-V5-src
        ${fuego-arm-V5-src}
        ${fuego-elbow-V5-src}
        ${fuego-wrist-V5-src}
        src/fuego/cap/cap.cpp
)
