include(src/afr-vexu-lib/base-commandable/CMakeLists.txt)
include(src/afr-vexu-lib/base-readable/CMakeLists.txt)
include(src/afr-vexu-lib/base-action/CMakeLists.txt)

set(
        afr-vexu-lib-src
        ${base-commandable-src}
        ${base-readable-src}
        ${base-action-src}
        src/afr-vexu-lib/action.cpp
        src/afr-vexu-lib/commandable.cpp
        src/afr-vexu-lib/ports_list.cpp
        src/afr-vexu-lib/readable.cpp
        src/afr-vexu-lib/scheduled.cpp
        src/afr-vexu-lib/state.cpp
        src/afr-vexu-lib/state_controller.cpp
        src/afr-vexu-lib/subsystem_controller.cpp
)

set(
        afr-vexu-lib-test-src
        ${base-commandable-test-src}
        ${base-readable-test-src}
        ${base-action-stest-src}
)

set(
        afr-vexu-lib-V5-src
        ${base-commandable-V5-src}
        ${base-readable-V5-src}
        ${base-action-V5-src}
)
