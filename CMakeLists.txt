cmake_minimum_required( VERSION 3.0 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Version
project( cpp-rest CXX )
set( cpp-rest_VERSION_MAJOR 1 )
set( cpp-rest_VERSION_MINOR 2017.1 )
set( cpp-rest_VERSION ${cpp-rest_VERSION_MAJOR}.${cpp-rest_VERSION_MINOR} )
set( PACKAGE_VERSION ${cpp-rest_VERSION} )
set( VERSION "${cpp-rest_VERSION}" )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/distribution/bin )

# Project cmake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules" )
find_package( restbed REQUIRED )
find_package( jsoncpp REQUIRED )
find_package( spdlog REQUIRED )

# Include headers
include_directories( SYSTEM ${restbed_INCLUDE} ${jsoncpp_INCLUDE} 
                            ${spdlog_INCLUDE_DIRS} )

# Source files                      
add_executable( ${PROJECT_NAME} src/nccdctrl.cpp src/nccdctrl.h )

# Dependencies to be builded before main executable
add_dependencies( ${PROJECT_NAME} restbed jsoncpp )

# Linker
link_libraries( ${restbed_LIBRARY} ${jsoncpp_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${restbed_LIBRARY} ${jsoncpp_LIBRARY} )

file( COPY config DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/distribution/" )

# Add the install targets
install ( TARGETS ${PROJECT_NAME} 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib )

# Install directories 
install ( DIRECTORY "${restbed_DISTRIBUTION}/lib/" DESTINATION lib )
install( DIRECTORY DESTINATION logs )
