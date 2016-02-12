#include "Car.h"
#include "Jukebox.h"
#include <GL/glut.h>    /* glut.h includes gl.h and glu.h */
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>

#include "ImageLoader.h" 
#include "Game.h"

class ImageLoader;

void Car::left ()
{
   if(!stopleft){
   if(Game::getInstance().getArrayPos() == 3 || Game::getInstance().getArrayPos() == 1){
      m_direction = Game::getInstance().getArrayPos() +1;
   }
   else{
      m_direction = Game::getInstance().getArrayPos() - 1;
   }
      
   if(m_x-5 <= 0)
   {
      if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 1){
         Game::getInstance().changeScreen(m_direction);
         Game::getInstance().setArrayPos(m_direction);
	      m_x = 968 ;
      }
   }else{
	   m_x -= 5*m_speed;//50
   }
   }
   m_carTexture= ImageLoader::LoadTexture( "./imgs/Left.bmp" );
}
void Car::right ()
{
   if(!stopright){
   if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 3){
      m_direction = Game::getInstance().getArrayPos() +1;
   }
   else{
      m_direction = Game::getInstance().getArrayPos() - 1;
   }

   if(m_x+55 >= 1023)
   {
      if(Game::getInstance().getArrayPos() != 2 && Game::getInstance().getArrayPos() != 4){
	      Game::getInstance().changeScreen(m_direction);
         Game::getInstance().setArrayPos(m_direction);
	      m_x = 5;
      }
   }else{
	m_x += 5*m_speed;
   }
   }
   m_carTexture= ImageLoader::LoadTexture( "./imgs/Right.bmp" );
}
void Car::up ()
{
   if(!stopup){
   if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 2){
      m_direction = Game::getInstance().getArrayPos() +2;
   }
   else{
      m_direction = Game::getInstance().getArrayPos() - 2;
   }

  if(m_y+60 >= 731)
  {
      if(Game::getInstance().getArrayPos() != 1 && Game::getInstance().getArrayPos() != 2){
	      Game::getInstance().changeScreen(m_direction);
         Game::getInstance().setArrayPos(m_direction);
	      m_y = 5;
      }
  }else{
	m_y +=5*m_speed;
  }
   }
  m_carTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}
void Car::down ()
{
   if(!stopdown){
   if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 2){
      m_direction = Game::getInstance().getArrayPos() +2;
   }
   else{
      m_direction = Game::getInstance().getArrayPos() - 2;
   }

  if(m_y-5 <= 0)
  {
      if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 4){
	      Game::getInstance().changeScreen(m_direction);
         Game::getInstance().setArrayPos(m_direction);
	      m_y = 676;
      }
   }else{
	m_y -= 5 * m_speed;
  }
   }
  m_carTexture= ImageLoader::LoadTexture( "./imgs/Down.bmp" );
}
void Car::attack ()
{
  Game::getInstance().changeScreen(1);
}
void Car::honk ()
{
  Jukebox::PlaySound("./sounds/AHH.WAV");
}

void Car::display ()
{
   displayTexture ();
}

void Car::displayTexture ()
{
   // Draw the car
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture (GL_TEXTURE_2D, m_carTexture);
   ImageLoader::rectangle(m_x,m_y, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glFlush();

}
void Car::update ()
{
   collisions(); 
}

void Car::collisions()
{
   int quadrant = Game::getInstance().getArrayPos();

   if(quadrant == 4){
      if(m_x > 115 &&m_x <140 && m_y >155 && m_y <357){
         stopright = true;
      }else if(m_x <325 && m_x > 300 && m_y >155 && m_y < 360){
         stopleft = true;
      }else if(m_y > 150 && m_y < 175 && m_x < 320 && m_x >120){
         stopup = true;
      }else if(m_y < 365 && m_y > 335 && m_x < 320 && m_x > 120){
         stopdown = true;
      }else{
         stopright = false;
         stopleft = false;
         stopup = false;
         stopdown = false;
      }
      //if(m_x < 250 && m_x > 245&& m_y > 220 && m_y <320){
        // stopleft = true;
         //stopright = true;
      //}
   }
   if(quadrant == 3){
      

   }
}

void Car::init()
{
  m_carTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}


Car::Car(int x, int y)
{
   m_x=x;
   m_y=y;
   m_direction = 0; // 1.5 up 3 left 4.5 down
   m_speed = 1;
   stopright=false;
   stopleft=false;
   stopup=false;
   stopdown=false;
}

