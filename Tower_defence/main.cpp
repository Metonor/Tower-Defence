#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include<math.h>
#include<cstdlib>

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
                    point=6;
                }

 move(x*elapsed.asSeconds(),y*elapsed.asSeconds());
        }

};
class Towers:public Global
{public:
    sf::Vector2f Tower_Center;
    sf::Vector2f aim_dir;
    sf::Vector2f aim_dir_norm;
    Towers(sf::Texture &a)
    {
        setRotation(90);
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

class Bullet
{
public:
    sf::CircleShape bullet;
    sf::Vector2f currV;
    float maxV;

    Bullet(float radius =4.f) : currV(0.f,0.f), maxV(5.f)
    {
        this->bullet.setRadius(radius);
        this->bullet.setFillColor(sf::Color::Magenta);
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
    //Gold
    int gold=100;
    std::cout<<gold;
    //

        sf::RenderWindow window(sf::VideoMode(800,600),"TD");
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
        //Vectors
        std::vector<std::unique_ptr<Global>> obiekty;
        std::vector<std::unique_ptr<Towers>> towers;
        std::vector<Bullet> ammo;
        sf::Vector2f Mouse_pos;

        //

        sf::Clock clock;
        for(int i=0;i<10;i++)
        {

            obiekty.emplace_back(new Mobs(Duch_tx));

        }


        while (window.isOpen())
            {



                sf::Time elapsed = clock.restart();
                //Shooting
                Bullet b1;


                Mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
                for(unsigned int i=0;i<towers.size();i++){
                    towers[i]->Tower_Center= sf::Vector2f(towers[i]->getPosition().x-5,towers[i]->getPosition().y+40);
                    towers[i]->aim_dir= Mouse_pos-towers[i]->Tower_Center;
                    towers[i]->aim_dir_norm= towers[i]->aim_dir/ (sqrt((towers[i]->aim_dir.x)*(towers[i]->aim_dir.x)
                                                                  +((towers[i]->aim_dir.y)*towers[i]->aim_dir.y)));
                   // std::cout<<towers[0]->aim_dir_norm.x<<" "<<towers[0]->aim_dir_norm.y<<std::endl;
                }


                //
                //Events
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();


//Left click mouse
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if(event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                            std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                            for(int i=0;i<tower_number;i++){
                            b1.bullet.setPosition(towers[i]->Tower_Center);
                            b1.currV= towers[i]->aim_dir_norm*b1.maxV;
                            ammo.push_back(Bullet(b1));
                        }
                           // std::cout<<ammo.size();

                        }
                   }



// Right click mouse
                if (event.type == sf::Event::MouseButtonPressed) {
                    if(event.mouseButton.button == sf::Mouse::Right && gold>=100) {


                   sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    towers.emplace_back(new Towers(Tower1_tx));
                   towers[tower_number]->setPosition(mouse_pos.x+20,mouse_pos.y-20);

                    tower_number++;
                    gold=gold-100;
                    std::cout<<"Deploy!"<<std::endl<<gold<<std::endl;


                }
                }



      }//Event while end
                //ammo erase
                for(size_t i=0;i<ammo.size();i++){
                    ammo[i].bullet.move(ammo[i].currV.x,ammo[i].currV.y);
                    if(ammo[i].bullet.getPosition().x<0|| ammo[i].bullet.getPosition().x>window.getSize().x
                            || ammo[i].bullet.getPosition().y<0 || ammo[i].bullet.getPosition().y>window.getSize().y){
                        ammo.erase(ammo.begin()+i);
                    }
                    else
                    {
                        //enemy collison

                        for(unsigned int k=0;k<obiekty.size();k++)
                    {
                            if(ammo[i].bullet.getGlobalBounds().intersects(obiekty[k]->getGlobalBounds())){
                                ammo.erase(ammo.begin()+i);
                                obiekty.erase(obiekty.begin()+k);
                                gold=gold+20;
                                std::cout<<"Zloto::"<<gold<<std::endl;
                                break;
                            }
                        }

                }
                }

                window.clear();
                //Draw
                window.draw(map1);


                for(unsigned int i=0;i<towers.size();i++){
                    window.draw(*towers[i]);
                }

                for(unsigned int i=0;i<ammo.size();i++){
                    window.draw(ammo[i].bullet);
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
