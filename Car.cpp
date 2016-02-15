#include "Car.h"
#include "Jukebox.h"
#include <GL/glut.h>    /* glut.h includes gl.h and glu.h */
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include <iostream>

#include "ImageLoader.h" 
#include "Game.h"

class ImageLoader;

void Car::left ()
{
   if(!stopleft){
   	if(Game::getInstance().getArrayPos() == 3 || Game::getInstance().getArrayPos() == 1){
      	m_arraypos = Game::getInstance().getArrayPos() +1;
   	}
   	else{
      	m_arraypos = Game::getInstance().getArrayPos() - 1;
   	}
      
   	if(m_x-5 <= 0)
   	{
      	if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 1){
         	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_x = 968 ;
      	}
   	}else{
	   	m_x -= 4*m_speed;//50
   	}
   }
   m_direction = 3;
   m_carTexture= ImageLoader::LoadTexture( "./imgs/Left.bmp" );
}
void Car::right ()
{
   if(!stopright){
   	if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 3){
      	m_arraypos = Game::getInstance().getArrayPos() +1;
   	}
   	else{
      	m_arraypos = Game::getInstance().getArrayPos() - 1;
   	}

   	if(m_x+55 >= 1023)
   	{
      	if(Game::getInstance().getArrayPos() != 2 && Game::getInstance().getArrayPos() != 4){
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_x = 5;
      	}
   	}else{
			m_x += 4*m_speed;
   	}
   }
   m_direction = 1;
   m_carTexture= ImageLoader::LoadTexture( "./imgs/Right.bmp" );
}
void Car::up ()
{
   if(!stopup){
   	if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 2){
      	m_arraypos = Game::getInstance().getArrayPos() +2;
   	}
   	else{
      	m_arraypos = Game::getInstance().getArrayPos() - 2;
   	}

  		if(m_y+60 >= 731)
  		{
      	if(Game::getInstance().getArrayPos() != 1 && Game::getInstance().getArrayPos() != 2){
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_y = 5;
     		}
  		}else{
			m_y +=4*m_speed;
		}
   }
   m_direction = 0;
	m_carTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}
void Car::down ()
{
   if(!stopdown){
   	if(Game::getInstance().getArrayPos() == 1 || Game::getInstance().getArrayPos() == 2){
      	m_arraypos = Game::getInstance().getArrayPos() +2;
   	}
   	else{
      	m_arraypos = Game::getInstance().getArrayPos() - 2;
   	}

  		if(m_y-5 <= 0)
  		{
      	if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 4){
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_y = 676;
      	}
   	}else{
			m_y -= 4 * m_speed;
  		}
   }
   m_direction = 2;
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
void Car::update (Obstacle *ob[],int size,int quad)
{
   for(int i=0;i<size;i++){
      int xpos = ob[i]->getX();
      int ypos = ob[i]->getY();
      int width = ob[i]->getW();
      int height = ob[i]->getH();
      int cond = ob[i]->getC();

      collisions(xpos, ypos, width, height, cond,quad);
      if(stopright == true || stopleft == true||stopup==true||stopdown==true)
      	break;   
   }
}

