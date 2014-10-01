project (City)

file(GLOB_RECURSE City_SOURCES "src/*.cpp")
file(GLOB_RECURSE City_HEADERS "src/*.h")

set (city_INCLUDE_DIRS "")
foreach (_headerFile ${City_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND City_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES City_INCLUDE_DIRS)

include_directories(${City_INCLUDE_DIRS})
add_executable (CityExe ${City_SOURCES})
