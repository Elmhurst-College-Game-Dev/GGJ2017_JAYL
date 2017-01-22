#ifndef __RENDER_CONTROL_CPP__
#define __RENDER_CONTROL_CPP__

#include "RenderControl.h"
#include "shaders.h"
#include "BaseEnemy.h"
#include "BaseObject.h"
#include "Sprite.h"
#include <iostream>
#include "image_loading.h"
#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <fstream>
#include <map>

using namespace rapidjson;

RenderControl::RenderControl()
{
}



RenderControl::~RenderControl()
{
}
/*
void RenderControl::draw(BaseObject * obj)
{
	float angleCos = cos(obj->getAngle());
	float angleSin = sin(obj->getAngle());
	GLfloat modelView[9]{
		obj->getWidth()*angleCos, -obj->getHeight()*angleSin, obj->getMiddle().x - 640.0f,
		obj->getWidth()*angleSin, obj->getHeight()*angleCos, -(obj->getMiddle().y - 360.0f),
		0.0f, 0.0f, 1.0f
	};
	/*cout << modelView[0] << ", " << modelView[1] << ", " << modelView[2] << ", " << endl
	<< modelView[3] << ", " << modelView[4] << ", " << modelView[5] << ", " << endl
	<< modelView[6] << ", " << modelView[7] << ", " << modelView[8] << endl <<
	(int)obj->getSprite().getOffset() << endl;*/
	/*glUniformMatrix3fv(modelLoc, 1, GL_TRUE, modelView);
	glVertexAttribPointer(vertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(vertPosLoc);
	glEnableVertexAttribArray(texCoordLoc);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, mySuperImage);

	glDrawArrays(GL_TRIANGLES, obj->getSprite().getOffset(), 6);
}

void RenderControl::draw(BaseEnemy * obj)
{
	glUseProgram(program);
	float angleCos = cos(obj->getAngle());
	float angleSin = sin(obj->getAngle());
	GLfloat modelView[9]{
		obj->getWidth()*angleCos, -obj->getHeight()*angleSin, obj->getMiddle().x - 640.0f,
		obj->getWidth()*angleSin, obj->getHeight()*angleCos, -(obj->getMiddle().y - 360.0f),
		0.0f, 0.0f, 1.0f
	};*/
	/*cout << modelView[0] << ", " << modelView[1] << ", " << modelView[2] << ", " << endl
		<< modelView[3] << ", " << modelView[4] << ", " << modelView[5] << ", " << endl
		<< modelView[6] << ", " << modelView[7] << ", " << modelView[8] << endl <<
		(int)obj->getSprite().getOffset() << endl;*/
	/*glUniformMatrix3fv(modelLoc, 1, GL_TRUE, modelView);
	glVertexAttribPointer(vertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(vertPosLoc);
	glEnableVertexAttribArray(texCoordLoc);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);
	glBindTexture(GL_TEXTURE_2D, mySuperImage);

	glDrawArrays(GL_TRIANGLES, obj->getSprite().getOffset(), 6);
}

*/

