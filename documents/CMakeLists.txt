cmake_minimum_required(VERSION 2.8.11)

project(docu LANGUAGES NONE)

######################################################################################
# MAKE GMB ASSET PRICES PLOT

find_package(Gnuplot REQUIRED)

set(gbmDataPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")
set(gbmScriptPath "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot_script")
set(gbmPlotPath "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot")

file(GLOB gbmDatasets "${gbmDataPath}" "${gbmDataPath}/*_const_sigma*.txt")
set(gbmOutFile "${gbmDataPath}/const_sigma.png")

add_custom_command( OUTPUT ${gbmOutFile}
                    COMMAND ${GNUPLOT_EXECUTABLE} ${gbmScriptPath}/const_sigma.plt
                    DEPENDS ${gbmScriptPath}/const_sigma.plt
                    COMMENT "Generating plot"
                    WORKING_DIRECTORY ${gbmDataPath})

add_custom_target(gbm_sigma ALL DEPENDS ${gbmOutFile})

set(cmake_src_d "${CMAKE_SOURCE_DIR}")
add_custom_command( TARGET gbm_sigma
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND}
                        -Dcmake_src_d=${cmake_src_d}
                        -P ${CMAKE_SOURCE_DIR}/documents/cmake/move.cmake)

######################################################################################
# LATEX

# Include useful macros
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(UseLATEX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(gbm_sigma_plot "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot/const_sigma.png")
set(elte "${PROJECT_SOURCE_DIR}/img/elte.eps")
set(gbm_doc_tex_path "src/gbm_doc.tex")

set(LATEX_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/gbm_doc")

# Target that generates documentation
add_latex_document( ${gbm_doc_tex_path}
                    CONFIGURE ${gbm_doc_tex_path}
                    TARGET_NAME gbm_doc
                    DEPENDS ${gbm_doc_tex_path} ${gbmOutFile})

######################################################################################