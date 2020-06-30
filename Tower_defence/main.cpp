#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include<math.h>
#include<cstdlib>
#include <stdlib.h>


class Global : public sf::Sprite{
public:
    virtual void Animuj(sf::Time &elapsed)=0;
    virtual int  Get_HP()=0;
    virtual void DMG()=0;
    float x;
    float y;
    int HP;
    enum typ{Towers,Ghost,Knight,Mapa};
    int type;


};

class Ghost : public Global
{public:
    int point=0;
    int speed=120;
    int HP=4;
    Ghost(sf::Texture &a)
    {
        setTexture(a);
        setPosition(0,310);
        x=100;
        y=0;
        HP=7;
        setScale(1,1);
        type = typ::Ghost;
    }
    int Get_HP(){

        return HP;
    }
    void DMG(){
        this->HP=HP-1;
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
class Knight : public Global
{public:
    int point=0;
    int speed=60;
    int HP=15;
    Knight(sf::Texture &a)
    {
        setTexture(a);
        setPosition(0,300);
        x=50;
        y=0;
        HP=20;
        setScale(0.7,0.7);
        type = typ::Knight;
    }
    int Get_HP(){

        return HP;
    }
    void DMG(){
        this->HP=HP-1;
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
                if((object_bounds.top < 120)&& point==1)
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
                if((object_bounds.top > 360)&& point==3)
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

        setTexture(a);
        x=0;
        y=0;
        setScale(0.7,0.7);
        type = typ::Towers;
    }
    void Animuj(sf::Time &elapsed)
    {

    }
    int Get_HP(){

    }
    void DMG(){

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
    int Get_HP(){

    }
    void DMG(){

    }

};

class Bullet
{
public:
    sf::CircleShape bullet;
    sf::Vector2f currV;
    float maxV;

    Bullet(float radius =3.f) : currV(0.f,0.f), maxV(5.f)
    {
        this->bullet.setRadius(radius);
        this->bullet.setFillColor(sf::Color::Red);
    }


};

class Base : public sf::Sprite{
  public:
  Base(const sf::Texture &texture) : sf::Sprite(texture)
  {
      this->setPosition(sf::Vector2f(680,230));
      this->setScale(0.7,0.7);
  };

};

//
//

int main()
{
    srand(time(NULL));
    //Main instructions
    int gold=100;
    int cost=100;
     int Enemy_G=5;
     int Enemy_K=1;
     int E=0;
     int tower_number = 0;
     float time=0;
     float time_d=0.6f;
     int wave=0;
     int Base_HP=5;
   std::cout<<"_________________________"<<std::endl<<"Press Q to next wave when all enemies die:::"<<std::endl;
   std::cout<<"GOLD:::"<<std::endl<<gold<<std::endl;
   std::cout<<"Base_HP:::"<<std::endl<<Base_HP<<std::endl<<"_________________________"<<std::endl;
    //

        sf::RenderWindow window(sf::VideoMode(800,600),"TD");
        window.setFramerateLimit(120);

        //      Tekstury
        sf::Texture map_tx;
        sf::Texture Duch_tx;
        sf::Texture Knight_tx;
        sf::Texture Slime_tx;
        sf::Texture Base_tx;
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
        if (!Base_tx.loadFromFile("tekstury/Mech1B.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!Tower1_tx.loadFromFile("tekstury/Mech4.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        if (!map_tx.loadFromFile("tekstury/map1.png"))
        {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        //Music

           sf::Music music;
           if (!music.openFromFile("music/Cyberpunk_Moonlight_ Sonata (online-audio-converter.com).ogg"))
               return -1; // error
           music.play();

// Stale obiekty
        Mapa map1(map_tx);
        Base Baza(Base_tx);


        //__________________________________

        //


        //Vectors
        std::vector<std::unique_ptr<Global>> obiekty;
        std::vector<std::unique_ptr<Towers>> towers;
        std::vector<Bullet> ammo;
        sf::Vector2f Mouse_pos;

        //

       sf::Clock clock1;

        while (window.isOpen())
            {



                sf::Time elapsed = clock1.restart();
                time=time+elapsed.asSeconds();
                //Enemies Generator
                if(wave%2==0){
                if(time>time_d && E<Enemy_G){
                    obiekty.emplace_back(new Ghost(Duch_tx));

                    time=0;
                    E+=1;
                }
                }
                else{
                    if(time>time_d && E<Enemy_K){
                        obiekty.emplace_back(new Knight(Knight_tx));
                        time=0;
                        E+=1;
                    }
                }

              // std::cout<<time<<std::endl;


                //Shooting
                Bullet b1;


                Mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
                for(unsigned int i=0;i<towers.size();i++){
                    towers[i]->Tower_Center= sf::Vector2f(towers[i]->getPosition().x+20,towers[i]->getPosition().y+40);
                    towers[i]->aim_dir= Mouse_pos-towers[i]->Tower_Center;
                    towers[i]->aim_dir_norm= towers[i]->aim_dir/ (sqrt((towers[i]->aim_dir.x)*(towers[i]->aim_dir.x)
                                                                  +((towers[i]->aim_dir.y)*towers[i]->aim_dir.y)));
                   // std::cout<<towers[0]->aim_dir_norm.x<<" "<<towers[0]->aim_dir_norm.y<<std::endl;
                }


                //
                //      Events

                sf::Event event;
                while (window.pollEvent(event))
                {

                    if (event.type == sf::Event::Closed)
                        window.close();


//Left click mouse
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if(event.mouseButton.button == sf::Mouse::Left) {
                            //sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                         //   std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                            for(int i=0;i<tower_number;i++){
                            b1.bullet.setPosition(towers[i]->Tower_Center);
                            b1.currV= towers[i]->aim_dir_norm*b1.maxV;
                            ammo.push_back(Bullet(b1));
                        }
                           // std::cout<<ammo.size();

                        }
                   }
                    //Q click
                    if(obiekty.size()==0){

                    if (event.type == sf::Event::KeyReleased) {
                        if (event.key.code == sf::Keyboard::Q) {

                            if(time_d>=0.25f){
                                time_d-=0.05f;
                                //std::cout<<time_d;
                            }
                    //Wave up
                            if(wave%2==0){
                        Enemy_G+=8;
                        E=0;

                            }
                            else{
                                Enemy_K+=3;
                                E=0;
                            }
                        wave+=1;
                        std::cout<<"____________"<<std::endl<<"Wave:::"<<wave<<std::endl<<"____________"<<std::endl;


                 }
                }
             }





// Right click mouse+
                if (event.type == sf::Event::MouseButtonPressed) {
                    if(event.mouseButton.button == sf::Mouse::Right && gold>=cost) {


                   sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    towers.emplace_back(new Towers(Tower1_tx));
                   towers[tower_number]->setPosition(mouse_pos.x-30,mouse_pos.y-20);

                    tower_number++;
                    gold=gold-cost;
                    cost=cost+50;
                    std::cout<<"Deploy!"<<std::endl<<gold<<std::endl;


                }
                }


      }//Event while end
                for(unsigned int i=0; i<obiekty.size();i++){
                if(obiekty[i]->getPosition().x>730)
                {
                    Base_HP=Base_HP-1;
                    obiekty.erase(obiekty.begin()+i);
                    std::cout<<"Base HP::"<<Base_HP<<std::endl;

                }
                }
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

                   auto it=obiekty.begin();
                        for(unsigned int k=0;k<obiekty.size();k++)
                    {
                            if(ammo[i].bullet.getGlobalBounds().intersects(obiekty[k]->getGlobalBounds())){
                                ammo.erase(ammo.begin()+i);
                                obiekty[k]->DMG();
                                if(obiekty[k]->Get_HP()==0){
                                 if(wave%2==0){
                                obiekty.erase(obiekty.begin()+k);
                                gold=gold+5;
                                 }
                                 else{
                                      obiekty.erase(it+k);
                                      gold=gold+20;
                                 }
                                std::cout<<"Zloto::"<<gold<<std::endl;
                                break;
                                }
                                }
                            }
                        it=obiekty.begin();


                }
                }

                window.clear();
                //Draw
                window.draw(map1);
                window.draw(Baza);
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
                if(Base_HP==0){
                    window.close();
                    std::cout<<"____________"<<std::endl<<"You Lose!!!"<<std::endl<<"____________";
                }
                window.display();


}//window open
}//main end
