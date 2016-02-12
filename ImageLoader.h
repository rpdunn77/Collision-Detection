#ifndef IMAGE_LOADER_H_
#define IMAGE_LOADER_H_


class ImageLoader {  
   private:

   public:
    static GLuint LoadTexture( const char * filename );
    static void drawBox(GLfloat size, GLenum type, int x, int y, int xangle, int yangle);
    static void RenderString(float x, float y, void *font, const char* string);
    static void arc(GLfloat x, GLfloat y, GLfloat r, int n, int s, int e);
    static void circle(GLfloat x, GLfloat y, GLfloat r, int n);
    static void rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height); 
    static void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness=5.0);
};

#endif /* IMAGE_LOADER_H_ */
