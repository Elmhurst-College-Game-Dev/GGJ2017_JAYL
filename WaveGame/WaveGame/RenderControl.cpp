#include "RenderControl.h"
#include "shaders.h"

RenderControl::RenderControl()
{
}


RenderControl::~RenderControl()
{
}

void RenderControl::draw(BaseObject & obj)
{
}

void RenderControl::initRender()
{
	const char *vertSource =
		"#version 330\n"
		"uniform mat3 view;"
		"uniform vec2 worldPos;"
		"uniform vec2 size;"
		"uniform float angle;"
		"in vec2 vertPos;"
		"in vec2 texCoord;"
		"out vec2 fragTexCoord;"
		"void main() {"
		"	vec3 trans = vec3(size.x, size.y, 0.0);"
		"	vec3 alright = trans;"
		"	trans.x = alright.x*cos(angle) - alright.y*sin(angle);"
		"	trans.y = alright.x*sin(angle) + alright.y*cos(angle);"
		"	vec3 yeong_haw_wang = view*trans;"
		"	fragTexCoord = texCoord;"
		"	gl_Position = vec4(yeong_haw_wang, 1.0);"
		"}"
		;
	const char *fragSource =
		"#version 330\n"
		"uniform sampler2D sampler;"
		"in vec2 fragTexCoord;"
		"void main() {"
		"	gl_FragColor = texture(sampler, fragTexCoord);"
		"}"
		;
	this->program = linkProgram(loadShader(vertSource, GL_VERTEX_SHADER), loadShader(fragSource, GL_FRAGMENT_SHADER));
	glUseProgram(this->program);
	viewLoc = glGetUniformLocation(program, "view");
	worldPosLoc = glGetUniformLocation(program, "worldPos");
	sizeLoc = glGetUniformLocation(program, "size");
	vertPosLoc = glGetAttribLocation(program, "vertPos");
	texCoordLoc = glGetAttribLocation(program, "texCoord");
	samplerLoc = glGetUniformLocation(program, "sampler");

	const int textureWidth = 32;
	const int textureHeight = 32;
	const int textureCount = 1;

	//Create the array
	int textures[textureCount*4]{
		//x, y, width, height format
		0, 0, 32, 32
	};
	//Now create the array buffer for the textures
	GLfloat arrayBuf[textureCount*16];
	GLuint indexArrayBuf[textureCount*6];
 
	for (int i = 0; i < textureCount; i++) {
		//top left to top right to bottom right to buttom left
		arrayBuf[(i* 16) + 0] = 0.0f;
		arrayBuf[(i* 16) + 1] = 0.0f;
		arrayBuf[(i* 16) + 2] = float(textures[0])/float(textureWidth);
		arrayBuf[(i* 16) + 3] = float(textures[1]) / float(textureHeight);

		arrayBuf[(i* 16) + 4] = 1.0f;
		arrayBuf[(i* 16) + 5] = 0.0f;
		arrayBuf[(i* 16) + 6] = float(textures[0]+ textures[2]) / float(textureWidth);
		arrayBuf[(i* 16) + 7] = float(textures[1]) / float(textureHeight);

		arrayBuf[(i* 16) + 8] = 1.0f;
		arrayBuf[(i* 16) + 9] = 1.0f;
		arrayBuf[(i* 16) + 10] = float(textures[0] + textures[2]) / float(textureWidth);
		arrayBuf[(i* 16) + 11] = float(textures[1] + textures[3]) / float(textureHeight);

		arrayBuf[(i* 16) + 12] = 0.0f;
		arrayBuf[(i* 16) + 13] = 1.0f;
		arrayBuf[(i* 16) + 14] = float(textures[0]) / float(textureWidth);
		arrayBuf[(i* 16) + 15] = float(textures[1] + textures[3]) / float(textureHeight);
	}

	for (int i = 0; i < textureCount; i++) {
		indexArrayBuf[(i * 6) + 0] = (i * 4) + 0;
		indexArrayBuf[(i * 6) + 1] = (i * 4) + 1;
		indexArrayBuf[(i * 6) + 2] = (i * 4) + 2;
		indexArrayBuf[(i * 6) + 3] = (i * 4) + 0;
		indexArrayBuf[(i * 6) + 4] = (i * 4) + 3;
		indexArrayBuf[(i * 6) + 5] = (i * 4) + 2;
	}

	//fill imageIndexLocations with images


	//That is done, finally
	//Make the buffers now
	glGenBuffers(1, &arrayBufferName);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBufferName);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16 * textureCount, arrayBuf, GL_STATIC_DRAW);

	glGenBuffers(1, &indexArrayBufferName);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferName);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6 * textureCount, indexArrayBuf, GL_STATIC_DRAW);


}
