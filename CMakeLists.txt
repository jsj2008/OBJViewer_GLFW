cmake_minimum_required(VERSION 3.4)
set(APP_NAME MotorGrafico_0_5)
project(${APP_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"windows.h\"")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"GL/glew.h\"")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"GL/freeglut.h\"")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"glm.hpp\"")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"gtc/matrix_transform.hpp\"")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include\"gtc/type_ptr.hpp\"")

add_definitions(-DGLEW_STATIC)

include_directories(.)
include_directories(./include)
include_directories(./include/utils)
include_directories(./include/inputs)
include_directories(./include/loaders)
include_directories(./include/objects)
include_directories(./include/objects/Material)
include_directories(./include/objects/Material/Textures)
include_directories(./libs/include)

link_directories(./libs/lib)

set(SOURCE_FILES

        include/loaders/BMPloader.cpp
        include/loaders/BMPloader.hpp
        include/loaders/ObjectDataloader.cpp
        include/loaders/ObjectDataloader.hpp
        include/loaders/shader_utils.cpp
        include/loaders/shader_utils.hpp

        include/inputs/Raton.cpp
        include/inputs/Raton.hpp
        include/inputs/Teclado.cpp
        include/inputs/Teclado.hpp

        include/objects/BasicObjects.cpp
        include/objects/BasicObjects.hpp
        include/objects/ObjectData.cpp
        include/objects/ObjectData.hpp
        include/objects/Object.cpp
        include/objects/Object.hpp
        include/objects/Object3D.cpp
        include/objects/Object3D.hpp
        include/objects/Camera.cpp
        include/objects/Camera.hpp
        include/objects/LuzPuntual.cpp
        include/objects/LuzPuntual.hpp
        include/objects/renderObject.cpp
        include/objects/renderObject.hpp

        include/objects/Material/Material.cpp
        include/objects/Material/Material.hpp
        include/objects/Material/Shader.cpp
        include/objects/Material/Shader.hpp
        include/objects/Material/Textures/Textura.cpp
        include/objects/Material/Textures/Textura.hpp

        include/utils/stringHelper.hpp
        include/utils/stringHelper.cpp
        include/utils/InitHelper.cpp
        include/utils/InitHelper.hpp

        main.cpp
        include/loaders/Consola.cpp include/loaders/Consola.hpp)

add_executable(${APP_NAME} ${SOURCE_FILES})

target_link_libraries(${APP_NAME} glew32s opengl32 freeglut)

add_custom_command(
        TARGET ${APP_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build/Debug/data/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_SOURCE_DIR}/build/Debug/data/
)