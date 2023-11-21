# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIRS})
link_directories(
	${CMAKE_BINARY_DIR}/src
    )

add_library(giant_foraging_loopfunc SHARED GiantForagingTwoSpotsLoopFunc.h GiantForagingTwoSpotsLoopFunc.cpp)
target_link_libraries(giant_foraging_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(giant_grid_exploration_loopfunc SHARED GiantGridExplorationLoopFunc.h GiantGridExplorationLoopFunc.cpp ${LOOP_HEADERS} ${LOOP_SOURCES})
target_link_libraries(giant_grid_exploration_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)

add_library(chocolate_giant_aac_loopfunc SHARED ChocolateGiantAACLoopFunc.h ChocolateGiantAACLoopFunc.cpp ${LOOP_HEADERS} ${LOOP_SOURCES})
target_link_libraries(chocolate_giant_aac_loopfunc argos3plugin_${ARGOS_BUILD_FOR}_rvr)
