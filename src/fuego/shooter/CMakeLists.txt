include(src/fuego/shooter/turret/CMakeLists.txt)
include(src/fuego/shooter/hood/CMakeLists.txt)
include(src/fuego/shooter/flywheel/CMakeLists.txt)
include(src/fuego/shooter/loader/CMakeLists.txt)
include(src/fuego/shooter/CMakeLists.txt)

set(
        fuego-shooter-src

        ${fuego-turret-src}
        ${fuego-hood-src}
        ${fuego-flwheel-src}
        ${fuego-loader-src}
)

set(
        fuego-shooter-test-src
        ${fuego-hood-test-src}
        ${fuego-turret-test-src}
        ${fuego-flywheel-test-src}
        ${fuego-loader-test-src}
)

set(
        fuego-shooter-V5-src
        ${fuego-hood-V5-src}
        ${fuego-turret-V5-src}
        ${fuego-flywheel-V5-src}
        ${fuego-loader-V5-src}
        src/fuego/shooter/shooter.cpp
)
