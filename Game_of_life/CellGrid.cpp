#include "CellGrid.h"

#define h sf::VideoMode::getDesktopMode().height
#define w sf::VideoMode::getDesktopMode().width

CellGrid::CellGrid(int dim)
{
    lin = h / (dim + 0.5);
    col = w / (dim + 0.5);

    act = new bool* [lin];
    for (int i = 0; i < lin; i++)
        act[i] = new bool[col];


    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            act[i][j] = 0;

    urm = new bool* [lin];
    for (int i = 0; i < lin; i++)
        urm[i] = new bool[col];


}

CellGrid::~CellGrid()
{
    for (int i = 0; i < lin; i++)
    {
        delete[] act[i];
        delete[] urm[i];
    }
    delete[]act;
    delete[]urm;

}




void CellGrid::init_rand()
{
    srand(time(NULL));

    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
        {

            act[i][j] = rand() % 2;


        }
    next();

}


void CellGrid::init()
{


    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
        {

            act[i][j] = 0;


        }
    next();

}


void CellGrid::add(int l, int c)
{
    if ((l >= 0 && l <= lin) && (c >= 0 && c <= col))  // incadrare in fereastra
        act[l][c] = 1;

}

void CellGrid::del(int l, int c)
{
    if ((l >= 0 && l <= lin) && (c >= 0 && c <= col))  // incadrare in fereastra
        act[l][c] = 0;

}


int CellGrid::nrvec(int i, int j)
{
    int t = 0;
    int y, x;  //p(y,x)

    for (int l = i - 1; l <= i + 1; l++)
        for (int c = j - 1; c <= j + 1; c++)
        {   //  warp space  ( miscare pacman)
            if (!(l == i && c == j))
            {
                y = l; x = c;
                if (y < 0)   y += lin;  // sus => jos
                if (y == lin) y = 0;    // jos => sus   
                if (x < 0)   x += col; // stanga => dreapta
                if (x == col) x = 0;    // dreapta => stanga

                t += act[y][x];
            }
        }
    return t;
}


void CellGrid::next()
{
    //reguli  
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
        {


            urm[i][j] = act[i][j];

            if (!act[i][j])
            {
                if (nrvec(i, j) == 3)
                    urm[i][j] = 1; //Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

            }

            else
            {
                if (nrvec(i, j) < 2)
                    urm[i][j] = 0;//Any live cell with fewer than two live neighbors dies, as if caused by under population.

                if (nrvec(i, j) > 3)
                    urm[i][j] = 0; //Any live cell with more than three live neighbors dies, as if by overpopulation.
            }

        }
    std::swap(act, urm);  // interschimbare intre matricea actuala si matricea de la pasul urmator

}

void::CellGrid::display(sf::RenderWindow& window, sf::RectangleShape& cell, int& dim)
{
    //display 
    
    
    for (int i = 0; i < lin; i++)
    {   
        for (int j = 0; j < col; j++)
        {
            if(!act[i][j]) continue ;
            else {
                cell.setPosition(j * (dim + 0.5), i * (dim + 0.5));


                if (nrvec(i, j) >= 2)
                    cell.setFillColor(sf::Color::Cyan);
                else
                    cell.setFillColor(sf::Color::White);

                window.draw(cell);
            }





        }
    }



    window.display();
    window.clear();
}



