#pragma once

struct vectors //Structure containing the Vectors from the Obj File
{
	float x, y, z;
};

struct vectorTextures //Structure containing the Vector Textures from the Obj File
{
	float x, y;
};

struct vectorNormals //Structure containing the Vector Normals from the Obj File
{
	float x, y, z;
};

struct faces //Structure containing the Faces from the Obj File
{
	char material[32]; //Material that the specific face uses
	int x, y, z;
};

struct ambientColour //Structure containing the Ambient Colours from the mtl File
{
	char ambientMaterial[32]; //Material cooresponding to the ambient Colour
	float x, y, z;
};

struct diffuseColour //Structure containing the Diffuse Colours from the mtl File
{
	char diffuseMaterial[32]; //Material cooresponding to the diffuse Colour
	float x, y, z;
};

class objFileLoader
{

public:

	int vectorCount;
	int vectorTextureCount;
	int vectorNormalCount;
	int faceCount;
	int diffuseCount;
	int kaCount;
	int kdCount;

	vectors* vectorList;
	vectorTextures* vectorTextureList;
	vectorNormals* vectorNormalList;
	faces* faceList;
	ambientColour* ambientColourList;
	diffuseColour* diffuseColourList;

	objFileLoader();
	~objFileLoader();

	void inputObjects(vectors*, vectorTextures*, vectorNormals*, faces*, ambientColour*, diffuseColour*);
	void vListInput(vectors*, float, float, float); //Input the Vectors into the structure
	void vtListInput(vectorTextures*, float, float); //Input the Vector Textures into the structure
	void vnListInput(vectorNormals*, float, float, float); //Input the Vector Normals into the structure
	void fListInput(faces*, char*, char*); //Input the Faces into the structure
	void kdListInput(ambientColour*, float, float, float, char*); //Input the Ambient Colours into the structure
	void kaListInput(diffuseColour*, float, float, float, char*); //Input the Diffuse Colours into the structure

	void counterInput(int, int, int, int, int, int);

	void printvList(vectors*); //Tests
	void printvtList(vectorTextures*); //Tests
	void printvnList(vectorNormals*); //Tests
	void printfList(faces*); //Tests
	void printKdList(ambientColour*); //Tests
	void printKaList(diffuseColour*); //Tests
};

