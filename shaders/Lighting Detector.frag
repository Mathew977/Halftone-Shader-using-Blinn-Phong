uniform sampler2D	grabTexture; 	//Used to grab the colour values from pixels in the scene
varying vec3 		tempColour;		//tempColour value that will determine the final output colour
varying vec2 		texCoord; 		//Current pixel point being looked at
uniform int			screenXSize; 	//Max screen size in the x - Passed in
uniform int 		screenYSize; 	//Max screen size in the y - Passed in
uniform int			circleSize; 	//Max size of the circles - Passed in

void main(void)
{
	vec2 tc;
	tc.x = texCoord.x * screenXSize;
	tc.y = texCoord.y * screenYSize;
	
	//Set the starting colour to be the same as the current colour values of the point
	tempColour = vec3(vec4(texture2D(grabTexture, texCoord.xy)).xyz);
	
	//Check if the point being looked at is the bottom right corner of the current cell
	if (mod(int((tc.x + 1.0)), circleSize) == 0 && mod(int((tc.y + 1.0)), circleSize) == 0 && (tc.y + 1.0) != 500.0 || mod(int((tc.x + 1.0)), circleSize) == 0 && (tc.y == 0.0))
	{
		tempColour = vec3(0.0, 0.0, 0.0); //Set the colour to black
		
		//Loop twice to add all the colours from the previous points in the same cell together
		for (int i = 0; i < circleSize; i++)
		{
			for (int j = 0; j < circleSize; j++)
			{
				vec2 tempVec = vec2(tc.x - i, tc.y + j);
				
				//Divide the coordinates by the screen size so we can grab the colour values
				tempVec.x /= screenXSize;
				tempVec.y /= screenYSize;
				
				//Add the colour value to the tempColour
				tempColour += vec3(vec4(texture2D(grabTexture, tempVec.xy)).xyz);
			}
		}
		
		//Calculate the average colour of the cell
		tempColour /= (circleSize * circleSize);
	}
	
	//Set the current point being looked at to the tempColour
	gl_FragColor = vec4(vec3(tempColour), 1.0);

}