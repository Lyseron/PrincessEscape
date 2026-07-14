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
	src/Game/Render.cpp
	src/Game/Update.cpp
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

	src/Textures/Textures.cpp

# ---------- PLAYER -------- #

	src/Player/Player.cpp
# -> Player_utils.c
	#src/utils/Player_utils.cpp

# ---------- CHEST -------- #
	src/Map/Chest/Chest.cpp

# ---------- DECOR -------- #
	src/Decor/Decor.cpp

# ---------- ANIM -------- #
	src/Animation/Animation.cpp

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