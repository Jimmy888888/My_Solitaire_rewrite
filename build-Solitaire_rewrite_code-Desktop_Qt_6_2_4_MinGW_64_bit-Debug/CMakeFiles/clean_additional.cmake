# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Solitaire_rewrite_code_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Solitaire_rewrite_code_autogen.dir\\ParseCache.txt"
  "Solitaire_rewrite_code_autogen"
  )
endif()
