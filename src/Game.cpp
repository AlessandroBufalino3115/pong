#include "Game.h"

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

// setting up texture on initiation
bool Game::init()
{
  Ball = Vector();
  Paddle1 = Vector();
  Paddle2 = Vector();

  in_menu = true;

#pragma region Texture_setting
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))  //loading font
  {
    std::cout << "font did not load \n";
  }

  if (!ball_texture.loadFromFile("Data/Images/ball.png"))
  {
    std::cout << "font did not load \n";
  }
  ball.setTexture(ball_texture);
  ball.scale(0.3f,0.3f);
  ball.setPosition(window.getSize().x/2 - (ball.getGlobalBounds().width/2), window.getSize().y/2 - (ball.getGlobalBounds().height/2));
  Ball.vector(30,-20);

  if (!paddle1_texture.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "font did not load \n";
  }
  paddle1.setTexture(paddle1_texture);
  paddle1.rotate(90);
  paddle1.setPosition(paddle1.getGlobalBounds().width, window.getSize().y/2 - (paddle1.getGlobalBounds().height/2));
  paddle1_obj = window.getSize().y/2 - (paddle1.getGlobalBounds().height/2);

  if (!paddle2_texture.loadFromFile("Data/Images/paddleRed.png"))
  {
    std::cout << "font did not load \n";
  }
  paddle2.setTexture(paddle2_texture);
  paddle2.rotate(90);
  paddle2.setPosition(window.getSize().x, window.getSize().y/2 - (paddle2.getGlobalBounds().height/2));
  paddle2_obj = window.getSize().y/2 - (paddle2.getGlobalBounds().height/2);

  Paddle1.new_x = paddle1.getGlobalBounds().width;
  Paddle2.new_x = window.getSize().x;

  if (!powerup_texture.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "font did not load \n";
  }
  powerup.setTexture(powerup_texture);
  powerup.scale(0.3f,0.3f);
  powerup.setPosition(window.getSize().x/2 -powerup.getGlobalBounds().width, window.getSize().y/2 );
#pragma endregion

#pragma region menu_text_init
  menu_text.setString("Welcome to the game, how do you want to play (press enter to continue)");
  menu_text.setPosition(window.getSize().x/5, window.getSize().y/8);
  menu_text.setFillColor(sf::Color(255,255,255,255));
  menu_text.setFont(font);
  menu_text.setCharacterSize(20);

  solo.setString("2 Players");
  solo.setPosition(window.getSize().x/4, window.getSize().y/4);
  solo.setFillColor(sf::Color(255,255,255,255));
  solo.setFont(font);
  solo.setCharacterSize(20);

  bot.setString("AI");
  bot.setPosition(window.getSize().x/2 + window.getSize().x/4, window.getSize().y/4);
  bot.setFillColor(sf::Color(255,255,255,255));
  bot.setFont(font);
  bot.setCharacterSize(20);

  leaderboard.setString("Leaderboard");
  leaderboard.setPosition(window.getSize().x/2, window.getSize().y/4);
  leaderboard.setFillColor(sf::Color(255,255,255,255));
  leaderboard.setFont(font);
  leaderboard.setCharacterSize(20);
#pragma endregion

#pragma region difficulties
  hard.setString("Hard");
  hard.setPosition(window.getSize().x/4, window.getSize().y/4);
  hard.setFillColor(sf::Color(255,255,255,255));
  hard.setFont(font);
  hard.setCharacterSize(20);

  medium.setString("Medium");
  medium.setPosition(window.getSize().x/2, window.getSize().y/4);
  medium.setFillColor(sf::Color(255,255,255,255));
  medium.setFont(font);
  medium.setCharacterSize(20);

  easy.setString("Easy");
  easy.setPosition(window.getSize().x/2 + window.getSize().x/4, window.getSize().y/4);
  easy.setFillColor(sf::Color(255,255,255,255));
  easy.setFont(font);
  easy.setCharacterSize(20);

  difficulties_exp.setString("You have decided to play against a bot, what difficulty\n would you like (you will only use the up and down arrow keys)");
  difficulties_exp.setPosition(window.getSize().x/3, window.getSize().y/2);
  difficulties_exp.setFillColor(sf::Color(255,255,255,255));
  difficulties_exp.setFont(font);
  difficulties_exp.setCharacterSize(20);
#pragma endregion

