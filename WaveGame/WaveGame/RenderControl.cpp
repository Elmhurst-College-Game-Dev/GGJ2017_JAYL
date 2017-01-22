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

using namespace rapidjson;

RenderControl::RenderControl()
{
}


RenderControl::~RenderControl()
{
}

void RenderControl::draw(BaseObject * obj)
{
	glUseProgram(program);
	float angleCos = cos(obj->getAngle());
	float angleSin = sin(obj->getAngle());
	GLfloat modelView[9]{
		obj->getWidth() / 2.0f*angleCos, -obj->getHeight() / 2.0f*angleSin, obj->getMiddle().x - 640.0f,
		obj->getWidth() / 2.0f*angleSin, obj->getHeight() / 2.0f*angleCos, -(obj->getMiddle().y - 360.0f),
		0.0f, 0.0f, 1.0f
	};
	glUniformMatrix3fv(modelLoc, 1, GL_TRUE, modelView);
	glVertexAttribPointer(vertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(vertPosLoc);
	glEnableVertexAttribArray(texCoordLoc);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, obj->getSprite().getOffset());
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
	};
	glUniformMatrix3fv(modelLoc, 1, GL_TRUE, modelView);
	glVertexAttribPointer(vertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(vertPosLoc);
	glEnableVertexAttribArray(texCoordLoc);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, obj->getSprite().getOffset());
}

void RenderControl::initRender()
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
		"	gl_FragColor = texture(sam, fragTexCoord);\n"
		"}\n"
		;
	std::cout << "Loading vertex Shader" << std::endl;
	GLuint vertShader = loadShader(vertSource, GL_VERTEX_SHADER);
	std::cout << "Loading fragment Shader" << std::endl;
	GLuint fragShader = loadShader(fragSource, GL_FRAGMENT_SHADER);
	this->program = linkProgram(vertShader, fragShader);
	glUseProgram(this->program);
	vertPosLoc = glGetAttribLocation(program, "vertPos");
	modelLoc = glGetUniformLocation(program, "model");
	texCoordLoc = glGetAttribLocation(program, "texCoord");
	samplerLoc = glGetUniformLocation(program, "sam");

	const int textureWidth = 8192;
	const int textureHeight = 8192;

	//Prepare the lists of arrays

	vector<string> textureNames;

	//Create the array
	vector<int> textureCoords;
	
	char *json_text = nullptr;
	{
		ifstream fp;
		fp.open(("textures_info.json"));
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

	delete [] json_text;

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
	
	/*cout << "READ IN THE JSON FILE!" << endl;
	for (int i = 0; i < textureNames.size(); i++) {
		cout << textureNames[i] << endl;
		cout << textureCoords[i * 4 + 0] << ", "
			<< textureCoords[i * 4 + 1] << ", "
			<< textureCoords[i * 4 + 2] << ", "
			<< textureCoords[i * 4 + 3] << ", "  << endl;
	}*/

	//Now create the array buffer for the textures
	GLfloat *arrayBuf = new GLfloat[textureNames.size()*16];
	GLuint *indexArrayBuf = new GLuint[textureNames.size() *6];
 
	for (int i = 0; i < textureNames.size(); i++) {
		//top left to top right to bottom right to buttom left
		arrayBuf[(i* 16) + 0] = -1.0f;
		arrayBuf[(i* 16) + 1] = -1.0f;
		arrayBuf[(i* 16) + 2] = float(textureCoords[ (i*4) +0 ])/float(textureWidth);
		arrayBuf[(i* 16) + 3] = float(textureCoords[(i * 4) + 1]) / float(textureHeight);

		arrayBuf[(i* 16) + 4] = 1.0f;
		arrayBuf[(i* 16) + 5] = -1.0f;
		arrayBuf[(i* 16) + 6] = float(textureCoords[(i * 4) + 0]+ textureCoords[(i * 4) + 2]) / float(textureWidth);
		arrayBuf[(i* 16) + 7] = float(textureCoords[(i * 4) + 1]) / float(textureHeight);

		arrayBuf[(i* 16) + 8] = 1.0f;
		arrayBuf[(i* 16) + 9] = 1.0f;
		arrayBuf[(i* 16) + 10] = float(textureCoords[(i * 4) + 0] + textureCoords[(i * 4) + 2]) / float(textureWidth);
		arrayBuf[(i* 16) + 11] = float(textureCoords[(i * 4) + 1] + textureCoords[(i * 4) + 3]) / float(textureHeight);

		arrayBuf[(i* 16) + 12] = -1.0f;
		arrayBuf[(i* 16) + 13] = 1.0f;
		arrayBuf[(i* 16) + 14] = float(textureCoords[(i * 4) + 0]) / float(textureWidth);
		arrayBuf[(i* 16) + 15] = float(textureCoords[(i * 4) + 1] + textureCoords[(i * 4) + 3]) / float(textureHeight);
	}

	for (int i = 0; i < textureNames.size(); i++) {
		indexArrayBuf[(i * 6) + 0] = (i * 4) + 0;
		indexArrayBuf[(i * 6) + 1] = (i * 4) + 1;
		indexArrayBuf[(i * 6) + 2] = (i * 4) + 2;
		indexArrayBuf[(i * 6) + 3] = (i * 4) + 0;
		indexArrayBuf[(i * 6) + 4] = (i * 4) + 3;
		indexArrayBuf[(i * 6) + 5] = (i * 4) + 2;
	}
	cout << "Gonna make the sprites array thing now " << endl;
	//Setup the map now
	for (int i = 0; i < textureNames.size(); i++) {
		sprites[textureNames[i]] = i * 6 * sizeof(GLuint); //because it's all ordered
	}

	GLuint mySuperImage = loadTexture("textures_info.png");
	glBindTexture(GL_TEXTURE_2D, mySuperImage);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);

	//That is done, finally
	//Make the buffers now
	glGenBuffers(1, &arrayBufferName);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16 * textureNames.size(), arrayBuf, GL_STATIC_DRAW);

	glGenBuffers(1, &indexArrayBufferName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferName);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6 * textureNames.size(), indexArrayBuf, GL_STATIC_DRAW);

	glUseProgram(program);
	//Initialize the view matrix
	glBindBuffer(GL_ARRAY_BUFFER, arrayBufferName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferName);

	delete arrayBuf;
	delete indexArrayBuf;
	
	//bg color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

Sprite & RenderControl::get(string name)
{
	return sprites[name];
}



#endif