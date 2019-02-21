include(src/robot2/cap/CMakeLists.txt)

set(
        robot2-src
        ${robot2-cap-src}
)

set(
        robot2-test-src
        ${robot2-cap-test-src}
)

set(
        robot2-V5-src
        ${robot2-cap-V5-src}

        src/robot2/robot.cpp
)