#pragma region leaderboard
  leaderboardText.setString("Scoreboard, press x to delete all the data and then refresh");
  leaderboardText.setPosition(window.getSize().x/4, window.getSize().y/8);
  leaderboardText.setFillColor(sf::Color(255,255,255,255));
  leaderboardText.setFont(font);
  leaderboardText.setCharacterSize(20);

  actualscores.setPosition(window.getSize().x/3, window.getSize().y/4);
  actualscores.setFillColor(sf::Color(255,255,255,255));
  actualscores.setFont(font);
  actualscores.setCharacterSize(20);

  headers.setString("Player 1(L)    Bot               Player 2(R)");
  headers.setPosition(window.getSize().x/3, window.getSize().y/5);
  headers.setFillColor(sf::Color(255,255,255,255));
  headers.setFont(font);
  headers.setCharacterSize(20);
#pragma endregion

#pragma region score_init
  score_in_game.setPosition(window.getSize().x/3 , window.getSize().y/10);
  score_in_game.setFillColor(sf::Color(255,255,255,255));
  score_in_game.setFont(font);
  score_in_game.setCharacterSize(30);
#pragma endregion

  spawnBall();
  return true;
}

//spawning the ball when needed
void Game::spawnBall()
{
  #pragma region resetting_everything
  show_powerup = false;
  if (paddle2buffed)  //if the paddles were enlarged, bring them back to their original size
  {
    paddle2.scale(0.5f,1);
  }
  if (paddle1buffed)
  {
    paddle1.scale(0.5f,1);
  }
  new_time_powerup = 0;
  buffCreation();

  paddle1_obj = window.getSize().y/2 - (paddle1.getGlobalBounds().height/2);
  paddle2_obj = window.getSize().y/2 - (paddle2.getGlobalBounds().height/2);
  ball.setPosition(window.getSize().x/2 - (ball.getGlobalBounds().width/2), window.getSize().y/2 - (ball.getGlobalBounds().height/2));
  #pragma endregion

  int n = rand() % 4;

  switch (n)
  {
    case 0:
    {
      Ball.startVectorBall(rand() % 50 + 10, (rand() % 30 + 5));
      break;
    }
    case 1:
    {
      Ball.startVectorBall((rand() % 50 + 10) * -1, (rand() % 30 + 5));
      break;
    }
    case 2:
    {
      Ball.startVectorBall(rand() % 50 + 10, (rand() % 30 + 5) * -1);
      break;
    }
    case 3:
    {
      Ball.startVectorBall((rand() % 50 + 10) * -1, (rand() % 30 + 5) * -1);
      break;
    }
  }
}

// handling the logistics per update
void Game::update(float dt)
{
  score_in_game.setString(std::to_string(score_L)+"                 Score                 " + std::to_string(score_R));
  checkCollision();

#pragma region Timer_code_for_AI
  std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::high_resolution_clock::now().time_since_epoch());
  auto currTime = ms.count();    // get the current time to work with the two timers

  if ((currTime>= new_time) && ai_selected)    //when the time is passed and the ai is selected call the function to automatically move the paddle
  {
    new_time = currTime + time_diff_buffer;    // set the next timer
    aiDrive();
  }
#pragma endregion

#pragma region Timer_code_for_buffspawn
  if (!show_powerup)    // if no power-up is present in the scene right now then start timer to spawn a new one
  {
    if ((currTime >= new_time_powerup))
    {
      show_powerup = true;
    }
  }
#pragma endregion

#pragma region Paddle_Clamps //keeping the paddles inside the screen
  if (paddle1_obj > window.getSize().y - paddle1.getGlobalBounds().height)
  {
    paddle1_obj = window.getSize().y - paddle1.getGlobalBounds().height;
  }
  else if (paddle1_obj < 0)
  {
   paddle1_obj =  0;
  }

  if (paddle2_obj > window.getSize().y - paddle2.getGlobalBounds().height)
  {
    paddle2_obj = window.getSize().y - paddle2.getGlobalBounds().height;
  }
  else if (paddle2_obj < 0)
  {
    paddle2_obj =  0;
  }
#pragma endregion

#pragma region Movement_code
  Paddle1.new_y = paddle1_obj;
  Paddle2.new_y = paddle2_obj;

  if(Ball.unit_x > 0)
  {
    hit_buffer = true;
  }
  else
  {
    hit_buffer = false;
  }

  if(!in_menu)
  {
    Paddle1.vector(paddle1.getPosition().x,paddle1.getPosition().y);
    paddle1.move(0, Paddle1.unit_y * dt * Paddle1.mag* 10);

    Paddle2.vector(paddle2.getPosition().x,paddle2.getPosition().y);
    paddle2.move(0, Paddle2.unit_y * dt * Paddle2.mag * 10);
  }
  ball.move(dt* resultant_y *Ball.unit_x, dt * speed_build_up_x * Ball.unit_y);
