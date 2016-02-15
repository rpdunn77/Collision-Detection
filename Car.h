#ifndef CAR_H_
#define CAR_H_

//#include "Jukebox.h"
#include <GL/freeglut.h>
#include "Obstacle.h"
class Obstacle;

class Car {  
   private:
    int m_x;  
    int m_y; 
    int m_size;
    float m_direction;
    float m_speed;
    
    bool stopup,stopdown,stopright,stopleft;

    GLuint m_carTexture;   

   public:
    void left ();
    void right ();
    void up ();
    void down ();
    void attack ();
    void honk ();
    void display ();
    void displayTexture ();
    void update (Obstacle *obstacle[],int size);
    void collisions(int xpos, int ypos, int width, int height, int cond);
    void init();
    Car(int x = 260, int y = 170);
};

#endif /* CAR_H_ */
