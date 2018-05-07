#--------------------------------------------------
# find MPI
#--------------------------------------------------
find_package(MPI REQUIRED)

#--------------------------------------------------
# setup tests
#--------------------------------------------------
set(TEST_C_SRCS
  allreduce
  alltoall
  barrier
  broadcast
  gather
  reduce
  sbroadcast
  scatter
#  scatter_long
  solo_gather
#  sreduce
#  sscatter
)
set(TEST_CPP_SRCS
  multi
#  ff_multi
)

include_directories(${MPI_C_INCLUDE_PATH})
message("include_directories(${MPI_INCLUDE_PATH})")

foreach(test ${TEST_C_SRCS})
  add_executable(${test} ${test}.c)
  target_link_libraries(${test} fflib)
endforeach()

foreach(test ${TEST_CPP_SRCS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} fflib)
endforeach()


