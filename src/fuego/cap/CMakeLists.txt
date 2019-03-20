include(src/fuego/cap/shoulder/CMakeLists.txt)
include(src/fuego/cap/elbow/CMakeLists.txt)
include(src/fuego/cap/wrist/CMakeLists.txt)
include(src/fuego/shooter/CMakeLists.txt)

set(
        fuego-cap-src

        ${fuego-shoulder-src}
        ${fuego-elbow-src}
        ${fuego-wrist-src}
)

set(
        fuego-cap-test-src
        ${fuego-shoulder-test-src}
        ${fuego-elbow-test-src}
        ${fuego-wrist-test-src}
)

set(
        fuego-cap-V5-src
        ${fuego-shoulder-V5-src}
        ${fuego-elbow-V5-src}
        ${fuego-wrist-V5-src}
        src/fuego/cap/cap.cpp
)
