find_path( jsoncpp_SOURCE CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/jsoncpp" )

if ( jsoncpp_SOURCE )
    set( jsoncpp_FOUND TRUE )
    set( jsoncpp_BUILD "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp_build" )
    set( jsoncpp_DISTRIBUTION "${CMAKE_CURRENT_BINARY_DIR}/distribution" )

    include( ExternalProject )
    ExternalProject_Add( jsoncpp SOURCE_DIR ${jsoncpp_SOURCE}
            PREFIX jsoncpp_build
            INSTALL_DIR ${jsoncpp_DISTRIBUTION}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${jsoncpp_DISTRIBUTION}
            -DBUILD_SHARED_LIBS=YES -DBUILD_STATIC_LIBS=NO
            -DJSONCPP_WITH_POST_BUILD_UNITTEST=NO
            -DJSONCPP_WITH_TESTS=NO -DJSONCPP_WITH_PKGCONFIG_SUPPORT=NO)

    set( jsoncpp_INCLUDE "${jsoncpp_SOURCE}/include" )
    set( jsoncpp_LIBRARY "${jsoncpp_DISTRIBUTION}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}jsoncpp${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    message( STATUS "Found jsoncpp: ${jsoncpp_SOURCE}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate jsoncpp dependency.${Reset}" )
endif ( )