cmake_minimum_required(VERSION 2.8.11)

project(docu LANGUAGES NONE)

# Include useful macros
#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#include(UseLATEX)

#set(gbm_sigma_plot "${PROJECT_SOURCE_DIR}/plot/GBM_data_plot/const_sigma.png")
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Target that generates documentation
#add_latex_document(src/latex_template.tex
 #                  CONFIGURE src/latex_template.tex
  #                 TARGET_NAME doc
   #                INPUTS src/nyilatkozat.tex src/abeld.bst
    #               BIBFILES src/references.bib
    #               IMAGE_DIRS img
     #              DEPENDS src/latex_template.tex plot)
      #             #EXCLUDE_FROM_ALL)

# Process plot CMake script
add_subdirectory(plot)
