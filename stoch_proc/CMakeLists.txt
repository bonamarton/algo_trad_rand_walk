
cmake_minimum_required(VERSION 3.11.0)

project(stoch LANGUAGES CXX)

add_executable(gbm geo_brown_motion.cpp)

set_property(TARGET gbm PROPERTY CXX_STANDARD 11)
set_property(TARGET gbm PROPERTY CXX_STANDARD_REQUIRED ON)

######################################################################################
# MAKE GMB ASSET PRICES FROM CONFIG FILES WITH BUILT EXECUTABLE

set(wantGenerateFiles TRUE) # TRUE or FALSE

    set(gbmInPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion_config")
    set(gbmOutPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")

    # Find all the input files
    file(GLOB gbmInNames RELATIVE "${gbmInPath}" "${gbmInPath}/*_config.txt")

    foreach(gbmIn ${gbmInNames})

        # Generate input file name
        set(gbm_in_file "${gbmInPath}/${gbmIn}")

        # Generate output file name
        string(REGEX REPLACE "_config" "" gbmOut "${gbmIn}")
        set(gbm_out_file "${gbmOutPath}/${gbmOut}")
        #if(wantGenerateFiles)
        # Custom command to do the processing
        add_custom_command( OUTPUT ${gbm_out_file}
                            COMMAND gbm < ${gbm_in_file}
                            DEPENDS ${gbm_in_file} gbm
                            COMMENT "\n\n ........ Process file: ${gbmIn} .......\n"
                            WORKING_DIRECTORY ${gbmOutPath})
        #endif(wantGenerateFiles)
        # Collecting outfut files
        set(gbmOutFiles ${gbmOutFiles} "${gbm_out_file}")

    endforeach(gbmIn)

add_custom_target(gbmDatasets DEPENDS ${gbmOutFiles})

####################################################################################