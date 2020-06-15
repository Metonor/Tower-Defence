#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
class Global : public sf::Sprite{
public:
    virtual void Animuj(sf::Time &elapsed)=0;
    int x;
    int y;
    enum typ{Pacman,owoc,duch,Mapa};
    int type;

};
class PacMan : public Global
{public:

    PacMan(sf::Texture &a)
    {
        setTexture(a);
        setPosition(400,300);
        x=1;
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
class Duch : public Global
{public:
    Duch(sf::Texture &a)
    {
        setTexture(a);
        setPosition(rand()%800,rand()%600);
        x=(rand()%5-1)*25;
        y=0;
        setScale(1,1);
        type = typ::duch;
    }
    void Animuj(sf::Time &elapsed)
    {
        move(x*elapsed.asSeconds(),y);
        if(getGlobalBounds().left+getGlobalBounds().width>500)
        {
            x=-std::abs(x);
        }
        if(getGlobalBounds().left<0)
        {
            x=std::abs(x);
        }
        {
            move(x*elapsed.asSeconds(),y*elapsed.asSeconds());
            auto object_bounds = this->getGlobalBounds();
                if(object_bounds.left < 0)
                {
                    int ys = getPosition().y;
                    setPosition(0,ys);
                }

                if(object_bounds.left+object_bounds.width > 800)
                {
                    int ys = getPosition().y;
                    setPosition(800,ys);
                }


        }
    }
};
class Owoc:public Global
{public:
    Owoc(sf::Texture &a)
    {
        setTexture(a);
        setPosition(rand()%800,rand()%600);
        y=5;
        setScale(1,1);
        type = typ::owoc;
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
    int iloscspadania=3;
        sf::RenderWindow window(sf::VideoMode(800,600),"programik");
        window.setFramerateLimit(120);
        //      Tekstury
        sf::Texture map_tx;
        sf::Texture Duch_tx;
        sf::Texture Pacman_tx;
        sf::Texture Owoc_tx;
        if (!Duch_tx.loadFromFile("tekstury/duch.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Pacman_tx.loadFromFile("tekstury/pacman.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Owoc_tx.loadFromFile("tekstury/owoc.png"))
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

        PacMan hero(Pacman_tx);
        std::vector<std::unique_ptr<Global>> obiekty;
        sf::Clock clock;
     /*   for(int i=0;i<20;i++)
        {
            obiekty.emplace_back(new Duch(Duch_tx));

        }
        for(int i=0;i<5;i++)
        {
            obiekty.emplace_back(new Owoc(Owoc_tx));
        }
        */
        int klatka = 0;
        while (window.isOpen())
            {

                sf::Time elapsed = clock.restart();
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                auto p=obiekty.begin();
                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if((mouse_pos.x > obiekty[i]->getGlobalBounds().left)&&(mouse_pos.x < obiekty[i]->getGlobalBounds().left + obiekty[i]->getGlobalBounds().width)&&(mouse_pos.y > obiekty[i]->getGlobalBounds().top)&&(mouse_pos.y < obiekty[i]->getGlobalBounds().top + obiekty[i]->getGlobalBounds().height))
                            {
                            float scale =1;
                                if(obiekty[i]->type==Global::typ::duch)
                                {

                                }
                                else
                                {
                                    scale+=1;
                                    obiekty[i]->setScale(scale,scale);
                                }

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
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                {
                    sf::Vector2f point(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                    sf::Vector2f totalMovement(sf::Mouse::getPosition(window).x
                        - hero.getPosition().x, sf::Mouse::getPosition(window).y - hero.getPosition().y);

                    hero.move(totalMovement * (1.f / 30.f));

                }
             /*   if(hero.zycia<=0)
                {
                    std::cout<<"Koniec gry Koniec Zyc"<<std::endl;
                    //return 1;
                    window.close();
                }
                if(hero.punkty==500)
                {
                    std::cout<<"WYGRANA ! ! ! "<<std::endl;
                    //return 1;
                    window.close();
                }
            */
                window.clear();
                window.draw(map1);
                window.draw(hero);
                hero.Animuj(elapsed);
                for(unsigned int i=0;i<obiekty.size();i++)
                {
                    window.draw(*obiekty[i]);
                }
                for(auto &p:obiekty)
                {
                    p->Animuj(elapsed);
                }
                window.display();
                klatka++;
            }
}
