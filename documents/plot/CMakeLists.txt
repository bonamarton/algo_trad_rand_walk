cmake_minimum_required (VERSION 2.8.11)

project(plots LANGUAGES NONE)

find_package(Gnuplot REQUIRED)

######################################################################################
# MAKE GMB ASSET PRICES PLOT

set(gbmDataPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")
set(gbmScriptPath "${PROJECT_SOURCE_DIR}/GBM_data_plot_script")
set(gbmPlotPath "${PROJECT_SOURCE_DIR}/GBM_data_plot")

file(GLOB gbmDatasets "${gbmDataPath}" "${gbmDataPath}/*_const_sigma*.txt")
set(gbmOutFile "${gbmDataPath}/const_sigma.png")

message("................${gbmDatasets}")

add_custom_command( OUTPUT ${gbmOutFile}
                    COMMAND ${GNUPLOT_EXECUTABLE} ${gbmScriptPath}/const_sigma.plt
                    DEPENDS ${gbmScriptPath}/const_sigma.plt gbmDatasets
                    COMMENT "...................Generating plot"
                    WORKING_DIRECTORY ${gbmDataPath})

add_custom_target(gbm_sigma_plot ALL DEPENDS ${gbmOutFile})

set(cmake_src_d "${CMAKE_SOURCE_DIR}")
add_custom_command( TARGET gbm_sigma_plot
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND}
                        -Dcmake_src_d=${cmake_src_d}
                        -P ${CMAKE_SOURCE_DIR}/documents/cmake/move.cmake)

######################################################################################