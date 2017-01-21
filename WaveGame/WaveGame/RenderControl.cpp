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

	//MAP VALUES TO THE INDEX LOCATION
	//fill imageIndexLocations with images
}
