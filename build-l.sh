#!/bin/sh
west build --build-dir build . --pristine --board orlangur_ezurio_nrf54l15/nrf54l15/cpuapp -- -DBOARD_ROOT=$(pwd) -DCONF_FILE=prj.conf --toolchain ${ZEPHYR_SDK_CMAKE_TOOLCHAIN_LLVM_PICO}
# west build --build-dir build . --pristine --board nrf54l15dk/nrf54l15/cpuapp -- -DCONF_FILE=prj.conf --toolchain ${ZEPHYR_SDK_CMAKE_TOOLCHAIN_LLVM_PICO}
