#include "Player.h"
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

void Player::left ()
{
   if(!stopleft){
      m_arraypos = Game::getInstance().getArrayPos();
    
   	if(m_x-5 <= 0)
   	{
      	if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 1){
      		m_arraypos -= 1;
         	Game::getInstance().changeScreen(m_arraypos);//change screen picture
         	Game::getInstance().setArrayPos(m_arraypos);//set new arraypos
	      	m_x = 968 ;//set x pos to other side of screen
      	}
   	}else{
	   	m_x -= 4*m_speed;
   	}
   }
   m_direction = 3;
   m_PlayerTexture= ImageLoader::LoadTexture( "./imgs/Left.bmp" );
}
void Player::right ()
{
   if(!stopright){
      m_arraypos = Game::getInstance().getArrayPos();

   	if(m_x+55 >= 1023)
   	{
      	if(Game::getInstance().getArrayPos() != 2 && Game::getInstance().getArrayPos() != 4){
      		m_arraypos +=1;
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_x = 5;
      	}
   	}else{
			m_x += 4*m_speed;
   	}
   }
   m_direction = 1;
   m_PlayerTexture= ImageLoader::LoadTexture( "./imgs/Right.bmp" );
}
void Player::up ()
{
   if(!stopup){
      m_arraypos = Game::getInstance().getArrayPos();

  		if(m_y+60 >= 731)
  		{
      	if(Game::getInstance().getArrayPos() != 1 && Game::getInstance().getArrayPos() != 2){
      		m_arraypos-=2;
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_y = 5;
     		}
  		}else{
			m_y +=4*m_speed;
		}
   }
   m_direction = 0;
	m_PlayerTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}
void Player::down ()
{
   if(!stopdown){
      m_arraypos = Game::getInstance().getArrayPos();

  		if(m_y-5 <= 0)
  		{
      	if(Game::getInstance().getArrayPos() != 3 && Game::getInstance().getArrayPos() != 4){
      		m_arraypos +=2;
	      	Game::getInstance().changeScreen(m_arraypos);
         	Game::getInstance().setArrayPos(m_arraypos);
	      	m_y = 676;
      	}
   	}else{
			m_y -= 4 * m_speed;
  		}
   }
	m_direction = 2;
  	m_PlayerTexture= ImageLoader::LoadTexture( "./imgs/Down.bmp" );
}
void Player::attack ()
{
	//will be used for final
}

void Player::display ()
{
   displayTexture ();
}