void RenderControl::initTextureWithData(const char *dataFile, const char *textureFile) {
	//Prepare the lists of arrays

	vector<string> textureNames;

	//Create the array
	vector<int> textureCoords;

	char *json_text = nullptr;
	{
		ifstream fp;
		fp.open(dataFile);
		assert(fp.good());
		fp.seekg(0, ios_base::end);
		long len = fp.tellg();
		cout << "FILE SIZE: " << len << endl;
		json_text = new char[len + 1];
		fp.seekg(0, ios_base::beg);
		for (int i = 0; i < len; i++) {
			char c;
			fp.get(c);
			//cout << c;
			json_text[i] = c;
		}
		json_text[len] = '\0';
		fp.close();
	}
	//cout << endl;

	/*json_text =
	"{\"frames\" : [{"
	"\"filename\" : \"test\","
	"\"frame\" : {\"x\":10,\"y\":10,\"w\":200,\"h\":200}"
	"}]}";*/

	//cout << json_text << endl;

	Document doc;
	doc.Parse(json_text);

	delete[] json_text;

	//cout << "checking if root is object...";
	assert(doc.IsObject());
	//cout << "is an object" << endl;
	//cout << "Checking to see if array..";
	assert(doc["frames"].IsArray());
	//cout << "is an array" << endl;
	const Value &frames = doc["frames"].GetArray();
	for (SizeType i = 0; i < frames.Size(); i++) {
		const Value &obj = frames[i];
		//cout << "Checking if object...";
		assert(obj.IsObject());
		//cout << "is object...checking filename is string...";
		assert(obj.GetObject()["filename"].IsString());
		//cout << "is string...checking image dim is object...";
		assert(obj.GetObject()["frame"].IsObject());
		//cout << "is object..." << endl;
		textureNames.push_back(obj.GetObject()["filename"].GetString());
		const Value &imageDim = obj.GetObject()["frame"];
		textureCoords.push_back(imageDim["x"].GetInt());
		textureCoords.push_back(imageDim["y"].GetInt());
		textureCoords.push_back(imageDim["w"].GetInt());
		textureCoords.push_back(imageDim["h"].GetInt());
	}

	int textureWidth = doc["meta"].GetObject()["size"].GetObject()["w"].GetInt();
	int textureHeight = doc["meta"].GetObject()["size"].GetObject()["h"].GetInt();

	cout << textureWidth << ", " << textureHeight << endl;

	cout << "READ IN THE JSON FILE AND GOT THE FOLLOWING:" << endl;
	for (int i = 0; i < textureNames.size(); i++) {
		cout << "[" << textureNames[i] << "]" << endl;
		cout << textureCoords[i * 4 + 0] << ", "
			<< textureCoords[i * 4 + 1] << ", "
			<< textureCoords[i * 4 + 2] << ", "
			<< textureCoords[i * 4 + 3] << ", " << endl;
	}

	//Now create the array buffer for the textures
	GLfloat *arrayBuf = new GLfloat[textureNames.size() * 24];

	for (int i = 0; i < textureNames.size(); i++) {
		//top left to top right to bottom right to buttom left
		arrayBuf[(i * 24) + 0] = -1.0f;
		arrayBuf[(i * 24) + 1] = -1.0f;
		arrayBuf[(i * 24) + 2] = float(textureCoords[(i * 4) + 0]) / float(textureWidth);
		arrayBuf[(i * 24) + 3] = float(textureCoords[(i * 4) + 1]) / float(textureHeight);

		arrayBuf[(i * 24) + 4] = 1.0f;
		arrayBuf[(i * 24) + 5] = -1.0f;
		arrayBuf[(i * 24) + 6] = float(textureCoords[(i * 4) + 0] + textureCoords[(i * 4) + 2]) / float(textureWidth);
		arrayBuf[(i * 24) + 7] = float(textureCoords[(i * 4) + 1]) / float(textureHeight);

		arrayBuf[(i * 24) + 8] = 1.0f;
		arrayBuf[(i * 24) + 9] = 1.0f;
		arrayBuf[(i * 24) + 10] = float(textureCoords[(i * 4) + 0] + textureCoords[(i * 4) + 2]) / float(textureWidth);
		arrayBuf[(i * 24) + 11] = float(textureCoords[(i * 4) + 1] + textureCoords[(i * 4) + 3]) / float(textureHeight);

		arrayBuf[(i * 24) + 12] = -1.0f;
		arrayBuf[(i * 24) + 13] = -1.0f;
		arrayBuf[(i * 24) + 14] = float(textureCoords[(i * 4) + 0]) / float(textureWidth);
		arrayBuf[(i * 24) + 15] = float(textureCoords[(i * 4) + 1]) / float(textureHeight);

		arrayBuf[(i * 24) + 16] = -1.0f;
		arrayBuf[(i * 24) + 17] = 1.0f;
		arrayBuf[(i * 24) + 18] = float(textureCoords[(i * 4) + 0]) / float(textureWidth);
		arrayBuf[(i * 24) + 19] = float(textureCoords[(i * 4) + 1] + textureCoords[(i * 4) + 3]) / float(textureHeight);

		arrayBuf[(i * 24) + 20] = 1.0f;
		arrayBuf[(i * 24) + 21] = 1.0f;
		arrayBuf[(i * 24) + 22] = float(textureCoords[(i * 4) + 0] + textureCoords[(i * 4) + 2]) / float(textureWidth);
		arrayBuf[(i * 24) + 23] = float(textureCoords[(i * 4) + 1] + textureCoords[(i * 4) + 3]) / float(textureHeight);
	}

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);

	GLuint tex = loadTexture(textureFile);

	//That is done, finally
	//Make the buffers now
	GLuint newSprite;
	glGenBuffers(1, &newSprite);
	glBindBuffer(GL_ARRAY_BUFFER, newSprite);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * textureNames.size(), arrayBuf, GL_STATIC_DRAW);
	delete arrayBuf;

	//cout << "Gonna make the sprites array thing now " << endl;
	//Setup the map now
	for (int i = 0; i < textureNames.size(); i++) {
		sprites[textureNames[i]] = Sprite(i * 6, newSprite, tex);
	}

}

