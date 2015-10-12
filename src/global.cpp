/**
 * @file
 *
 * @brief Global variables to be used through several portions of the game.
 *        This eases implementation, but the number of global variables
 *        shold be kept small.
 *
 * @author Alexandre Lopes
 *
 * @copyright (c) 2015 Alexandre Lopes. This project is released under the GNU Public License.
 *
 */

/* This file is part of EngineZ.
 *
 * EngineZ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EngineZ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EngineZ. If not, see <http://www.gnu.org/licenses/>.
 */

#include "global.h"

//Window's parameters
int WINDOW_WIDTH  = 800;
int WINDOW_HEIGHT = 600;

//The window we'll be rendering to 
SDL_Window* window     = NULL; 

//The window renderer 
SDL_Renderer* renderer = NULL;

//Chroma key
int COLOR_KEY[3] = {0, 255, 0}; 
