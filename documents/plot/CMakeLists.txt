cmake_minimum_required (VERSION 2.8.11)

project(plots LANGUAGES NONE)

find_package(Gnuplot REQUIRED)

set(gbmOutPath "${CMAKE_SOURCE_DIR}/asset_prices/stoch_models/geo_brown_motion")
set(gbmInFile "${gbmOutPath}/gbm_const_sigma_1m_01.txt")

#set(gbmScriptPath "${PROJECT_SOURCE_DIR}/GBM_data_plot_script")
#set(gbmPlotPath "${PROJECT_SOURCE_DIR}/GBM_data_plot")
#file(GLOB gbmDatasets RELATIVE "${gbmOutPath}" "${gbmOutPath}/*_const_sigma*.txt")
#configure_file(${gbmScriptPath}/const_sigma.plt ${gbmOutPath}/const_sigma.plt COPYONLY)
#set(gbmOutFile "${gbmOutPath}/const_sigma.png")
set(GNUPLOT_EXECUTABLE_PATH "${GNUPLOT_EXECUTABLE}")
message(" ........... ${GNUPLOT_EXECUTABLE_PATH} .........")
message(" ........... ${GNUPLOT_EXECUTABLE} .........")

add_custom_command(COMMAND ${GNUPLOT_EXECUTABLE} ${PROJECT_SOURCE_DIR}/GBM_data_plot_script/const_sigma.plt
                   WORKING_DIRECTORY ${gbmOutPath}
                   OUTPUT ${gbmOutPath}/const_sigma.png
                   BYPRODUCTS ${gbmOutPath}/const_sigma.png
                   DEPENDS ${PROJECT_SOURCE_DIR}/GBM_data_plot_script/const_sigma.plt gbmInFile
                   COMMENT "...................Generating plot")

add_custom_target(gbm_sigma_plot DEPENDS ${gbmOutPath}/const_sigma.png)

#file(RENAME "${gbmOutPath}/const_sigma.png" "${gbmPlotPath}/const_sigma.png")