#pragma endregion
}

//rendering assets
void Game::render()
{
    if (in_menu)
    {
      if (!difficulty_draw && !draw_leaderboard)
      {
        window.draw(ball);
        window.draw(menu_text);
        window.draw(solo);
        window.draw(bot);
        window.draw(leaderboard);
      }
      else if (difficulty_draw && !draw_leaderboard)
      {
        window.draw(easy);
        window.draw(medium);
        window.draw(hard);
        window.draw(difficulties_exp);
      }
      else if (!difficulty_draw && draw_leaderboard)
      {
        window.draw(leaderboardText);
        window.draw(actualscores);
        window.draw(headers);
      }
    }
    else
    {
      window.draw(score_in_game);
      window.draw(ball);
      window.draw(paddle2);
      window.draw(paddle1);
      if (show_powerup)
      {
        window.draw(powerup);
      }
    }
}

//writing to the designated file
void Game::addingFile()
{
  std::ofstream file;

  if (!file)  // checking if the file is reachable
  {
    printf("file has not been found");
  }
  else
  {
    file.open(file_path,std::ios::app);

    if (score_R !=0 || score_L !=0)
    {
      if (ai_selected)
      {
        file << std::to_string(score_L) +"ss" + std::to_string(score_R) + "ss" + "--/"<< std::endl;
      }
      else
      {
        file << std::to_string(score_L) +"ss" + "--" + "ss" + std::to_string(score_R) +"/"<< std::endl;
      }
    }
    file.close();
  }
}

//deleting all the data from the file
void Game::deleteDataFile()
{
  std::ofstream ofs;
  ofs.open(file_path, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}

//reading from the designate file and printing on the leaderboard screen
void Game::readingFile()
{
  std::ifstream  file(file_path);
  std::string per_line_read;
  std::string mainStorage;

  while (file >> per_line_read)
  {
    for (char const &c: per_line_read)     // formatting the output depending on the contents of the file
    {
      if (c == '/')
      {
        mainStorage += "\n";
      }
      else if(c == 's')
      {
        for (int i = 0; i < 12; ++i)
        {
          mainStorage += ' ';
        }
      }
      else
      {
        mainStorage += c;
      }
    }
  }
  actualscores.setString(mainStorage);
}

//on key press events, checked just need to delete the bottom part
void Game::keyPressed(sf::Event event)
{
  #pragma region call_on_escape_key
  if (event.key.code == sf::Keyboard::Escape)
  {
      if (difficulty_draw && in_menu)
      {
        difficulty_draw = !difficulty_draw;
        ai_selected = false;
      }
      else if (!in_menu)
      {
        difficulty_draw = false;
        in_menu = !in_menu;
        addingFile();
        ai_selected = false;
        score_L = 0;
        score_R = 0;
      }
      else if (draw_leaderboard)
      {
        draw_leaderboard = !draw_leaderboard;
      }
  }
  #pragma endregion

  #pragma region menu_selection
  if (in_menu)
  {
    #pragma region enter_and_logic_follows
    // pressing enter and logic that goes through the decision
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (!difficulty_draw)
      {
        //when in selection_menu fo difficulty enter press
        switch (selection_menu)
        {
          case 1:
            draw_leaderboard = true;
            readingFile();
            break;

          case 2:
            difficulty_draw = true;
            break;

          case 3:
            in_menu = false;
            spawnBall();
            break;
        }
      }
      else
      {
        ai_selected = true;   //when in selection_menu fo difficulty enter press

        switch (selection_menu)
        {
          case 1:
            time_diff_buffer = 200;
            break;

          case 2:
            time_diff_buffer = 300;
            break;

          case 3:
            time_diff_buffer = 450;
            break;
        }
        spawnBall();
        in_menu = false;
      }
    }
    #pragma endregion
    #pragma region  menu_selection_navigation
    //navigation of the option in the menu
    if (event.key.code == sf::Keyboard::Left)
    {
      selection_menu--;
      if (selection_menu == 0)
      {
        selection_menu = 3;
      }
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
      selection_menu++;
      if (selection_menu == 4)
      {
        selection_menu = 1;
      }
    }

    if (difficulty_draw)
    {
      switch (selection_menu)
      {
        case 1:
          hard.setString("<  Hard  >");
          medium.setString("Medium");
          easy.setString("Easy");
          break;

        case 2:
          hard.setString("Hard");
          medium.setString("<  Medium  >");
          easy.setString("Easy");
          break;

        case 3:
          hard.setString("Hard");
          medium.setString("Medium");
          easy.setString("<  Easy  >");
          break;
      }
    }
    else
    {
      switch (selection_menu)
      {
        case 1:
          solo.setString("2 Players");
          bot.setString("AI");
          leaderboard.setString("<Leaderboard>");
          break;

        case 2:
          solo.setString("2 Players");
          bot.setString("<AI>");
          leaderboard.setString("Leaderboard");
          break;

        case 3:
          solo.setString("> 2 Players <");
          bot.setString("   AI");
          leaderboard.setString("Leaderboard");
          break;
      }
    }
#pragma endregion
  }
  else // if not in the menus scene then we allow the movement of the paddles
  {
    // movement paddle right
    if (!ai_selected)
    {
      if (!in_menu && event.key.code == sf::Keyboard::W)
      {
        paddle1_obj -= 50;
      }
      else if (!in_menu && event.key.code == sf::Keyboard::S)
      {
        paddle1_obj += 50;
      }
    }

    // movement paddle left
    if (!in_menu && event.key.code == sf::Keyboard::Up)
    {
      paddle2_obj -= 50;
    }
    else if (!in_menu && event.key.code == sf::Keyboard::Down)
    {
      paddle2_obj += 50;
    }
  }
  #pragma endregion

  //calling the deletion of data in the file
  if (event.key.code == sf::Keyboard::X)
  {
    deleteDataFile();
  }
}