void Car::collisions(int xpos, int ypos, int width, int height, int cond,int quad)
{
	int quadrant = Game::getInstance().getArrayPos();
	if(quadrant == quad && height > 0){
      if(m_x+5+m_size > xpos && m_x < xpos + width && m_y+m_size > ypos && m_y < ypos+height){
         stopright = true;
         m_x -=4;
      }else if(m_x+m_size > xpos && m_x-5 < xpos + width && m_y+m_size > ypos && m_y < ypos+height){
         stopleft = true;
         m_x+=4;
      }else if(m_y-5 < ypos+height  && m_y > ypos && m_x +m_size > xpos && m_x < xpos+width){
         stopdown = true;
         m_y+=4;
      }else if(m_y+m_size+5> ypos && m_y < ypos+height && m_x+m_size > xpos && m_x < xpos+width){
         stopup = true;
         m_y-=4;
      }else{
         stopright = false;
         stopleft = false;
         stopup = false;
         stopdown = false;
      }
	}else if(quadrant == quad && height == 0){
		float circledistancex = abs(xpos - (m_x + (m_size/2)));
		float circledistancey = abs(ypos - (m_y + (m_size/2)));
		float corner = pow((circledistancex - m_size/2),2) +
							pow((circledistancey - m_size/2),2);
		//float corner = pow(circledistancex,2) + pow(circledistancey,2);
		//corner = sqrt(corner);
		if(circledistancex > (m_size/2 + width)){	
			//m_speed = 1;
			stopup = false;
      	stopdown = false;
      	stopleft = false;
      	stopright = false;
		}else if(circledistancey > (m_size/2 + width)){	
			//m_speed = 1;
			stopup = false;
      	stopdown = false;
      	stopleft = false;
      	stopright = false;
		}else if(circledistancex <= (m_size/2)){
      	//m_speed = 0.5;
      	if(c_up){
      				//stopup = true;
      				//stopdown = false;
      				//stopleft = false;
      				//stopright = false;
      				m_y -=4;
      	}
      	if(c_right){
      				//stopright = true;
      				//stopleft=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x -=4;
      	}
      	if(c_down){
      				//stopdown = true;
      				//stopup=false;
      				//stopright=false;
      				//stopleft=false;
      				m_y +=4;
      	}
      	if(c_left){
      				//stopleft = true;
      				//stopright=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x +=4;
      	}
		}else if(circledistancey <= (m_size/2)){
			//m_speed = 0.5;
			if(c_up){
      				//stopup = true;
      				//stopdown = false;
      				//stopleft = false;
      				//stopright = false;
      				m_y -=4;
      	}
      	if(c_right){
      				//stopright = true;
      				//stopleft=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x -=4;
      	}
      	if(c_down){
      				//stopdown = true;
      				//stopup=false;
      				//stopright=false;
      				//stopleft=false;
      				m_y +=4;
      	}
      	if(c_left){
      				//stopleft = true;
      				//stopright=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x +=4;
      		}
		//}else if(corner <= width + sqrt(pow(m_size/2,2)+pow(m_size/2,2))){
		}else if(corner <=pow(width,2)){
			//m_speed = 0.5;
      	if(c_up){
      				//stopup = true;
      				//stopdown = false;
      				//stopleft = false;
      				//stopright = false;
      				m_y -=4;
      	}
      	if(c_right){
      				//stopright = true;
      				//stopleft=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x -=4;
      	}
      	if(c_down){
      				//stopdown = true;
      				//stopup=false;
      				//stopright=false;
      				//stopleft=false;
      				m_y +=4;
      	}
      	if(c_left){
      				//stopleft = true;
      				//stopright=false;
      				//stopup=false;
      				//stopdown=false;
      				m_x +=4;
      	}
		}
     
     
     /*
     if(m_direction == 0){
      				stopup = true;
      				stopdown = false;
      				stopleft = false;
      				stopright = false;
      				m_y -=5;
      		}else if(m_direction == 1){
      				stopright = true;
      				stopleft=false;
      				stopup=false;
      				stopdown=false;
      				m_x -=5;
      		}else if(m_direction == 2){
      				stopdown = true;
      				stopup=false;
      				stopright=false;
      				stopleft=false;
      				m_y +=5;
      		}else if(m_direction == 3){
      				stopleft = true;
      				stopright=false;
      				stopup=false;
      				stopdown=false;
      				m_x +=5;
      		}
     */
     
     
     
     
     
     	/*for(int i = 0; i<200;i++){
      	double angle = 2*i*M_PI/200;
      	float newX = xpos + width*cos(angle);
      	float newY = ypos + width*sin(angle);
      	
      	
      	if(newX+5 > m_x && newX < m_x+m_size && newY > m_y && newY < m_y+m_size){
      		stopleft = true;
      	}else if(newX-5 < m_x+m_size && newX > m_x && newY > m_y && newY < m_y+m_size){
      		stopright = true;
      	}else if(newY-5 < m_y+m_size && newY > m_y && newX > m_x && newX < m_x+m_size){
      		stopup = true;
      	}else if(newY+5 > m_y && newY < m_y+m_size && newX> m_x && newX < m_x+m_size){
      		stopdown = true;
      	}else{
         	stopright = false;
         	stopleft = false;
         	stopup = false;
         	stopdown = false;
      	}
      	if(stopright == true || stopleft == true||stopup==true||stopdown==true)
      		break;
      	/*
      	
      	/*if(newX+5 > m_x && newX-5 < m_x+m_size && newY+5 > m_y && newY-5 < m_y+m_size){
      		if(m_direction == 0){
      				stopup = true;
      		}else if(m_direction == 1){
      				stopright = true;
      		}else if(m_direction == 2){
      				stopdown = true;
      		}else if(m_direction == 3){
      				stopleft = true;
      		}else{
      			stopup = false;
					stopright = false;
					stopdown = false;	
					stopleft = false;
      		}
      	}
      }*/
	}
}

void Car::init()
{
  m_carTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}


Car::Car(int x, int y)
{
	c_up=false;
	c_down=false;
	c_left=false;
	c_right=false;
   m_x=x;
   m_y=y;
   m_direction = 2;
   m_arraypos = 0;
   m_speed = 1;
   m_size = 48;
   stopright=false;
   stopleft=false;
   stopup=false;
   stopdown=false;
}