void CellGrid::game(int dim)
{
    sf::Music menu_music;
    menu_music.openFromFile("../extras/menu_music.wav");
    menu_music.setLoop(true);
    menu_music.setVolume(20);
    menu_music.play();

   
    sf::SoundBuffer sb;
    sb.loadFromFile("../extras/menu_select.wav");
    sf::Sound select_sound;
    select_sound.setBuffer(sb);
    select_sound.setVolume(30);

    bool exit = 0;
    sf::RenderWindow window2(sf::VideoMode(w, h), "Game of life - Main Menu", sf::Style::Fullscreen);
    Menu menu(w, h);
    while (window2.isOpen())
    {   
        sf::Event event;


        while (window2.pollEvent(event))
        {
            menu.draw(window2);
            window2.display();
            window2.clear();
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp(), select_sound.play();
                    
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown(), select_sound.play();
                    
                    break;
                case sf::Keyboard::Escape:
                    window2.close(), exit = 1; break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:

                        init(), window2.close();
                        break;
                    case 1:
                        init_rand(), window2.close();
                        break;
                    case 2:
                        window2.close(), exit = 1;
                        break;

                    }

                    break;
                }
                menu.draw(window2);
                window2.display();
                window2.clear();



            }

        }




        if (!window2.isOpen() && exit != 1)
        {
            sf::Music music;
            music.openFromFile("../extras/game_music.wav");
            music.setLoop(true);
            music.setVolume(20);
            menu_music.stop();
            music.play();

            sf::RenderWindow window(sf::VideoMode(w, h), "Game of life", sf::Style::Fullscreen);
            sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(w, h));
            view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);   // camera
            sf::View view_init = view;  // original de referinta 
            sf::View view_check = view; // auxiliar
            window.setView(view);
            sf::RectangleShape cell(sf::Vector2f((float)dim, (float)dim));           //celula
            sf::Sprite fundal;
            sf::Texture texture;
            texture.loadFromFile("../extras/bg.jpg");   //fundal
            fundal.setTexture(texture);
            fundal.setOrigin(0, 0);
            

            bool run = true;
            while (window.isOpen())
            {
                
                sf::Event event;


                while (window.pollEvent(event))
                {

                    if (event.type == sf::Event::Closed)
                    {

                        window.close();

                    }
                }


                


                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                { // adaugare manuala de celule  
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    int px = worldPos.x / (dim + 0.5);
                    int py = worldPos.y / (dim + 0.5);
                    add(py, px);


                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                { // stergere manuala de celule  
                    
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    int px = worldPos.x / (dim + 0.5);
                    int py = worldPos.y / (dim + 0.5);
                    del(py, px);

                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    view.zoom(0.99f);
                    window.setView(view);
                          //zoom in
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    sf::View view_check = view;

                    view_check.zoom(1.01f);
                    if (view_check.getCenter().y + view_check.getSize().y / 2.0 <= view_init.getCenter().y + view_init.getSize().y / 2.0
                        && view_check.getCenter().y - view_check.getSize().y / 2.0 >= view_init.getCenter().y - view_init.getSize().y / 2.0
                        && view_check.getCenter().x + view_check.getSize().x / 2.0 <= view_init.getCenter().x + view_init.getSize().x / 2.0
                        && view_check.getCenter().x - view_check.getSize().x / 2.0 >= view_init.getCenter().x - view_init.getSize().x / 2.0
                        )
                        // zoom out
                    {
                        view = view_check;
                        window.setView(view);
                    }
                   
                }                                        


                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::G:
                        run = true;  //start
                        break;

                    case sf::Keyboard::Space:   //pauza
                        run = false;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();             //exit
                        break;
                    case sf::Keyboard::R:
                        view = view_init, window.setView(view);   // reset camera
                        break;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                {

                    view_check = view;
                    view_check.move(0.f, -4.f);
                    if ( view_check.getCenter().y - view_check.getSize().y / 2.0 >= view_init.getCenter().y - view_init.getSize().y / 2.0)
                    {
                        view = view_check;
                        window.setView(view);
                    }

                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                {
                    view_check = view;
                    view_check.move(-4.f, 0.f);
                    if (view_check.getCenter().x - view_check.getSize().x / 2.0 >= view_init.getCenter().x - view_init.getSize().x / 2.0)
                    {
                        view = view_check;
                        window.setView(view);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    view_check = view;
                    view_check.move(0.f, 4.f);
                    if (view_check.getCenter().y + view_check.getSize().y / 2.0 <= view_init.getCenter().y + view_init.getSize().y / 2.0)
                    {
                        view = view_check;
                        window.setView(view);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                     view_check = view;
                    view_check.move(4.f, 0.f);
                    if (view_check.getCenter().x + view_check.getSize().x / 2.0 <= view_init.getCenter().x + view_init.getSize().x / 2.0)
                    {
                        view = view_check;
                        window.setView(view);
                    }
                }
               

                if (run)    
                    next();
                

                window.draw(fundal);
                display(window, cell, dim);



            }

        }
    }
}