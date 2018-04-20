
cmake_minimum_required(VERSION 3.11.0)

project(stoch LANGUAGES CXX)

add_executable(gbm geo_brown_motion.cpp)

set_property(TARGET gbm PROPERTY CXX_STANDARD 11)
set_property(TARGET gbm PROPERTY CXX_STANDARD_REQUIRED ON)

######################################################################################
# MAKE GMB ASSET PRICES FROM CONFIG FILES WITH BUILT EXECUTABLE

set(wantGenerateFiles TRUE) # TRUE or FALSE

if(wantGenerateFiles)

    set(gbmInPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion_config")
    set(gbmOutPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")
    set(sigma_plot_output "${CMAKE_SOURCE_DIR}/documents/plot/GBM_data_plot/const_sigma.png")

    # Find all the input files
    file(GLOB gbmInNames RELATIVE "${gbmInPath}" "${gbmInPath}/*_config.txt")

    foreach(gbmIn ${gbmInNames})

        # Generate input file name
        set(gbm_in_file "${gbmInPath}/${gbmIn}")

        # Generate output file name
        string(REGEX REPLACE "_config" "" gbmOut "${gbmIn}")
        set(gbm_out_file "${gbmOutPath}/${gbmOut}")
        
        # Custom command to do the processing
        add_custom_command( OUTPUT ${gbm_out_file}
                            COMMAND gbm < ${gbm_in_file}
                            COMMAND ${CMAKE_COMMAND}
                                -DFile=${sigma_plot_output}
                                -P ${CMAKE_SOURCE_DIR}/documents/cmake/remove_file.cmake
                            DEPENDS ${gbm_in_file} gbm
                            COMMENT "\n\n ........ Process file: ${gbmIn} .......\n"
                            WORKING_DIRECTORY ${gbmOutPath})
        
        # Collecting output files
        set(gbmOutFiles ${gbmOutFiles} "${gbm_out_file}")

    endforeach(gbmIn)

    add_custom_target(gbmDatasets ALL DEPENDS ${gbmOutFiles})

endif(wantGenerateFiles)

####################################################################################