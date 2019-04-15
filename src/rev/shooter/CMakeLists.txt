include(src/rev/shooter/altitude/CMakeLists.txt)
include(src/rev/shooter/puncher/CMakeLists.txt)
include(src/rev/shooter/rollers/CMakeLists.txt)

set(
        rev-shooter-src
	
	${rev-rollers-src}
        ${rev-altitude-src}
        ${rev-puncher-src}
)

set(
        rev-shooter-test-src
	${rev-rollers-test-src}
        ${rev-altitude-test-src}
        ${rev-puncher-test-src}
)

set(
        rev-shooter-V5-src
	${rev-rollers-V5-src}
        ${rev-altitude-V5-src}
        ${rev-puncher-V5-src}
        src/rev/shooter/shooter.cpp
)
