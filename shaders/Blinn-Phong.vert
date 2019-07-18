varying vec3 normal;
varying vec3 camPos;

void main(void)
{	
	
	gl_Position 	= ftransform();
	normal 			= (gl_NormalMatrix * gl_Normal); //Get the normal of the pixel point being looked at
	camPos 			= vec3(gl_ModelViewMatrix * gl_Vertex); //Get the camera vector
}