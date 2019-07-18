#include "objFileLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

objFileLoader::objFileLoader()
{
}


objFileLoader::~objFileLoader()
{
}

void objFileLoader::inputObjects(vectors* vectorList, vectorTextures* vectorTextureList, vectorNormals* vectorNormalList, faces* faceList, ambientColour* ambientColourList, diffuseColour* diffuseColourList)
{
	this->vectorList = vectorList;
	this->vectorTextureList = vectorTextureList;
	this->vectorNormalList = vectorNormalList;
	this->faceList = faceList;
	this->ambientColourList = ambientColourList;
	this->diffuseColourList = diffuseColourList;
}

void objFileLoader::vListInput(vectors *vectorList, float v1, float v2, float v3)
{
	vectorList->x = v1; //Add the first vertex to the vector structure
	vectorList->y = v2; //Add the second vertex to the vector structure
	vectorList->z = v3; //Add the third vertex to the vector structure
}

void objFileLoader::vtListInput(vectorTextures *vectorTextureList, float vt1, float vt2)
{

	vectorTextureList->x = vt1; //Add the first vertex texture coordinate to the vertex texture structure
	vectorTextureList->y = vt2; //Add the second vertex texture coordinate to the vertex texture structure
}

void objFileLoader::vnListInput(vectorNormals *vectorNormalList, float vn1, float vn2, float vn3)
{
	vectorNormalList->x = vn1; //Add the first vertex normal to the vertex normal structure
	vectorNormalList->y = vn2; //Add the second vertex normal to the vertex normal structure
	vectorNormalList->z = vn3; //Add the third vertex normal to the vertex normal structure
}

void objFileLoader::fListInput(faces *faceList, char* f, char* mtl)
{
	strcpy(faceList->material, mtl);

	char *token;
	int count = 0;

	token = strtok(f, "/"); //Split the face string read in from the file at the slashes
	//Convert char to int and add the variable to the fList structure
	faceList->x = atoi(token) - 1;
	//faceList->x -= 1;
	//Loop Until end of string
	while (token != NULL)
	{
		token = strtok(NULL, "/"); //Split the face string read in from the file at the slashes
		switch (count) {
		case 0:
			//Convert char to int and add the variable to the fList struct
			faceList->y = atoi(token) - 1;
			break;
		case 1:
			//Convert char to int and add the variable to the fList struct
			faceList->z = atoi(token) - 1;
			break;
		}
		count++;
	}
}

void objFileLoader::kdListInput(ambientColour* ambientColourList, float kd1, float kd2, float kd3, char* file2Material)
{
	strcpy(ambientColourList->ambientMaterial, file2Material);
	ambientColourList->x = kd1; //Add the first ambient Colour to the kd structure
	ambientColourList->y = kd2; //Add the second ambient Colour to the kd structure
	ambientColourList->z = kd3; //Add the third ambient Colour to the kd structure
}

void objFileLoader::kaListInput(diffuseColour* diffuseColourList, float ka1, float ka2, float ka3, char* file2Material)
{
	strcpy(diffuseColourList->diffuseMaterial, file2Material);
	diffuseColourList->x = ka1; //Add the first diffuse Colour to the ka structure
	diffuseColourList->y = ka2; //Add the second diffuse Colour to the ka structure
	diffuseColourList->z = ka3; //Add the third diffuse Colour to the ka structure
}

void objFileLoader::counterInput(int vectorCount, int vectorTextureCount, int vectorNormalCount, int faceCount, int kaCount, int kdCount)
{
	this->vectorCount = vectorCount;
	this->vectorTextureCount = vectorTextureCount;
	this->vectorNormalCount = vectorNormalCount;
	this->faceCount = faceCount;
	this->kaCount = kaCount;
	this->kdCount = kdCount;
}

void objFileLoader::printvList(vectors *vectorList)
{
	//Debug - Print the vList
	printf("%f, %f, %f\n", vectorList->x, vectorList->y, vectorList->z);
}

void objFileLoader::printvtList(vectorTextures *vectorTextureList)
{
	//Debug - Print the vtList
	printf("%f, %f\n", vectorTextureList->x, vectorTextureList->y);
}

void objFileLoader::printvnList(vectorNormals *vectorNormalList)
{
	//Debug - Print the vnList
	printf("%f, %f, %f\n", vectorNormalList->x, vectorNormalList->y, vectorNormalList->z);
}

void objFileLoader::printfList(faces *faceList)
{
	//Debug - print the fList
	printf("%d, %d, %d\n", faceList->x, faceList->y, faceList->z);
}

void objFileLoader::printKdList(ambientColour *ambientColourList)
{
	//Debug - print the kdList
	printf("%f, %f, %f\n", ambientColourList->x, ambientColourList->y, ambientColourList->z);
}

void objFileLoader::printKaList(diffuseColour *diffuseColourList)
{
	//Debug - print the kaList
	printf("%f, %f, %f\n", diffuseColourList->x, diffuseColourList->y, diffuseColourList->z);
}