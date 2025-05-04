#
# MbedCE I2C examples
#
cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19...3.22)

#### Initialize Mbed OS build system. ####
######################################################################################################
### Block of including .json5 files. Files of this block must be included before the app.cmake

#[[ Set path of mbed_app.json (necessary at all times) ]]
set(MBED_APP_JSON_PATH mbed_app.json5)

###--------------------------------------------------------------------------------------------------- 
#[[ This part is dedicated for custom targets only! The settings below activate targets from
    custom_targets.json5 and upload method config. If custom targets are not used the lines below should be commented. ]]

#[[ Here set path for custom_targets.json5 (this is our default) ]]
#set(CUSTOM_TARGETS_JSON_PATH custom_targets/custom_targets.json5)

#[[ Here you can set path for custom upload config .cmake (optional example) ]]
#set(CUSTOM_UPLOAD_CFG_PATH ${CMAKE_SOURCE_DIR}/${MBED_TARGET}/${MBED_TARGET}.cmake)

#[[ Note: For custom target you need also an upload method and we have few options how you can do that
    - use the variable CUSTOM_UPLOAD_CFG_PATH above to set the location of your config file
    - use the default expected path for custom targets upload method config file:
      MY_PROJECT/custom_targets/upload_method_cfg
    - of course you can set upload method parameters directly via cmake in this file
   For more visit https://github.com/mbed-ce/mbed-os/wiki/Upload-Methods ]]
   
### End of block
######################################################################################################

### Include Mbed toolchain setup file
include(mbed-os/tools/cmake/mbed_toolchain_setup.cmake)

### Set up your project.
# The project name will be made available in the ${PROJECT_NAME} variable.
# If you like, you can specify a version here, which CMake will make available in the ${PROJECT_VERSION} variable.

project(I2C_Scanner
        # VERSION 1.0.0
        LANGUAGES C CXX ASM)
project(I2C_Master
        # VERSION 1.0.0
        LANGUAGES C CXX ASM)

project(I2C_Master_single_byte
        # VERSION 1.0.0
        LANGUAGES C CXX ASM)

project(I2C_Master_transfer
        # VERSION 1.0.0
        LANGUAGES C CXX ASM)

project(I2C_Slave
        # VERSION 1.0.0
        LANGUAGES C CXX ASM)

### Include Mbed project setup file
include(mbed_project_setup)

######################################################################################################
### Block of including project folders

#[[ If using a custom target, the subdirectory containing the custom target must be included before 
    the mbed-os subdir, otherwise the next line should be commented]]
#add_subdirectory(custom_targets)

###--------------------------------------------------------------------------------------------------
## Add mbed-os subdirectory (necessary everytime)
add_subdirectory(mbed-os)

###--------------------------------------------------------------------------------------------------
## Add another subdirectory, for example subdirectory of a library (if needed)
#add_subdirectory(mylib)

### End of block
######################################################################################################

### add executable (necessary everytime)
# This will compile an elf file named the same as the project with the given source files.
add_executable(I2C_Scanner I2C_bus_scanner.cpp)
add_executable(I2C_Master I2C_Master_ex.cpp)
add_executable(I2C_Master_single_byte I2C_Master_singlebyte_ex.cpp)
add_executable(I2C_Master_transfer I2C_Master_transfer_ex.cpp)
add_executable(I2C_Slave I2C_Slave_ex.cpp)


######################################################################################################
### Link libraries block
#[[For more about this configuration visit wiki page MbedOS-configuration
https://github.com/mbed-ce/mbed-os/wiki/MbedOS-configuration#configuration-via-cmake-files]]

# Link Mbed OS core library. This is called mbed-os when using the Mbed RTOS, and mbed-baremetal when using
# the bare metal version. This if statement checks to see which is in use and links it.
# Important: The mbed-os and mbed-baremetal libraries are object libraries, so they should ONLY be
# linked to executables, not to other libraries. Libraries should link to `mbed-core-flags` instead.
if("MBED_CONF_TARGET_APPLICATION_PROFILE=bare-metal" IN_LIST MBED_CONFIG_DEFINITIONS)
    target_link_libraries(I2C_Scanner mbed-baremetal)
    target_link_libraries(I2C_Master mbed-baremetal)
    target_link_libraries(I2C_Master_single_byte mbed-baremetal)
    target_link_libraries(I2C_Master_transfer mbed-baremetal)
    target_link_libraries(I2C_Slave mbed-baremetal)
else()
    target_link_libraries(I2C_Scanner mbed-os)
    target_link_libraries(I2C_Master mbed-os)
    target_link_libraries(I2C_Master_single_byte mbed-os)
    target_link_libraries(I2C_Master_transfer mbed-os)
    target_link_libraries(I2C_Slave mbed-os)
endif()

### link user library (if needed)
#target_link_libraries(${PROJECT_NAME} mylib)

# This generates build rules to generate bin/hex files, and to flash the code if you have configured an
# upload method.
mbed_set_post_build(I2C_Scanner)
mbed_set_post_build(I2C_Master)
mbed_set_post_build(I2C_Master_single_byte)
mbed_set_post_build(I2C_Master_transfer)
mbed_set_post_build(I2C_Slave)
#[[ Note: if you wish to use a custom linker script instead of the default Mbed one for
   your target, you can do that with mbed_set_post_build(${PROJECT_NAME} path/to/linker_script.ld) ]]

### End of block
######################################################################################################