void RenderControl::initRender()
{
	initShaders();
	initTextureWithData("enemies_data.json", "enemies_data.png");
	initTextureWithData("cosmic_rays.json", "cosmic_rays.png");
	initTextureWithData("gamma_ray_info.json", "gamma_ray_info.png");
	initTextureWithData("infared_info.json", "infared_info.png");
	initTextureWithData("micro_waves.json", "micro_waves.png");
	initTextureWithData("radio_info.json", "radio_info.png");
	initTextureWithData("rainbow_info.json", "rainbow_info.png");
	initTextureWithData("tops_info.json", "tops_info.png");
	initTextureWithData("ultra_violet_info.json", "ultra_violet_info.png");
	initTextureWithData("x_ray_data.json", "x_ray_data.png");
	initTextureWithData("button_data.json", "button_data.png");
	initTextureWithData("map_data.json", "map_data.png");


	//bg color and other stuff
	glClearColor(0.1f, 0.0f, 0.25f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUseProgram(program);
}

void RenderControl::initShaders()
{
	const char *vertSource =
		"#version 330\n"
		"uniform mat3 model;\n"
		"in vec2 vertPos;\n"
		"in vec2 texCoord;\n"
		"out vec2 fragTexCoord;\n"
		"void main() {\n"
		"	vec3 trans = vec3(vertPos.x, vertPos.y, 1.0);\n"
		"	trans = model*trans;\n"
		"	vec3 yeong_haw_wang = vec3(trans.x/640.0, trans.y/360.0, 1.0);\n"
		"	fragTexCoord = texCoord;\n"
		"	gl_Position = vec4(yeong_haw_wang, 1.0);\n"
		"}\n"
		;
	const char *fragSource =
		"#version 330\n"
		"uniform sampler2D sam;\n"
		"in vec2 fragTexCoord;\n"
		"void main() {\n"
		"	vec4 color = texture(sam, fragTexCoord);\n"
		"	gl_FragColor = color;\n"
		"}\n"
		;
	//std::cout << "Loading vertex Shader" << std::endl;
	GLuint vertShader = loadShader(vertSource, GL_VERTEX_SHADER);
	//std::cout << "Loading fragment Shader" << std::endl;
	GLuint fragShader = loadShader(fragSource, GL_FRAGMENT_SHADER);
	this->program = linkProgram(vertShader, fragShader);
	glUseProgram(this->program);
	vertPosLoc = glGetAttribLocation(program, "vertPos");
	modelLoc = glGetUniformLocation(program, "model");
	texCoordLoc = glGetAttribLocation(program, "texCoord");
	samplerLoc = glGetUniformLocation(program, "sam");
}

Sprite & RenderControl::get(string name)
{
	if (sprites.find(name) == sprites.end()) {
		cout << "Could not find sprite " << name << endl;
		assert(false);
		return Sprite(0, 0, 0);
	} else {
		return sprites[name];
	}
}



#endif