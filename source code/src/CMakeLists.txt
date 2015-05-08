set( SRC_SOURCES
	main.cpp
	sceneoit.cpp)

add_executable( SRC ${SRC_SOURCES} )
target_link_libraries( SRC ${OIT_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
