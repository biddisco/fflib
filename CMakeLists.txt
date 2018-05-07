PROJECT(FFLIB)
cmake_minimum_required(VERSION 3.2)

#--------------------------------------------------
# Setup Output directories
#--------------------------------------------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables."
)
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries"
)
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all static libraries."
)

#--------------------------------------------------
# set path for cmake searching
#--------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#--------------------------------------------------
# find portals
#--------------------------------------------------
find_package(Portals REQUIRED)
include_directories(
  ${PORTALS_INCLUDE_DIR}
)

#--------------------------------------------------
# Define source files
#--------------------------------------------------
set(FFLIB_SRCS
  src/ff.c
  src/ff_container.c
  src/ff_recv.c
  src/ff_send.c
  src/ff_computation.c
  src/ff_op.c
  src/ff_schedule.c
  src/ff_storage.c
  #
  src/colls/ff_activation.c
  src/colls/ff_allreduce.c
  src/colls/ff_barrier.c
  src/colls/ff_gather.c
  src/colls/ff_scatter.c
  src/colls/ff_allgather.c
  src/colls/ff_alltoall.c
  src/colls/ff_bcast.c
  src/colls/ff_reduce.c
  src/colls/ff_solo_allreduce.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#--------------------------------------------------
# Link fflib library
#--------------------------------------------------
add_library(fflib SHARED ${FFLIB_SRCS})
target_link_libraries(fflib ${PORTALS_LIBRARIES})

#--------------------------------------------------
# Tests
#--------------------------------------------------
add_subdirectory(tests)
