include(src/fuego/ball-intake/CMakeLists.txt)
include(src/fuego/cap/CMakeLists.txt)
include(src/fuego/drive/CMakeLists.txt)
include(src/fuego/shooter/CMakeLists.txt)

set(
        fuego-src
        ${fuego-ball-intake-src}
        ${fuego-cap-src}
        ${fuego-drive-src}
        ${fuego-shooter-src}
)

set(
        fuego-test-src
        ${fuego-ball-intake-test-src}
        ${fuego-cap-test-src}
        ${fuego-drive-test-src}
        ${fuego-shooter-test-src}
)

set(
        fuego-V5-src
        ${fuego-ball-intake-V5-src}
        ${fuego-cap-V5-src}
        ${fuego-drive-V5-src}
        ${fuego-shooter-V5-src}

        src/fuego/fuego.cpp
        src/fuego/auto.cpp
)