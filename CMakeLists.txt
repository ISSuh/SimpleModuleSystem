CMAKE_MINIMUM_REQUIRED (VERSION 3.7)
PROJECT (mrm)

SET ( CMAKE_C_COMPILER g++)
set ( CMAKE_CXX_STANDARD 11)
ADD_COMPILE_OPTIONS ( -g -Wall )

set ( CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake)

#-------------------------------------------------------------------------------
# Linking option about debug, release
#-------------------------------------------------------------------------------
SET ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )
 
SET ( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
SET ( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )

#-------------------------------------------------------------------------------
# Third paty library
#-------------------------------------------------------------------------------
find_package(Boost REQUIRED system)
find_package(cpprestsdk REQUIRED)

#-------------------------------------------------------------------------------
# Project files
#-------------------------------------------------------------------------------
include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    src/main.cpp
)

#-------------------------------------------------------------------------------
# Final target
#-------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
	cpprestsdk::cpprest  
	${Boost_SYSTEM_LIBRARY}
	crypto
	ssl
)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "build")
