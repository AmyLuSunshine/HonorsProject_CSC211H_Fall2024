cmake_minimum_required(VERSION 3.16)
project(campus_jobs_app VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt prefix path
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.7/mingw_64")

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
)

# Source and header files
set(PROJECT_SOURCES
    src/main.cpp
    src/auth/loginwindow.cpp
    src/auth/registerwindow.cpp
    src/database/database.cpp
    src/models/user.cpp
    src/models/job.cpp
    src/models/application.cpp
    src/ui/jobdetailwidget.cpp
    src/ui/joblistwidget.cpp
    src/ui/mainwindow.cpp
    src/ui/profilewidget.cpp
    src/ui/searchfilterwidget.cpp
)

set(PROJECT_HEADERS
    include/auth/loginwindow.h
    include/auth/registerwindow.h
    include/database/database.h
    include/models/user.h
    include/models/job.h
    include/models/application.h
    include/ui/jobdetailwidget.h
    include/ui/joblistwidget.h
    include/ui/mainwindow.h
    include/ui/profilewidget.h
    include/ui/searchfilterwidget.h
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)

# Deployment
if(WIN32)
    set(DEBUG_SUFFIX)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    # Copy Qt DLLs
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::Core>
            $<TARGET_FILE:Qt6::Gui>
            $<TARGET_FILE:Qt6::Widgets>
            $<TARGET_FILE:Qt6::Sql>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # Copy platform plugin
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms"
    )

    # Copy SQL plugins
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_PREFIX_PATH}/plugins/sqldrivers/qsqlite.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers"
    )
endif()
