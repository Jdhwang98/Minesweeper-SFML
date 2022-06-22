#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include <time.h>
#include "functions.h"


int main()
{
    srand(time(NULL));
    //array which stores whole map
    Map gameMap[sizeX][sizeY];

    //game state variable
    std::string game = "game";
    sf::Clock gameClock;

    //placing bombs in map array
    for (int i = 0; i < bombs; i++) {
        int x = rand() % sizeX;
        int y = rand() % sizeY;
        //bomb is live
        gameMap[x][y].bomb = 1;
    }

    //setting numbers to tiles next to bombs
    //tile number indicator for #of bombs near by
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            getNumbers(gameMap, i, j);
        }
    }

    //SFML STUFF :)
    //setting closed tile testure and sprite
    sf::Texture cTile;
    if (!cTile.loadFromFile("img/closed_tile.png"))
        std::cout << "Could not load closed_tile texture!\n";
    sf::Sprite closedTile(cTile);


    //numbers tile texture and sprite
    sf::Texture numbersT;
    if (!numbersT.loadFromFile("img/numbers.png"))
        std::cout << "Could not load numbers texture!\n";
    sf::Sprite numbers(numbersT);

    //flags tile texture and sprite
    sf::Texture flagT;
    if (!flagT.loadFromFile("img/flag.png"))
        std::cout << "Could not load numbers texture!\n";
    sf::Sprite flag(flagT);

    //bombs tile texture and sprite
    sf::Texture bombT;
    if (!bombT.loadFromFile("img/bomb.png"))
        std::cout << "Could not load numbers texture!\n";
    sf::Sprite bomb(bombT);

    //setting font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "could not load font from file!\n";
    }

    //setting gameover text
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setString("    Game over\nPress R to restart");
    //gameover.setOrigin(floor(gameover.getLocalBounds().width / 2), floor(gameover.getLocalBounds().height / 2));
    gameover.setFillColor(sf::Color::Black);
    gameover.setOutlineColor(sf::Color::White);
    gameover.setOutlineThickness(3);
    gameover.setCharacterSize(sizeX*4);
    gameover.setStyle(sf::Text::Bold);
    gameover.setPosition(sf::Vector2f(0,0));

    //setting win text
    //setting gameover text
    sf::Text win;
    win.setFont(font);
    win.setString("     You won!\nPress R to restart");
    //win.setOrigin((win.getGlobalBounds().width / 2), (win.getGlobalBounds().height / 2));
    win.setFillColor(sf::Color::Black);
    win.setOutlineColor(sf::Color::White);
    win.setOutlineThickness(3);
    win.setCharacterSize(sizeX * 4);
    win.setStyle(sf::Text::Bold);
    win.setPosition(sf::Vector2f(0,0));

    //time text
    sf::Text time;
    time.setFont(font);
    time.setCharacterSize(20);
    time.setFillColor(sf::Color::White);
    time.setPosition(sf::Vector2f(10, 10));

    //bombs text
    sf::Text bombsText;
    bombsText.setFont(font);
    bombsText.setCharacterSize(20);
    bombsText.setFillColor(sf::Color::White);
    bombsText.setPosition(sf::Vector2f(sizeX * 40 - 100, 10));
    std::string b = "Bombs: ";
    b += std::to_string(bombs);
    bombsText.setString(b);


    sf::RenderWindow window(sf::VideoMode(sizeX*40, sizeY*40+40), "Minesweeper");
    window.setFramerateLimit(60);

    int moveIndex = 0;
    int goal = sizeX * sizeY - bombs;

    //game loop
    while (window.isOpen())
    {
        //mouse position in map coordinates
        int  mouseX = sf::Mouse::getPosition(window).x / 40;
        int  mouseY = sf::Mouse::getPosition(window).y / 40 - 1;
        if (game == "game")
        {

            //event loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                //left mouse button
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {

                    if (mouseX < sizeX && mouseY < sizeY && mouseX >= 0 && mouseY >= 0 && gameMap[mouseX][mouseY].state != 2)
                    {
                        //guarantee that first move wont be on bomb
                        if (moveIndex == 0)
                        {
                            //cleares bombs on first move and relocate them, nBombs - number of cleared bombs
                            int nBombs = clearBomb(gameMap, mouseX, mouseY);
                            if (nBombs > 0)
                            {
                                for (int i = 0; i < nBombs; i++) {
                                    int x = rand() % sizeX;
                                    int y = rand() % sizeY;
                                    //randomizing x and y untill it wont be close to first move
                                    while (abs(mouseX - x) <= 1 && abs(mouseY - y) <= 1) {
                                        int x = rand() % sizeX;
                                        int y = rand() % sizeY;
                                    }
                                    gameMap[x][y].bomb = 1;
                                }
                                //since some bombs have been replaced we need to reasign numbers
                                for (int i = 0; i < sizeX; i++) {
                                    for (int j = 0; j < sizeY; j++) {
                                        gameMap[i][j].number = 0;
                                        getNumbers(gameMap, i, j);
                                    }
                                }
                            }
                        }
                        if (gameMap[mouseX][mouseY].number == 0)
                            clearEmpty(gameMap, mouseX, mouseY);
                        gameMap[mouseX][mouseY].state = 1;
                        //checking if opened tile is bomb
                        if (gameMap[mouseX][mouseY].bomb == 1)
                        {
                            for (int i = 0; i < sizeX; i++)
                            {
                                for (int j = 0; j < sizeY; j++)
                                {
                                    //opening all bombs
                                    if (gameMap[i][j].bomb == 1)
                                        gameMap[i][j].state = 1;


                                }
                            }
                            game = "gameover";
                        }

                        moveIndex++;
                    }
                }
                //right mouse button - flag
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                    if (mouseX < sizeX && mouseY < sizeY && mouseX >= 0 && mouseY >= 0)
                    {
                        if (gameMap[mouseX][mouseY].state == 0)
                            gameMap[mouseX][mouseY].state = 2;
                        else if (gameMap[mouseX][mouseY].state == 2)
                            gameMap[mouseX][mouseY].state = 0;
                    }

                }
            }

            //checking if player won
            int temp = 0;
            for (int i = 0; i < sizeX; i++)
            {
                for (int j = 0; j < sizeY;j++)
                {
                    if (gameMap[i][j].state == 1)
                        temp++;
                }
            }
            if (temp == goal)
            {   //set variable to string win for conditional statement
                game = "win";
            }
            //tile color setting
            sf::Color gray(127, 127, 127);
            window.clear(gray);
            //tell sfml how many tiles it's going to display
            for (int i = 0; i < sizeX; i++) {
                for (int j = 0; j < sizeY; j++) {

                    //if state of tile is closed (0) draw closed_tile sprite
                    if (gameMap[i][j].state == 0) {
                        closedTile.setPosition(i * 40, j * 40 + 40);
                        window.draw(closedTile);
                    }
                    else if (gameMap[i][j].state == 1) {
                        //drawing opened tile, depending on number containing by tile sprite is moving to the right by size of one tile
                        numbers.setTextureRect(sf::IntRect(gameMap[i][j].number * 40, 0, 40, 40));
                        numbers.setPosition(i * 40, j * 40 + 40);
                        if (!gameMap[i][j].bomb == 1)
                        {   //shows how many bombs are near on tile
                            window.draw(numbers);
                        }
                        else
                        {   //will display the bombs
                            bomb.setPosition(i * 40, j * 40 + 40);
                            window.draw(bomb);
                        }
                    }
                        //state 2 - flagged tile
                    else if (gameMap[i][j].state == 2)
                    {
                        flag.setPosition(i * 40, j * 40 + 40);
                        window.draw(flag);
                    }
                }
            }
            //drawing time and number of bombs
            time.setString(std::to_string(gameClock.getElapsedTime().asSeconds()));
            window.draw(time);
            window.draw(bombsText);

            //drawing gameover or win text
            if(game=="gameover")
                window.draw(gameover);
            else if (game == "win")
                window.draw(win);
            window.display();
        }
        else if (game == "gameover")
        {
            //event loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //if "R" is pressed game will restart
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                //restarting game
                for (int i = 0; i < sizeX; i++)
                {
                    for (int j = 0; j < sizeY; j++)
                    {
                        gameMap[i][j].number = 0;
                        gameMap[i][j].bomb = 0;
                        gameMap[i][j].state = 0;
                    }
                }
                //placing bombs in map array at random
                for (int i = 0; i < bombs; i++) {
                    int x = rand() % sizeX;
                    int y = rand() % sizeY;
                    gameMap[x][y].bomb = 1;
                }

                //setting numbered tiles next to bombs
                for (int i = 0; i < sizeX; i++) {
                    for (int j = 0; j < sizeY; j++) {
                        getNumbers(gameMap, i, j);
                    }
                }
                moveIndex = 0;
                gameClock.restart();
                game = "game";
            }

        }
        else if (game == "win")
        {
            //event loop (for windowed game)
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //if "R" is pressed game will restart
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                //restarting game
                for (int i = 0; i < sizeX; i++)
                {
                    for (int j = 0; j < sizeY; j++)
                    {
                        gameMap[i][j].number = 0;
                        gameMap[i][j].bomb = 0;
                        gameMap[i][j].state = 0;
                    }
                }
                //placing bombs in map array
                for (int i = 0; i < bombs; i++) {
                    int x = rand() % sizeX;
                    int y = rand() % sizeY;
                    gameMap[x][y].bomb = 1;
                }

                //setting numbers to tiles next to bombs
                for (int i = 0; i < sizeX; i++) {
                    for (int j = 0; j < sizeY; j++) {
                        getNumbers(gameMap, i, j);
                    }
                }
                moveIndex = 0;
                gameClock.restart();
                game = "game";
            }
        }
    }

    return 0;
}


