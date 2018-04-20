
cmake_minimum_required(VERSION 3.11.0)

project(docu LANGUAGES NONE)

######################################################################################
# MAKE GMB ASSET PRICES PLOT

find_package(Gnuplot REQUIRED)

set(gbmDataPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")
set(gbmScriptPath "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot_script")
set(gbmPlotPath "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot")

set(sigmaPlotName "const_sigma.png")
set(sigmaScriptName "const_sigma.plt")

file(GLOB bmDatasets "${gbmDataPath}" "${gbmDataPath}/*_const_sigma*.txt")
set(sigma_plot_output "${gbmPlotPath}/${sigmaPlotName}")

add_custom_command( OUTPUT ${sigma_plot_output}
                    COMMAND  ${GNUPLOT_EXECUTABLE} "${gbmScriptPath}/${sigmaScriptName}"
                    DEPENDS "${gbmScriptPath}/${sigmaScriptName}" gbmDatasets
                    COMMENT "\n ........... Generatin plot ..........\n"
                    WORKING_DIRECTORY ${gbmDataPath})

add_custom_target(gbmSigmaPlot DEPENDS ${sigma_plot_output})

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
                    DEPENDS ${gbm_doc_tex_path} ${sigma_plot_output})

######################################################################################
