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
#include <chrono>
#include <thread>

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



void RenderControl::initTextureWithData(const char *dataFile, const char *textureFile, 
	float textureWidth, float textureHeight) {
	//Prepare the lists of arrays
	struct json_data {
		string name;
		int x;
		int y;
		int w;
		int h;
	};

	vector<json_data> data;
	char *json_text = nullptr;
	{
		ifstream fp;
		fp.open(dataFile);
		assert(fp.good());
		fp.seekg(0, ios_base::end);
		long len = fp.tellg();
		//cout << "FILE SIZE: " << len << endl;
		json_text = new char[len + 1];
		fp.seekg(0, ios_base::beg);
		char lastc = ']';
		for (long i = 0; i < len; i++) {
			char c;
			fp.get(c);
			//cout << c;
			json_text[i] = c;
			if (c == ']' && lastc == ']')
			{
				len = i + 1l;
				break;
			}
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
	//cout << "About to print" << endl;
	//cout << json_text << endl;
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Document doc;
	doc.Parse(json_text);

	//cout << "Printed!" << endl;

	delete[] json_text;
	//cout << dataFile << " " << textureFile << endl;
	//cout << "checking if root is object...";
	assert(doc.IsArray());
	//cout << "is an object" << endl;
	//cout << "Checking to see if array..";
	assert(doc[0].IsObject());
	//cout << "is an array" << endl;
	const Value &frames = doc[0].GetObject()["items"].GetObject();
	for (Value::ConstMemberIterator itr = frames.MemberBegin();
		itr != frames.MemberEnd(); ++itr) {
		json_data dat;
		dat.name = itr->name.GetString();
		dat.x = itr->value["x"].GetInt();
		dat.y = itr->value["y"].GetInt();
		dat.w = itr->value["width"].GetInt();
		dat.h = itr->value["height"].GetInt();
		data.push_back(dat);
	}

	//int textureWidth = doc["meta"].GetObject()["size"].GetObject()["w"].GetInt();
	//int textureHeight = doc["meta"].GetObject()["size"].GetObject()["h"].GetInt();

	cout << textureWidth << ", " << textureHeight << endl;

	/*cout << "READ IN THE JSON FILE AND GOT THE FOLLOWING:" << endl;
	for (int i = 0; i < data.size(); i++) {
		cout << "[" << data[i].name << "]" << endl;
		cout << data[i].x << ", "
			<< data[i].y << ", "
			<< data[i].w << ", "
			<< data[i].h << ", " << endl;
	}*/

	//Now create the array buffer for the textures
	GLfloat *arrayBuf = new GLfloat[data.size() * 24];

	
	for (int i = 0; i < data.size(); i++) {
		//top left to top right to bottom right to buttom left
	//	cout << "TEXTURE DATA FOR " << data[i].name << endl;
		
		//TRIANGLE 1

		arrayBuf[(i * 24) + 0] = -0.5f;
		arrayBuf[(i * 24) + 1] = -0.5f;
		arrayBuf[(i * 24) + 2] = data[i].x/textureWidth;
		arrayBuf[(i * 24) + 3] = 1.0f-(data[i].y/textureHeight);

	//	cout << arrayBuf[(i * 24) + 2] << ", ";
	//	cout << arrayBuf[(i * 24) + 3] << endl;

		arrayBuf[(i * 24) + 4] = 0.5f;
		arrayBuf[(i * 24) + 5] = -0.5f;
		arrayBuf[(i * 24) + 6] = (data[i].x+data[i].w)/textureWidth;
		arrayBuf[(i * 24) + 7] = 1.0f - (data[i].y/textureHeight);

	//	cout << arrayBuf[(i * 24) + 6] << ", ";
	//	cout << arrayBuf[(i * 24) + 7] << endl;

		arrayBuf[(i * 24) + 8] = -0.5f;
		arrayBuf[(i * 24) + 9] = 0.5f;
		arrayBuf[(i * 24) + 10] = data[i].x/textureWidth;
		arrayBuf[(i * 24) + 11] = 1.0f - ((data[i].y+data[i].h)/textureHeight);

	//	cout << arrayBuf[(i * 24) + 10] << ", ";
	//	cout << arrayBuf[(i * 24) + 11] << endl;

		//NOW BEGINS TRIANGLE 2

		arrayBuf[(i * 24) + 12] = 0.5f;
		arrayBuf[(i * 24) + 13] = -0.5f;
		arrayBuf[(i * 24) + 14] = (data[i].x + data[i].w) / textureWidth;
		arrayBuf[(i * 24) + 15] = 1.0f - (data[i].y / textureHeight);

	//	cout << arrayBuf[(i * 24) + 14] << ", ";
	//	cout << arrayBuf[(i * 24) + 15] << endl;

		arrayBuf[(i * 24) + 16] = 0.5f;
		arrayBuf[(i * 24) + 17] = 0.5f;
		arrayBuf[(i * 24) + 18] = (data[i].x + data[i].w) / textureWidth;
		arrayBuf[(i * 24) + 19] = 1.0f - ((data[i].y + data[i].h) / textureHeight);

	//	cout << arrayBuf[(i * 24) + 18] << ", ";
	//	cout << arrayBuf[(i * 24) + 19] << endl;

		arrayBuf[(i * 24) + 20] = -0.5f;
		arrayBuf[(i * 24) + 21] = 0.5f;
		arrayBuf[(i * 24) + 22] = data[i].x / textureWidth;
		arrayBuf[(i * 24) + 23] = 1.0f - ((data[i].y + data[i].h) / textureHeight);
	
	//	cout << arrayBuf[(i * 24) + 22] << ", ";
	//	cout << arrayBuf[(i * 24) + 23] << endl << endl;
	}
	/*
	for (int i = 0; i < data.size(); i++) {
		//top left to top right to bottom right to buttom left
		//	cout << "TEXTURE DATA FOR " << data[i].name << endl;

		//TRIANGLE 1

		arrayBuf[(i * 24) + 0] = -0.5f;
		arrayBuf[(i * 24) + 1] = -0.5f;
		arrayBuf[(i * 24) + 2] = 0.0f;
		arrayBuf[(i * 24) + 3] = 1.0 - 0.0f;

		//	cout << arrayBuf[(i * 24) + 2] << ", ";
		//	cout << arrayBuf[(i * 24) + 3] << endl;

		arrayBuf[(i * 24) + 4] = 0.5f;
		arrayBuf[(i * 24) + 5] = -0.5f;
		arrayBuf[(i * 24) + 6] = 0.625f;
		arrayBuf[(i * 24) + 7] = 1.0 - 0.0f;

		//	cout << arrayBuf[(i * 24) + 6] << ", ";
		//	cout << arrayBuf[(i * 24) + 7] << endl;

		arrayBuf[(i * 24) + 8] = -0.5f;
		arrayBuf[(i * 24) + 9] = 0.5f;
		arrayBuf[(i * 24) + 10] = 0.0f;
		arrayBuf[(i * 24) + 11] = 1.0 - 0.29f;

		//	cout << arrayBuf[(i * 24) + 10] << ", ";
		//	cout << arrayBuf[(i * 24) + 11] << endl;

		//NOW BEGINS TRIANGLE 2

		arrayBuf[(i * 24) + 12] = 0.5f;
		arrayBuf[(i * 24) + 13] = -0.5f;
		arrayBuf[(i * 24) + 14] = 0.625f;
		arrayBuf[(i * 24) + 15] = 1.0 - 0.0f;

		//	cout << arrayBuf[(i * 24) + 14] << ", ";
		//	cout << arrayBuf[(i * 24) + 15] << endl;

		arrayBuf[(i * 24) + 16] = 0.5f;
		arrayBuf[(i * 24) + 17] = 0.5f;
		arrayBuf[(i * 24) + 18] = 0.625f;
		arrayBuf[(i * 24) + 19] = 1.0 - 0.29f;

		//	cout << arrayBuf[(i * 24) + 18] << ", ";
		//	cout << arrayBuf[(i * 24) + 19] << endl;

		arrayBuf[(i * 24) + 20] = -0.5f;
		arrayBuf[(i * 24) + 21] = 0.5f;
		arrayBuf[(i * 24) + 22] = 0.0f;
		arrayBuf[(i * 24) + 23] = 1.0-0.29f;

		//	cout << arrayBuf[(i * 24) + 22] << ", ";
		//	cout << arrayBuf[(i * 24) + 23] << endl << endl;
	}
	*/

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);

	GLuint tex = loadTexture(textureFile);
	//cout << "Size of data is " << data.size() << endl;
	//That is done, finally
	//Make the buffers now
	GLuint newSprite;
	glGenBuffers(1, &newSprite);
	glBindBuffer(GL_ARRAY_BUFFER, newSprite);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * data.size(), arrayBuf, GL_STATIC_DRAW);

	//cout << "Gonna make the sprites array thing now " << endl;
	//Setup the map now
	for (int i = 0; i < data.size(); i++) {
		sprites[data[i].name] = Sprite(i * 6, newSprite, tex);
		cout << data[i].name << " (" << data[i].x << ", " << data[i].y << "); (" << data[i].w << ", " << data[i].h << ")"
			<< " offset of " << (i*6) << endl;
	}

	delete [] arrayBuf;
}

