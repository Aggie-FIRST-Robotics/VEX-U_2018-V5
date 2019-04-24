include(src/rev/cap/CMakeLists.txt)
include(src/rev/drive/CMakeLists.txt)
include(src/rev/shooter/CMakeLists.txt)

set(
        rev-src
        ${rev-cap-src}
        ${rev-drive-src}
        ${rev-shooter-src}
)

set(
        rev-test-src
        ${rev-cap-test-src}
        ${rev-drive-test-src}
        ${rev-shooter-test-src}
)

set(
        rev-V5-src
        ${rev-cap-V5-src}
        ${rev-drive-V5-src}
        ${rev-shooter-V5-src}

        src/rev/rev.cpp
        src/rev/auto.cpp
)