#include <SFML/Graphics.hpp>
#include "helperf.h"

int main()
{
    sf::Texture t;

    if(!t.loadFromFile("Resource\\sprite1.png"))
    {
        std::printf("\nFor some reasons we couldn't load image. It should be with this executable file");
        return 0;
    }

    sf::Sprite s;
    s.setTexture(t);
    s.setTextureRect(sf::IntRect(0,0,40,40));

    sf::Font f;
    if(!f.loadFromFile("Resource\\sansation.ttf"))
    {
        std::printf("\nFor some reason we couldn't load image. It should be with this executable file");
        return 0;
    }

    sf::RenderWindow app(sf::VideoMode(650,400),"KM's MineSweeper",sf::Style::Close);
    sf::Event e;

    int i,j,minesf;
    minesf = 0;
    unsigned minesc = 0;
    short win = 0;
    short lose = 0;
    bool is_game_haulted = false;
    short *data = new short[100];
    short *map = new short[100];

    ResetGame(map,data);
    ReadGameData(win,lose);
    app.setFramerateLimit(30);

    sf::Text minesRemaining;
    minesRemaining.setPosition(410,0);
    minesRemaining.setFont(f);
    minesRemaining.setString(sf::String("Mines\nRemaining : ") + std::to_string(100 - minesc));

    sf::Text mineFlagged;
    mineFlagged.setPosition(410,100);
    mineFlagged.setFont(f);
    mineFlagged.setString(sf::String("Mines\n\tFlagged : ") + std::to_string(minesf));

    sf::Text wintext;
    wintext.setPosition(410,200);
    wintext.setFont(f);
    wintext.setString(sf::String("Games\n\tWon : ") + std::to_string(win));

    sf::Text losetext;
    losetext.setPosition(410,300);
    losetext.setFont(f);
    losetext.setString(sf::String("Games\n\tLose : ") + std::to_string(lose));

    sf::Text result;
    result.setOutlineThickness(1.5);
    result.setPosition(60,200);
    result.setFont(f);
    result.setString("");

    while(app.isOpen())
    {
        while(app.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                WriteGameData(win,lose);
                app.close();
            }

            if(e.type == sf::Event::KeyPressed && is_game_haulted){
                result.setString("");
                is_game_haulted = false;
                ResetGame(map,data);
                minesf = minesc = 0;
                mineFlagged.setString(sf::String("Mines\nFlagged : ") + std::to_string(minesf));
                minesRemaining.setString(sf::String("Mines\nRemaining : ") + std::to_string(100 - minesc));
            }

            if(e.type == sf::Event::MouseButtonPressed && !is_game_haulted)
            {
                sf::Vector2i mPos = sf::Mouse::getPosition(app);
                i = mPos.x / PSIZE;
                j = mPos.y / PSIZE;

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && i < 10 && j < 10)
                {
                    //if the selected tile was flagged
                    if(map[i*10+j] == MSFLAG)
                    {
                        continue;
                    }
                    //if it is not already opened
                    else if(map[i*10+j] != data[i*10+j] + 1)
                    {
                        map[i*10+j] = data[i*10+j]+1;

                        //if clicked on mine ( on losing game)
                        if(data[i*10+j] == MS_MINE)
                        {
                            OpenAll(map,data);
                            result.setString("\t\tYou lose!\nBetter luck next time.");
                            result.setOutlineColor(sf::Color::Red);
                            result.setFillColor(sf::Color::Black);
                            is_game_haulted = true;
                            lose++;
                            losetext.setString(sf::String("Games\nLose : ") + std::to_string(lose));
                        }
                        minesc++;
                    }

                    //if it has 0 tiles then open tiles near it
                    if(data[i*10 + j] == 0)
                    {
                        OpenTiles(map,data,j,i,minesc);
                    }

                    minesRemaining.setString(sf::String("Mines\nRemaining : ") + std::to_string(100 - minesc));
                }

                else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    //if it is closed tile and not flagged
                    if(map[i*10+j] == 0)
                    {
                        minesf++;
                        map[i*10+j] = MSFLAG;
                    }
                    //if the tile is already flagged
                    else if(map[i*10+j] == MSFLAG)
                    {
                        minesf--;
                        map[i*10+j] = 0;
                    }
                    mineFlagged.setString(sf::String("Mines\nFlagged : ") + std::to_string(minesf));
                }
            }
        }
        app.clear(sf::Color::Blue);
        for(i = 0; i < 10; i++)
        {
            for(j = 0; j < 10; j++)
            {
                s.setPosition(float(i*PSIZE),float(j*PSIZE));
                s.setTextureRect(sf::IntRect(map[i*10+j]*PSIZE,0,PSIZE,PSIZE));
                app.draw(s);
            }
        }

        if(minesc == 90 && !is_game_haulted)
        {
            result.setString("\tYou won the game!\nPress any key to start again.");
            result.setFillColor(sf::Color::Black);
            result.setOutlineColor(sf::Color::Green);
            is_game_haulted = true;
            win++;
            wintext.setString(sf::String("Games\nWon : ") + std::to_string(win));
        }

        app.draw(minesRemaining);
        app.draw(mineFlagged);
        app.draw(result);
        app.draw(wintext);
        app.draw(losetext);
        app.display();
    }
    delete []data;
    data = NULL;
    delete []map;
    map = NULL;
    return EXIT_SUCCESS;
}
