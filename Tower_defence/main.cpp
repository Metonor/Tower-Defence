#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
class Global : public sf::Sprite{
public:
    virtual void Animuj(sf::Time &elapsed)=0;
    float x;
    float y;
    enum typ{Pacman,Towers,Mobs,Mapa};
    int type;
    int wave=0;

};
class PacMan : public Global
{public:

    PacMan(sf::Texture &a)
    {
        setTexture(a);
        setPosition(400,300);
        x=0;
        y=0;
        type = typ::Pacman;
        zycia=3;
        punkty=0;
    }
    int zycia;
    int punkty;
    void Animuj(sf::Time &elapsed)
    {
        move(x,y);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            y=-1;
            x=0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            y=1;
            x=0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            y=0;
            x=-1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            y=0;
            x=1;
        }

    }
};
class Mobs : public Global
{public:
    int point=0;
    int speed=50;
    Mobs(sf::Texture &a)
    {
        setTexture(a);
        setPosition(-45,310);
        x=(rand()%30)*3;
        y=0;
        setScale(1,1);
        type = typ::Mobs;
    }
    void Animuj(sf::Time &elapsed)
    {

            auto object_bounds = this->getGlobalBounds();
                if((object_bounds.left > 125)&& point==0)
                {
                    x=0;
                    y=-speed;
                    point=1;

                }
                if((object_bounds.top < 130)&& point==1)
                {
                    x=speed;
                    y=0;
                    point=2;
                }
                if((object_bounds.left > 310)&& point==2)
                {
                    x=0;
                    y=speed;
                    point=3;
                }
                if((object_bounds.top > 370)&& point==3)
                {
                    x=speed;
                    y=0;
                    point=4;
                }

                if((object_bounds.left > 555)&& point==4)
                {
                    x=0;
                    y=-speed;
                    point=5;
                }

                if((object_bounds.top < 260)&& point==5)
                {
                    x=speed;
                    y=0;
                    point=0;
                }

 move(x*elapsed.asSeconds(),y*elapsed.asSeconds());
        }

};
class Towers:public Global
{public:

    Towers(sf::Texture &a)
    {
        setTexture(a);
        x=0;
        y=0;
        setScale(0.5,0.5);
        type = typ::Towers;
    }
    void Animuj(sf::Time &elapsed)
    {
        move(0,y*elapsed.asSeconds());
    }
};

class Mapa:public Global
{
public:
    Mapa(sf::Texture &a)
    {
        setTexture(a);
        setScale(1.5,1.5);
        type = typ::Mapa;
    }
    void Animuj(sf::Time &elapsed)
    {

    }

};



//

//

//

//

//
int main()
{
    srand(time(NULL));

        sf::RenderWindow window(sf::VideoMode(800,600),"programik");
        window.setFramerateLimit(120);
        //      Tekstury
        sf::Texture map_tx;
        sf::Texture Duch_tx;
        sf::Texture Knight_tx;
        sf::Texture Slime_tx;
        sf::Texture Pacman_tx;
        sf::Texture Tower1_tx;
        if (!Duch_tx.loadFromFile("tekstury/duch.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Knight_tx.loadFromFile("tekstury/knight.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Slime_tx.loadFromFile("tekstury/slime.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Pacman_tx.loadFromFile("tekstury/pacman.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Tower1_tx.loadFromFile("tekstury/Mech1A.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!map_tx.loadFromFile("tekstury/map1.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }

        Mapa map1(map_tx);


        //__________________________________

        //

        int tower_number = 0;
        PacMan hero(Pacman_tx);
        std::vector<std::unique_ptr<Global>> obiekty;
        std::vector<std::unique_ptr<Towers>> towers;
        sf::Clock clock;
        for(int i=0;i<10;i++)
        {

            obiekty.emplace_back(new Mobs(Duch_tx));

        }


        while (window.isOpen())
            {



                sf::Time elapsed = clock.restart();
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();


                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if(event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                            std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                        }
                    }
                }
               /* p=obiekty.begin();
                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    if(obiekty[i]->getPosition().y>800)
                    {
                        if(obiekty[i]->type==Global::typ::duch)
                        {
                            obiekty.emplace_back(new Duch(Duch_tx));
                        }
                        else
                        {
                            obiekty.emplace_back(new Owoc(Owoc_tx));
                        }
                        obiekty.erase(p+i);
                        iloscspadania--;
                    }
                }
                p=obiekty.begin();
                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    if(hero.getGlobalBounds().intersects(obiekty[i]->getGlobalBounds()))
                    {
                        if(obiekty[i]->type==Global::typ::duch)
                        {
                            //obiekty.emplace_back(new Duch(Duch_tx));
                            hero.zycia--;
                            hero.setPosition(400,300);
                             std::cout<<std::endl<<"HP left::"<<hero.zycia<<std::endl;
                        }
                        else
                        {
                            //obiekty.emplace_back(new Owoc(Owoc_tx));
                            hero.punkty+=100;
                            std::cout<<std::endl<<"PUNKTY::"<<hero.punkty<<std::endl;
                        }
                        obiekty.erase(p+i);

                    }
                }
                */
                if (event.type == sf::Event::MouseButtonPressed) {
                    if(event.mouseButton.button == sf::Mouse::Right) {


                   sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    towers.emplace_back(new Towers(Tower1_tx));
                   towers[tower_number]->setPosition(mouse_pos.x-40,mouse_pos.y-25);
                    std::cout<<"deploy";
                    tower_number++;



                }
                }



      }//While end

                window.clear();
                window.draw(map1);
                window.draw(hero);
                hero.Animuj(elapsed);
                for(unsigned int i=0;i<towers.size();i++){
                    window.draw(*towers[i]);
                }
                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    window.draw(*obiekty[i]);

                }
                for(auto &p:obiekty)
                {
                    p->Animuj(elapsed);
                }
                window.display();


}//window open
}//main end
