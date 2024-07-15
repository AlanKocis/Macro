cmake_minimum_required(VERSION 3.8)
project(MacroLog)

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/source/*.c
	${CMAKE_SOURCE_DIR}/source/*.cpp
	${CMAKE_SOURCE_DIR}/imgui/*.cpp
	${CMAKE_SOURCE_DIR}/imgui/*.c
	${CMAKE_SOURCE_DIR}/imgui/*.hpp
	${CMAKE_SOURCE_DIR}glad/*.c
)
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/source/*.h
	${CMAKE_SOURCE_DIR}/source/*.hpp
	${CMAKE_SOURCE_DIR}/imgui/*.h
	${CMAKE_SOURCE_DIR}/glad/*.h
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_subdirectory("${CMAKE_SOURCE_DIR}/glfw-3.3.8")
target_link_libraries(MacroLog glfw)

add_library(GLAD "${CMAKE_SOURCE_DIR}/glad/glad.c")

set(LIBS glfw ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} ${IMGUI_LIBRARY})

# include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/source"
	"${CMAKE_SOURCE_DIR}/glad"
	"${CMAKE_SOURCE_DIR}/imgui"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})





if(MSVC_IDE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()