void RenderControl::initRender()
{
	initShaders();
	initTextureWithData("atlas0.json", "atlas0_0.png", 2048.0f, 2048.0f);

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
		"in vec2 vertPos;\n"
		"out vec2 fragTexCoord;\n"
		"in vec2 texCoord;\n"
		"uniform mat3 model;\n"
		"uniform vec2 size;\n"
		"uniform vec2 worldPos;\n"
		"void main() {\n"
		"	fragTexCoord = texCoord;\n"
	//	"	vec3 rotated = model*vec3(vertPos, 1.0);"
		"	gl_Position = vec4(\n"
		"		((vertPos.x*size.x)+worldPos.x-640.0)/640.0,\n"
		"		-((vertPos.y*size.y)+worldPos.y-360.0)/360.0,\n"
		"		0.0, 1.0);\n"
		"}\n"
		;
	const char *fragSource =
		"#version 330\n"
		"uniform sampler2D sam;\n"
		"in vec2 fragTexCoord;\n"
		"void main() {\n"
		"	vec4 color = texture(sam, fragTexCoord);\n"
		"	//vec4 color = vec4(0.0, 1.0, 0.0, 1.0);\n"
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
	sizeLoc = glGetUniformLocation(program, "size");
	worldPosLoc = glGetUniformLocation(program, "worldPos");
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