# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "src\\CMakeFiles\\QtCity_autogen.dir\\AutogenUsed.txt"
  "src\\CMakeFiles\\QtCity_autogen.dir\\ParseCache.txt"
  "src\\QtCity_autogen"
  )
endif()
