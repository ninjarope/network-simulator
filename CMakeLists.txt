project(NetworkSimulator)

# Find SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/deps/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
if(WIN32)
	find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio main)
else()
	find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)
endif()

target_include_directories(NetworkSimulator PUBLIC
	${SFML_INCLUDE_DIR}
)
target_link_libraries(NetworkSimulator ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
