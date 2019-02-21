include(src/robot2/ball/CMakeLists.txt)

set(
        robot2-src
        ${robot2-ball-src}
)

set(
        robot2-test-src
        ${robot2-ball-test-src}
)

set(
        robot2-V5-src
        ${robot2-ball-V5-src}

        src/robot2/robot.cpp
)
