uniform sampler2D	grabTexture; 	//Used to grab the colour values from pixels in the scene
uniform int			screenXSize; 	//Max screen size in the x - Passed in
uniform int 		screenYSize; 	//Max screen size in the y - Passed in
uniform int			circleSize; 	//Max size of the circles - Passed in
varying vec2 		texCoord; 		//Current pixel point being looked at

void main(void)
{
	vec2 tc;
	tc.x = texCoord.x * screenXSize;
	tc.y = texCoord.y * screenYSize;

	vec2 finalPoint; //Used to store the bottom right point's coordinates in the cell
	vec2 centerPoint; //Used to store the coordinates of the centre point of the cell
	vec3 white = vec3(1.0, 1.0, 1.0);
    vec3 black = vec3(0.0, 0.0, 0.0);
	vec3 tempColour = vec3(0.0, 0.0, 0.0);
	
	float radius = circleSize / 2; //Set the radius of the circles to be half of the circleSize input
	
	vec3 finalColour = vec3(black);
	
	//Check if the points being looked at is at the bottom right corner of the cell
	if (mod(int((tc.x + 1.0)), circleSize) == 0 && mod(int((tc.y + 1.0)), circleSize) == 0 && (tc.y + 1.0) != 500.0 || mod(int((tc.x + 1.0)), circleSize) == 0 && (tc.y == 0.0))
	{
		gl_FragColor = vec4(vec3(white), 1.0); //Set the point to black
	}
	else
	{
		for (int i = 0; i < circleSize; i++)
		{
			for (int j = 0; j < circleSize; j++)
			{
				//Loop until the bottom right corner point of the cell has been found
				if (mod(int((tc.x + i + 1.0)), circleSize) == 0 && mod(int((tc.y - j + 1.0)), circleSize) == 0 && (tc.y - j + 1.0) != 500.0 || mod(int((tc.x + i + 1.0)), circleSize) == 0 && (tc.y == 0.0))
				{
					finalPoint = vec2(tc.x + i, tc.y - j); //Save the corner points coordinates
					
					//Grab the colour value of the corner point
					tempColour = vec3(vec4(texture2D(grabTexture, vec2(finalPoint.x / screenXSize, finalPoint.y / screenYSize).xy)).xyz);
				}
			}
		}
		
		 //Calculate the centerpoint of the cell currently in
		centerPoint.x = (finalPoint.x - radius);
		centerPoint.y = (finalPoint.y + radius);
		
		float whichColour ; //Used to add up the total colour value of the corner point
		int colourCount = 0; //Counts the number of colours present in the corner point
		
		if (tempColour.x != 0.0)
		{
			whichColour += tempColour.x;
			colourCount++;
		}
		if (tempColour.y != 0.0)
		{
			whichColour += tempColour.y;
			colourCount++;
		}
		if (tempColour.z != 0.0)
		{
			whichColour += tempColour.z;
			colourCount++;
		}
		
		whichColour /= colourCount; //Get the average colour value in the bottom right corner of the cell
		
		radius *= whichColour; //Multiply the radius by the total colour value of the bottom right corner to determine the circle radius
		
		radius *= radius; //Square the radius to work in squarespace
		
		//Calculate the distance between the centerpoint of the cell currently being looked at and the pixel currently being looked at
		//Notice no square root due to working in squarespace
		float dist = ((tc.x - centerPoint.x) * (tc.x - centerPoint.x) + (tc.y - centerPoint.y) * (tc.y - centerPoint.y));

		//Check if the point being looked at is within the radius of the circle
		if (dist <= radius)
		{
			finalColour = vec3(white); //Make the point white because it's within the radius
		}
		else
		{
			finalColour = vec3(black); //Make the point black because it's outside the radius
		}
		
		//if (tempColour.x == 0.0 && tempColour.y == 0.0 && tempColour.z == 0.0)
		//{
		//	finalColour = vec3(black);
		//}

	}
	
	gl_FragColor = vec4(vec3(finalColour), 1.0); //Set colour of point
}