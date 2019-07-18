varying vec2 	texCoord; 		//Current pixel point being looked at
uniform int		screenXSize; 	//Max screen size in the x - Passed in
uniform int 	screenYSize; 	//Max screen size in the y - Passed in
uniform int		circleSize; 	//Max size of the circles - Passed in

void main(void)
{	
	gl_Position 	= ftransform();
	texCoord	= gl_MultiTexCoord0.xy;
}