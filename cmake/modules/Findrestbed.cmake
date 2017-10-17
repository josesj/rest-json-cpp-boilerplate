find_path( restbed_SOURCE CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/restbed" )

if ( restbed_SOURCE )
    set( restbed_FOUND TRUE )
    set( restbed_BUILD "${CMAKE_CURRENT_BINARY_DIR}/restbed_build" )
    set( restbed_DISTRIBUTION "${CMAKE_CURRENT_BINARY_DIR}/distribution" )

    include( ExternalProject )
    ExternalProject_Add( restbed SOURCE_DIR ${restbed_SOURCE}
            PREFIX restbed_build
            INSTALL_DIR ${restbed_DISTRIBUTION}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${restbed_DISTRIBUTION}
            -DBUILD_SSL=${BUILD_SSL} -DBUILD_SHARED=YES
            -DCMAKE_INSTALL_LIBDIR=lib )

    set( restbed_INCLUDE "${restbed_SOURCE}/source" )
    set( restbed_LIBRARY "${restbed_DISTRIBUTION}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}restbed${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    message( STATUS "Found Restbed: ${restbed_SOURCE}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate Restbed dependency.${Reset}" )
endif ( )
