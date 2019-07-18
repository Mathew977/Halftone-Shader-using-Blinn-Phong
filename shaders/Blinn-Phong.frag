varying vec4 colour;
varying vec3 normal;
varying vec3 camPos;

const float ka 	= 0.1; //Coefficient for ambient
const float kd 	= 0.4; //Coefficient for diffuse
const float ks 	= 0.8; //Coefficient for specular

void main(void)
{
	//Lighting/colour Values
	vec3 lPosition 	= vec3(1.0, 1.0, 1.0); //Position of the Light
	vec3 lIntensity	= vec3(1.0, 1.0, 1.0); //Intensity of the light

	vec3 ambient 	= vec3(1.0, 0.0, 1.0); //Ambient Colour value
	vec3 diffuse 	= vec3(1.0, 0.0, 1.0); //Diffuse Colour value
	vec3 specColour = vec3(1.0, 1.0, 1.0); //Specular Colour value

	float ns		= 20.0; //Determines the shininess  of the object

	vec3 n = normalize(normal); //Normalise the normal

	vec3 lightDir = normalize(lPosition - camPos);

	vec3 viewDir = normalize(-camPos); //Normalise the camera vector

	//Temporary value to be used later during calculating the diffuse
	float tempDifVal = clamp(max(dot(lightDir, n), 0.0), 0.0, 1.0);
	
	float specular = 0.0;

	vec3 halfDir = normalize(lightDir + viewDir); //Calculate the halfway vector
	
	float specAngle = max(dot(halfDir, n), 0.0); //Set specAngle to the dot product of the halfway vector and the shininess value, if the dot product is less than zero then set it to zero
	
	specular = pow(specAngle, ns);
	
	ambient *= ka; //Calculate the ambient colour value
	diffuse = (lIntensity * kd) * tempDifVal; //Calculate the diffuse colour value
	specColour = (lIntensity * ks) * specular; //Calculate the specular colour value
	
	colour = vec4(vec3(ambient + diffuse + specColour), 1.0); //Set colour of the point to the blinn phong value
	
	gl_FragColor = vec4(colour); //Set the colour of the point
}