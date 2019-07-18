//////////////////////////////////////////////////////////////////////////////////////////
// externals 
//////////////////////////////////////////////////////////////////////////////////////////
extern void winReshapeFunc(GLint w, GLint h);
extern void renderScene();
extern void update();

//////////////////////////////////////////////////////////////////////////////////////////
// constants 
//////////////////////////////////////////////////////////////////////////////////////////
const int SCREEN_WIDTH	= 500;
const int SCREEN_HEIGHT = 500;

const int PASSES		= 3;

typedef unsigned int	u32	;

//////////////////////////////////////////////////////////////////////////////////////////
// structures 
//////////////////////////////////////////////////////////////////////////////////////////
struct sRGB
{
	float r, g, b;
};
