#ifndef HEADERS_H
#define HEADERS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//defines constants
const int screenWidth = 912;//910.66667
const int screenHeight = 768/1.5;//512
const int boardHeight = 433;//650
const int boardWidth = 433;
const int tigerHeight = 73;
const int tigerWidth = 73;
const int goatHeight = 73;
const int goatWidth = 73;
const int playerHeight = 73;
const int playerWidth = 73;
const int selectorHeight = 73;
const int selectorWidth = 73;
const int boardX = (screenWidth - boardWidth)/2;
const int boardY = (screenHeight - boardHeight)/2;
const float AITime = 0.1;
const int numberOfStates = 10;

//directions in which movement can take place
const int direction[4] = {1, 4, 5, 6};
const int corner[4] = {1, 5, 21, 25};
//direction[0] = 1;//horizontal
//direction[1] = 4;//diagonal 1
//direction[2] = 5;//vertical
//direction[3] = 6;//diagonal 2
const int INF = 1000000;

//the offsets for moving sprites by one unit in x or y direction.
const int dx = boardWidth/4;
const int dy = boardHeight/4;
const float xFactor = screenWidth * static_cast<float>(1)/1366;//used for non-fullscreen mode.
const float yFactor = screenHeight * static_cast<float>(1)/768;

const int totalTime = 5;

enum Player {Tiger = 1, Goat};
enum State {N = 0, T, G, V}; // N = Nothing, T = Tiger, G = Goat, V = validMoveSprite

#endif
