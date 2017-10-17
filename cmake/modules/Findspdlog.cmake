if(spdlog_FOUND)
return()
endif()

find_path(spdlog_INCLUDE_DIR spdlog/spdlog.h HINT ${EXTERNAL_ROOT}/include dependency/spdlog/include)

set(spdlog_INCLUDE_DIRS ${spdlog_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(spdlog  DEFAULT_MSG spdlog_INCLUDE_DIR)
