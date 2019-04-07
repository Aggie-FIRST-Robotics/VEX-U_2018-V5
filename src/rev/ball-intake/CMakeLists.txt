include(src/rev/ball-intake/rollers/CMakeLists.txt)

message(WARNING Hello ${rev-ball-intake-V5-src})

set(
        rev-ball-intake-src
        ${rev-rollers-src}
)

set(
        rev-ball-intake-test-src
        ${rev-rolers-test-src}
)

set(
        rev-ball-intake-V5-src
        ${rev-rollers-V5-src}
        src/rev/ball-intake/ball_intake.cpp
)
