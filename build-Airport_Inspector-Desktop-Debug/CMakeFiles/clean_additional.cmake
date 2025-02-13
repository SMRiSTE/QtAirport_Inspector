# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Airport_Inspector_autogen"
  "CMakeFiles\\Airport_Inspector_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Airport_Inspector_autogen.dir\\ParseCache.txt"
  )
endif()