void Player::displayTexture ()
{
   // Draw the Player
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture (GL_TEXTURE_2D, m_PlayerTexture);
   ImageLoader::rectangle(m_x,m_y, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glFlush();

}
void Player::update (Obstacle *ob[],int size,int quad)
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

void Player::collisions(int xpos, int ypos, int width, int height, int cond,int quad)
{
	int quadrant = Game::getInstance().getArrayPos();
	if(quadrant == quad && height > 0){
      //********************** TODO 1 **********************//
      //******* Implement up, down, left stoping     *******//
      //******* HINTS:                               *******//
      //*******      xpos & ypos start bottom left   *******//
      //*******      of the rectangles, these values *******//
      //*******      are already coded in.           *******//
      //*******                                      *******//
      //*******      for +5 in the below "m_x+5"     *******//
      //*******      the +5 is used to determine     *******//
      //*******      if the next movement in that    *******//
      //*******      direction will be a collision   *******//
      //*******      if so, stop%direction% = true   *******//
      //******* WHY:                                 *******//
      //*******  	   This method is using a similar  *******//
      //*******  		method as Dr. J's to check if   *******//
      //*******  		the two boxes are colliding     *******//
      //****************************************************//
      if(m_x+5+m_size > xpos && m_x < xpos + width && m_y+m_size > ypos && m_y < ypos+height){
         stopright = true; //determines whether or not player can move right
         m_x-=4;           //this fixes clipping issues when moving diagonal
		}/*start code task 1*/		
		
				
				/*Your Code Here*/


		/*end code task 1*/
		else{//not at any collision point
			stopright = false;
			stopleft = false;
			stopup = false;
			stopdown = false;
		}
	//the if height == 0 means that this is a circle
	//and width should be used as radius
	}else if(quadrant == quad && height == 0){
      //********************** TODO 3 **********************//
      //******* Decrease the speed of the player     *******//
      //******* when colliding with the lake(circle) *******//
      //******* by half. 								     *******//
      //*******                                      *******//
      //******* HINT:  										  *******//
      //*******  	There is a speed variable that is  *******//
      //*******  	multiplied by the distance moved	  *******//
      //*******  	when player is travelling in the   *******//
      //*******  	proper directions. 					  *******//
      //*******  												  *******//
      //******* WHY:											  *******//
      //*******  	Collision detection does not only  *******//
      //*******  	include the stopping of a player.  *******//
      //*******  	In this case, it can simulate 	  *******//
      //*******  	travelling through a shallow lake. *******//
      //****************************************************//

		//****************************************************//      
      //*******    The logic and code for Circle     *******//
      //*******    was found here:						  *******//
      //******* http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection 										  *******//
      //*******	UserName: e.James                  *******//
      //*******   This code was slightly modified to *******//
      //*******   suit the needs of this Lab         *******//
      //****************************************************//
      
      
      
		float circleDistanceX = abs(xpos - (m_x + (m_size/2)));
		float circleDistanceY = abs(ypos - (m_y + (m_size/2)));
		float corner = pow((circleDistanceX - m_size/2),2) +
							pow((circleDistanceY - m_size/2),2);
		if(circleDistanceX > (m_size/2 + width)){	//did not collide
			m_speed = 1;
		}else if(circleDistanceY > (m_size/2 + width)){	//did not collide
			m_speed = 1;
		}else if(circleDistanceX <= (m_size/2)){ //collided
		
		
		
		
		//***************EXTRA CODE TO PLAY WITH**************//
		//*******  This is some extra code you can use *******//
		//*******  to test your circle collision with  *******//
		//*******  stopping. Sometimes it is difficult *******//
		//*******  to determine if objects are         *******//
		//*******  accurately colliding with only slow *******//
		//*******  movement.  								  *******//
		//*******  												  *******//
		//*******  You can also use this as a guide to *******//
		//*******  see a seperate method of making     *******//
		//*******  your sprite stop.						  *******//
		//*******  Place in all places that use collide*******//
		//*******  for the circle. 						  *******//
		//****************************************************//
		
		   /*if(c_up){
      		m_y -=4;
      	}
      	if(c_right){
      		m_x -=4;
      	}
      	if(c_down){
      		m_y +=4;
      	}
      	if(c_left){
      		m_x +=4;
      	}*/
		
		//********************** TODO 2 **********************//
      //*******  Using the above example: 			  *******//
      //*******  	 if(circleDistanceX <= (m_size/2)) *******//
      //*******  write the equivalent code using     *******//
      //*******  circleDistanceY.                    *******//
      //*******  Then using the corner variable      *******//
      //*******  compare the point on the circle     *******//
      //*******  that the corner of the square will  *******//
      //*******  collid with.                        *******//
      //*******  												  *******//
      //*******  HINT:									  	  *******//
      //*******     corner is defined above using    *******//
      //*******     the pythagorean theorem  to find *******//
      //*******     the point on the circle that the *******//
      //*******  	  square collides with.            *******//
      //*******                                      *******//
      //*******     Radius is defined as width       *******//
      //*******     this is so we could reuse the    *******//
      //*******     same parameters without creating *******//
      //*******     another version of Obsticle class*******//
      //*******                                      *******//
      //*******     corner was not squarerooted at   *******//
      //*******     the end in order to run faster,  *******//
      //*******     use your comparison ^2 instead.  *******//
      //*******  												  *******//
      //*******  WHY:                                *******//
      //*******  First is checking if the y distance *******//
      //*******  from center of the circle is in the *******//
      //*******  square.                             *******//
      //*******  Second is checking if the distance  *******//
      //*******  from one of the corners of the      *******//
      //*******  square is colliding with the circle *******//
      //*******  												  *******//
      //****************************************************//
      }else if(1/*Your code here task 2 part 1*/){//collided
      	/*Your code here task 3*/
		
		}else if(1/*Your code here task 2 part 2*/){//collided
			/*Your code here task 3*/
		}
	}
}

void Player::init()
{
  m_PlayerTexture= ImageLoader::LoadTexture( "./imgs/Up.bmp" );
}


Player::Player(int x, int y)
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