//called from when the timer for a new direction is up
void Game::aiDrive()
{
  float mid_paddle = paddle1.getPosition().y + paddle1.getGlobalBounds().height;
  float mid_ball = ball.getPosition().y + ball.getGlobalBounds().width;

  if (mid_paddle > mid_ball)   // ball on top
  {
    paddle1_obj -= 30;
  }
  else if (mid_paddle < mid_ball)   // ball underneath
  {
    paddle1_obj += 30;
  }
}

//obj collisions
void Game::checkCollision()
{
  #pragma region ball_bounding_box
  int x_max = ball.getPosition().x + ball.getGlobalBounds().width;
  int x_min = ball.getPosition().x;
  int y_min = ball.getPosition().y;
  int y_max = ball.getPosition().y + ball.getGlobalBounds().height;
  #pragma endregion

  #pragma region side_screen_collision checks
  if (!in_menu) // while in game
  {
    if ( x_min < 0)        //left side screen hit check
    {
      score_R +=1;
      spawnBall();
    }

    if (x_max > (window.getSize().x ))        // right hit check
    {
      score_L +=1;
      spawnBall();
    }
  }
  else   // while not in game
  {
    if ( x_min < 0)        //left side screen hit check in menu
    {
      Ball.unit_x *= -1;
    }

    if (x_max > (window.getSize().x ))        // right hit check in menu
    {
      Ball.unit_x *= -1;
    }
  }
  #pragma endregion

  #pragma region left_paddle_collision
  if (x_max  >= paddle2.getPosition().x - paddle2.getGlobalBounds().width && !in_menu && hit_buffer) //right paddle hit checks
  {
    hit_buffer = false;
    //head on
    if ((y_min >= paddle2.getPosition().y) && (y_max<= paddle2.getPosition().y + paddle2.getGlobalBounds().height))
    {
      resultant_y += (Paddle2.mag * 2 * Paddle2.unit_y);
      Ball.unit_x *= -1;
      speed_build_up_x += 2;
    }
    //top hit
    else if ((y_min < paddle2.getPosition().y) && (y_max>= paddle2.getPosition().y))
    {
      if (Ball.unit_x > 0 && Ball.unit_y > 0)
      {
        resultant_y += (Paddle2.mag * 2 * Paddle2.unit_y);
        Ball.unit_x *= -1;
        Ball.unit_y *= -1;
        speed_build_up_x += 2;
      }
      else
      {
        resultant_y += (Paddle2.mag * 2 * Paddle2.unit_y);
        Ball.unit_x *= -1;
        speed_build_up_x += 2;
      }
    }
    // bottom hit
    else if ((y_min <= paddle2.getPosition().y + paddle2.getGlobalBounds().height) && (y_max> paddle2.getPosition().y + paddle2.getGlobalBounds().height))
    {
      if (Ball.unit_x > 0 && Ball.unit_y < 0)
      {
        resultant_y += (Paddle2.mag * 2 * Paddle2.unit_y);
        Ball.unit_y *= -1;
        Ball.unit_x *= -1;
        speed_build_up_x += 2;
      }
      else
      {
        resultant_y += (Paddle2.mag * 2 * Paddle2.unit_y);
        Ball.unit_x *= -1;
        speed_build_up_x += 2;
      }
    }
  }
  #pragma endregion

  #pragma region right_paddle_collision
  if (x_min  <= paddle1.getPosition().x && !in_menu && !hit_buffer)  //left paddle hit checks
  {
    hit_buffer = true;
    //head on
    if ((y_min >= paddle1.getPosition().y) && (y_max <= paddle1.getPosition().y + paddle1.getGlobalBounds().height))
    {
      resultant_y += (Paddle1.mag * 2 * Paddle1.unit_y);
      Ball.unit_x *= -1;
      speed_build_up_x += 2;
    }
    //top hit
    else if ((y_min < paddle1.getPosition().y) && (y_max>= paddle1.getPosition().y))
    {
      if(Ball.unit_x < 0 && Ball.unit_y > 0)
      {
        resultant_y += (Paddle1.mag * 2 * Paddle1.unit_y);
        Ball.unit_x *= -1;
        Ball.unit_y *= -1;
        speed_build_up_x += 2;
      }
      else
      {
        resultant_y += (Paddle1.mag * 2 * Paddle1.unit_y);
        Ball.unit_x *= -1;
        speed_build_up_x += 2;
      }
    }
    //bottom hit
    else if ((y_min <= paddle1.getPosition().y + paddle1.getGlobalBounds().height) && (y_max > paddle1.getPosition().y + paddle1.getGlobalBounds().height))
    {
      if(Ball.unit_x < 0 && Ball.unit_y < 0)
      {
        resultant_y += (Paddle1.mag * 2 * Paddle1.unit_y);
        Ball.unit_x *= -1;
        Ball.unit_y *= -1;
        speed_build_up_x += 2;
      }
      else
      {
        resultant_y += (Paddle1.mag * 2 * Paddle1.unit_y);
        Ball.unit_x *= -1;
        speed_build_up_x += 2;
      }
    }
  }
  #pragma endregion

  #pragma region top/bot_screen_collisions_check
  // top screen hit check
  if (y_min < 0)
  {
    Ball.unit_y *= -1;
    speed_build_up_x += 4;
  }
  if (y_max > window.getSize().y)     // bottom hit check
  {
    Ball.unit_y *= -1;
    speed_build_up_x += 4;
  }
  #pragma endregion

  #pragma region collisions_with_the_buff
  if (show_powerup)
  {
    if (((powerup.getPosition().x <= x_min && powerup.getPosition().x + powerup.getGlobalBounds().width >= x_min) && (powerup.getPosition().y <= y_min &&powerup.getPosition().y + powerup.getGlobalBounds().height >=y_min))) // this is for the top left of the ball
    {
      show_powerup = false;
      if (hit_buffer && !paddle1buffed)
      {
        paddle1buffed = true;
        paddle1.scale(2,1);
      }
      else if (!hit_buffer && !paddle2buffed)
      {
        paddle2buffed = true;
        paddle2.scale(2,1);
      }
      buffCreation();
    }
    if (((powerup.getPosition().x <= x_max && powerup.getPosition().x + powerup.getGlobalBounds().width >= x_max) && (powerup.getPosition().y <= y_max && powerup.getPosition().y + powerup.getGlobalBounds().height >= y_max))) // this is for the bottom left of the ball
    {
      show_powerup = false;

      if (hit_buffer && !paddle1buffed)
      {
        paddle1buffed = true;
        paddle1.scale(2,1);
      }
      else if (!hit_buffer && !paddle2buffed)
      {
        paddle2buffed = true;
        paddle2.scale(2,1);
      }
      buffCreation();
    }
  }
  #pragma endregion
}

//called when we want the timer for a new buff spawn to start
void Game::buffCreation()
{
  if (!show_powerup)
  {
    powerup.setPosition(window.getSize().x /2,rand() % (window.getSize().y - 100) + 20);

    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now().time_since_epoch());
    auto currTime = ms.count();

    int n = rand() % 15000 + 25000;

    new_time_powerup = currTime + n;
  }
}