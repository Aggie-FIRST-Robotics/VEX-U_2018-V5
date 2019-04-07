include(src/rev/drive/base/CMakeLists.txt)
include(src/rev/drive/shifter/CMakeLists.txt)

message(WARNING Hello ${rev-drive-V5-src})

set(
        rev-drive-src
        ${rev-base-src}
        ${rev-shifter-src}
)

set(
        rev-drive-test-src
        ${rev-base-test-src}
        ${rev-shifter-test-src}
)

set(
        rev-drive-V5-src
        ${rev-base-V5-src}
        ${rev-shifter-V5-src}
        src/rev/drive/drive.cpp
)