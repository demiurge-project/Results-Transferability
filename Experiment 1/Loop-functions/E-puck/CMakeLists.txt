# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIRS})
link_directories(
	${CMAKE_BINARY_DIR}/src
    )

add_library(chocolate_aac_loopfunc SHARED ChocolateAACLoopFunc.h ChocolateAACLoopFunc.cpp)
target_link_libraries(chocolate_aac_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(foraging_loopfunc SHARED ForagingTwoSpotsLoopFunc.h ForagingTwoSpotsLoopFunc.cpp)
target_link_libraries(foraging_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(grid_exploration SHARED GridExplorationLoopFunc.h GridExplorationLoopFunc.cpp)
target_link_libraries(grid_exploration argos3plugin_${ARGOS_BUILD_FOR}_epuck)


