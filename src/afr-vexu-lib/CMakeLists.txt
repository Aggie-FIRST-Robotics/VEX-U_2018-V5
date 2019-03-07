include(src/afr-vexu-lib/base-commandable/CMakeLists.txt)
include(src/afr-vexu-lib/base-readable/CMakeLists.txt)
include(src/afr-vexu-lib/base-action/CMakeLists.txt)
include(src/afr-vexu-lib/comms/CMakeLists.txt)

set(
        afr-vexu-lib-src
        ${base-commandable-src}
        ${base-readable-src}
        ${base-action-src}
        ${comms-src}
)

set(
        afr-vexu-lib-test-src
        ${base-commandable-test-src}
        ${base-readable-test-src}
        ${base-action-stest-src}
        ${comms-test-src}
)

set(
        afr-vexu-lib-V5-src
        ${base-commandable-V5-src}
        ${base-readable-V5-src}
        ${base-action-V5-src}
        ${comms-V5-src}
)
