cmake_minimum_required(VERSION 3.16)

project(ssl)

set(CMAKE_CXX_STANDARD 11)

# Find SFML and OpenGL libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCES
  src/main.cpp
  src/primitives.cpp
  src/Core/Game.cpp
  src/Core/World.cpp
  src/Core/Camera.cpp
  src/Core/Input.cpp
  src/Core/Texture.cpp
  src/Core/Model.cpp
  src/Core/Light.cpp
  src/Core/MousePicker.cpp
  src/Core/OBJLoader.cpp
  src/Core/Mesh.cpp
  src/Core/Utils.cpp
  src/Core/Collider.cpp
  src/Core/CubeCollider.cpp
  src/Core/SphereCollider.cpp

  src/Entities/GameObject.cpp
  src/Entities/Player.cpp
  src/Entities/Terrain.cpp
  src/Entities/Bullet.cpp
  src/Entities/Enemy.cpp
  src/Entities/Spaceship.cpp
  src/Entities/Boss.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} 
  ${SOURCES}
)

include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

# Link SFML and OpenGL libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system OpenGL::GL)
