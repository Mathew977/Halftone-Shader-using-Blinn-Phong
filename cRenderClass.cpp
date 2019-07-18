// cRenderClass.cpp
// 
//////////////////////////////////////////////////////////////////////////////////////////
// includes 
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Declarations 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass graphics( SCREEN_WIDTH, SCREEN_HEIGHT );

unsigned int	m_tex[256];

float angle = 0;

float angleIncrease = 1.0;

int halftoneSize;

void keyboardread(unsigned char key, int x, int y)
{
	system("CLS");

	int halfIncrease = 0;

	switch (key) {
	case '+':
		halfIncrease++; //Move Camera right
		break;
	case '-':
		halfIncrease--; //Move Camera left
		break;
	}

	halftoneSize += halfIncrease;

	if (halftoneSize > 25)
		halftoneSize = 25;
	if (halftoneSize < 2)
		halftoneSize = 2;

	printf("Current Halftone Circle Size: %d\n", halftoneSize);

	printf("Press + to increase the size of the circles by 1\n");

	printf("Press - to decrease the size of the circles by 1\n");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////////////
// cRenderClass() - constructor 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass::cRenderClass(const int w, const int h)
{
	m_sw = w;
	m_sh = h;

	int total_count = w*h*4;

	m_buffer = new float[total_count];

	for( int i=0; i<total_count; i++ )
	{
		m_buffer[i] = 1;
	}
	
	m_point_size = 1;

	char halfInput[32];

	printf("Enter the size of the circles for the halftone shader (MAX = 25) (MIN = 2)\n");

	scanf("%s", halfInput);

	halftoneSize = atoi(halfInput);

	printf("Press + to increase the size of the circles by 1\n");

	printf("Press - to decrease the size of the circles by 1\n");

	if (halftoneSize > 25)
		halftoneSize = 25;
	if (halftoneSize < 2)
		halftoneSize = 2;

	m_OPENGL_2_0_SUPPORTED = true;

	// generate a number of textures...
	glGenTextures(1, m_tex);
}

//////////////////////////////////////////////////////////////////////////////////////////
// cRenderClass() - destructor 
//////////////////////////////////////////////////////////////////////////////////////////
cRenderClass::~cRenderClass()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// loop() - enters game loop
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::loop()
{
	glutMainLoop();
}

extern cShaderInfo	ShaderInfo;

//////////////////////////////////////////////////////////////////////////////////////////
// initShaders() - init GLSL shaders
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::initShaders()
{
	GLenum err = glewInit();

	if( GLEW_OK != err )
	{
		printf("Error: Glew is not supported\n\n");
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if (glewIsSupported("GL_VERSION_2_0"))
	{
		printf("OpenGL 2.0 is supported\n\n");
	}
	else
	{
		printf("Error: OpenGL 2.0 is not supported\n\n");
		m_OPENGL_2_0_SUPPORTED = false;
	}

	ShaderInfo.create();
}

//////////////////////////////////////////////////////////////////////////////////////////
// initialize glut stuff
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::create(int argc, _TCHAR* argv[])
{
	// initialise the glut library
	glutInit(&argc, argv);

	// set up the initial display mode
	// need both double buffering and z-buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// set the initial window position
	glutInitWindowPosition(100, 100);

	// set the initial window size
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// create and name the window
	glutCreateWindow("Using GLSL Shaders for Post Processing (Multi-Pass)!");

	// reshape callback for current window
	glutReshapeFunc(winReshapeFunc);

	// set display callback for current window
	glutDisplayFunc(renderScene);	

	glutKeyboardFunc(keyboardread);

	// set up the global idle callback
	glutIdleFunc(update);

	initShaders();	
}

//////////////////////////////////////////////////////////////////////////////////////////
// drawPixel() - draw a pixel into an off-screen buffer
//				 if m_point_size>1 then draw a block of pixels
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::drawPixel(int x, int y)
{
	int start, end;

	start = -(m_point_size/2);
	end	= (int)((m_point_size/2.0f) + 0.5);

	for( int i=start; i<end; i++ )
	{
		for( int j=start; j<end; j++ )
		{
			// reject values outside m_buffer range
			if( (x+j < 0) || (x+j >= m_sw) )
				continue;

			if( (y+i < 0) || (y+i >= m_sh) )
				continue;

			m_buffer[(((y+i)*m_sw+(x+j))*4) + 0] = m_colour.r;
			m_buffer[(((y+i)*m_sw+(x+j))*4) + 1] = m_colour.g;
			m_buffer[(((y+i)*m_sw+(x+j))*4) + 2] = m_colour.b;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// setViewport2D() - sets up the viewport ready for a screen grab
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::setViewport2D()
{
	glLoadIdentity();
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, m_sw, 0, m_sh);
	glMatrixMode(GL_MODELVIEW);

	// set up the viewport
	glViewport
	(
		0,							// lower left x position
		0,							// lower left y position
		m_sw,	// viewport width
		m_sh	// viewport height
	);
}

void cRenderClass::setViewport3D(GLint w, GLint h)
{
	if (h == 0 || w == 0)
		return;

	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0, (GLdouble)w / (GLdouble)h, 0.5, 100.0);

	//GLfloat lightpos0[] = { 0.0f, 0.5f, 0.85, 0.05 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);

	//GLfloat lightpos1[] = { 0.70f, -0.707f, 0.0f, 0.0f };
	//glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport
	(
		0, //lower left x position
		0, //lower left y position
		(GLsizei)SCREEN_WIDTH, //Viewport width
		(GLsizei)SCREEN_HEIGHT //viewport height
	);
}
//float angle = 0;


//////////////////////////////////////////////////////////////////////////////////////////
// render() - 
//////////////////////////////////////////////////////////////////////////////////////////
void cRenderClass::render( int pass )
{
	if( pass == 0 )
	{
		///////////////////////////////////////////////////////
		// Render the 3D object during the first PASS
		///////////////////////////////////////////////////////

		// set the viewport to 3D - so you can render your 3D objects on the first pass
		setViewport3D(SCREEN_WIDTH, SCREEN_HEIGHT);

		// disable shader program
		glUseProgram(0);

		// clear the back buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/////////////////////////////////////////////////////////////
		// draw object here using OpenGL standard calls
		/////////////////////////////////////////////////////////////
		glPushMatrix();

		glLoadIdentity();

		glTranslatef(0.0, 0.0, -2.0);

		glEnable(GL_DEPTH_TEST);

		glRotatef(angle, 1.0, 1.0, 1.0);
		angle += angleIncrease;
		if (angle > 360)
			angle = 0;

		// render selected texture map here..
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		cShader *pList = ShaderInfo.getList();
		int shdr = 0;

		if (shdr >= ShaderInfo.shaderCount())
		{
			printf("Error: Can't access requested shader\n");
			shdr = 0;
		}

		// enable shader program..
		glUseProgram(pList[shdr].program());

		glUniform1i(pList[shdr].get_grabLoc(), (int)m_tex[0]);

		glutSolidTorus(0.25, 0.5, 100, 100);

		glPopMatrix();

		glFlush();

		/////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////	
		if (PASSES > 1)
			return;
	}
	else if (pass == 1)
	{
		// flatten the viewport - i.e. convert to image space
		setViewport2D();

		glEnable(GL_TEXTURE_2D);

		glReadBuffer( GL_BACK );
		glBindTexture(GL_TEXTURE_2D, m_tex[0] );
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, m_sw, m_sh, 0 );

		glBindTexture( GL_TEXTURE_2D, m_tex[0]);	
		glDrawBuffer( GL_BACK );

		// render selected texture map here..
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		cShader *pList = ShaderInfo.getList();
		int shdr = 2;

		if( shdr >= ShaderInfo.shaderCount() )
		{
			printf( "Error: Can't access requested shader\n" );
			shdr = 2;
		}

		// enable shader program..
		glUseProgram( pList[shdr].program() );

		GLint screenXSize = glGetUniformLocation(pList[shdr].program(), "screenXSize");
		GLint screenYSize = glGetUniformLocation(pList[shdr].program(), "screenYSize");
		GLint circleSize = glGetUniformLocation(pList[shdr].program(), "circleSize");

		glUniform1i(circleSize, halftoneSize);
		glUniform1i(screenXSize, SCREEN_WIDTH);
		glUniform1i(screenYSize, SCREEN_HEIGHT);

		glUniform1i( pList[shdr].get_grabLoc(),(int)m_tex[0] );

		glActiveTexture(GL_TEXTURE0 + m_tex[0]);

		glLineWidth(2);

		//glBegin(GL_QUADS);			

		//	// render the final disordered image here..
		//	glColor3f(1.0,1.0,1.0);		

		//	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
		//	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_sh);
		//	glTexCoord2f(1.0f, 1.0f); glVertex2f(m_sw, m_sh);
		//	glTexCoord2f(1.0f, 0.0f); glVertex2f(m_sw, 0);

		//glEnd();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_tex[0] );
		glDisable(GL_TEXTURE_2D);
		glUseProgram( 0 );

		if (PASSES > 2)
			return;
	}
	else
	{
		// flatten the viewport - i.e. convert to image space
		setViewport2D();

		glEnable(GL_TEXTURE_2D);

		glReadBuffer(GL_BACK);
		glBindTexture(GL_TEXTURE_2D, m_tex[0]);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, m_sw, m_sh, 0);

		glBindTexture(GL_TEXTURE_2D, m_tex[0]);
		glDrawBuffer(GL_BACK);

		// render selected texture map here..
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		cShader *pList = ShaderInfo.getList();
		int shdr = 1;

		if (shdr >= ShaderInfo.shaderCount())
		{
			printf("Error: Can't access requested shader\n");
			shdr = 1;
		}

		// enable shader program..
		glUseProgram(pList[shdr].program());

		GLint screenXSize = glGetUniformLocation(pList[shdr].program(), "screenXSize");
		GLint screenYSize = glGetUniformLocation(pList[shdr].program(), "screenYSize");
		GLint circleSize = glGetUniformLocation(pList[shdr].program(), "circleSize");

		glUniform1i(circleSize, halftoneSize);
		glUniform1i(screenXSize, SCREEN_WIDTH);
		glUniform1i(screenYSize, SCREEN_HEIGHT);

		glUniform1i(pList[shdr].get_grabLoc(), (int)m_tex[0]);

		glActiveTexture(GL_TEXTURE0 + m_tex[0]);

		glLineWidth(2);

		glBegin(GL_QUADS);
		
		// render the final disordered image here..
		glColor3f(1.0, 1.0, 1.0);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_sh);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(m_sw, m_sh);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(m_sw, 0);

		glEnd();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_tex[0]);
		glDisable(GL_TEXTURE_2D);
		glUseProgram(0);
	}

	// finally swap the buffers of the current window
	glutSwapBuffers();
	
	// clear out the temp buffer
	clear();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// winReshapeFunc() - gets called initially and whenever the window get resized
// resizing has been locked
//////////////////////////////////////////////////////////////////////////////////////////
void winReshapeFunc(GLint w, GLint h)
{
	// specify current matrix
	glMatrixMode(GL_PROJECTION);

	// load an identity matrix
	glLoadIdentity();	

	// create a projection matrix... i.e. 2D projection onto xy plane
	glOrtho( -SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up the viewport
	glViewport
	(
		0,				// lower left x position
		0,				// lower left y position
		(GLsizei) SCREEN_WIDTH,	// viewport width
		(GLsizei) SCREEN_HEIGHT	// viewport height
	);
}
