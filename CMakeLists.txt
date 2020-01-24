cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(pi-decay)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

add_executable(pi-decay main.cc)
target_link_libraries(pi-decay ${Geant4_LIBRARIES})
