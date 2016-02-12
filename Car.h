#ifndef CAR_H_
#define CAR_H_

//#include "Jukebox.h"
#include <GL/freeglut.h>

class Car {  
   private:
    int m_x;  
    int m_y; 
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
    void update ();
    void collisions();
    void init();
    Car(int x = 260, int y = 170);
};

#endif /* CAR_H_ */
