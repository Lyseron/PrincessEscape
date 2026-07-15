cmake_minimum_required(VERSION 3.20)

project(Princess_Escape)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(
	Princess_Escape
	src/main.cpp
# ---------- GAME ---------- #

	src/Game/Game.cpp
	src/Game/Events.cpp
	src/Game/Visual.cpp
	src/Game/VisualChange.cpp
# -> Game_utils.c
	src/Game/Utils/ActionInMap.cpp
	src/Game/Utils/Draw.cpp
	src/Game/Utils/Init.cpp
	src/Game/Utils/key.cpp
	src/Game/Utils/LoadImg.cpp
	src/Game/Utils/Move.cpp

# ---------- MAP ----------- #

	src/Map/Map.cpp

# ---------- TEXTURE ------- #

	src/UtilsObject/Textures/Textures.cpp

# ---------- PLAYER -------- #

	src/Player/Player.cpp

# ---------- CHEST -------- #
	src/Map/Interactable/Chest/Chest.cpp
	src/Map/Interactable/Door/Door.cpp
	src/Map/Interactable/Interactable.cpp

# ---------- DECOR -------- #
	src/Map/Decor/Decor.cpp

# ---------- ANIM -------- #
	src/UtilsObject/Animation/Animation.cpp

# ---------- COLLISION -------- #
	src/UtilsObject/Collision/Collision.cpp

)

target_include_directories(
	Princess_Escape
	PRIVATE
	includes
)

target_link_libraries(
	Princess_Escape
	PRIVATE
	SDL3::SDL3
	SDL3_image::SDL3_image
)