#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sys/time.h>
class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void checkCollision();
  void spawnBall();
  void aiDrive();
  void readingFile();
  void addingFile();
  void deleteDataFile();
  void buffCreation();


 private:
  sf::Texture powerup_texture;
  sf::Sprite powerup;
  long long int new_time_powerup = 0;
  bool show_powerup = false;
  bool paddle1buffed = false;
  bool paddle2buffed = false;

  sf::Font font;
  sf::RenderWindow& window;

  sf::Sprite paddle1;
  sf::Texture paddle1_texture;
  int paddle1_obj = 0;
  Vector Paddle1;

  sf::Sprite paddle2;
  sf::Texture paddle2_texture;
  int paddle2_obj = 0;
  Vector Paddle2;

  sf::Text leaderboardText;
  sf::Text actualscores;
  sf::Text headers;
  bool draw_leaderboard;
  std::string file_path = "Scoreboard.txt";

  Vector Ball;
  sf::Sprite ball;
  sf::Texture ball_texture;
  float resultant_y=200;
  int speed_build_up_x =250;
  bool hit_buffer = false;

  bool in_menu = false;
  sf::Text menu_text;
  sf::Text solo;
  sf::Text bot;
  sf::Text leaderboard;

  sf::Text easy;
  sf::Text medium;
  sf::Text hard;
  sf::Text difficulties_exp;
  bool difficulty_draw = false;
  int selection_menu = 1;

  sf::Text score_in_game;
  int score_L = 0;
  int score_R = 0;

  bool ai_selected = false;
  long long int new_time = 0;
  int time_diff_buffer   = 0;
};

#endif // PONG_GAME_H