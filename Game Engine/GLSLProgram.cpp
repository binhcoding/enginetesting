#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

// initialization list
GLSLProgram::GLSLProgram() : _numAttributes(0), _programId(0), _vertexShaderId(0), _fragmentShaderId(0)
{

}


GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderId == 0)
	{
		FatalError("Vertex shader failed to be created.");
	}

	_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderId == 0)
	{
		FatalError("Fragment shader failed to be created.");
	}

	CompileShader(vertexShaderFilePath, _vertexShaderId);
	CompileShader(fragmentShaderFilePath, _fragmentShaderId);
}

void GLSLProgram::CompileShader(const std::string& filePath, GLuint id)
{
	_programId = glCreateProgram();

	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		FatalError("Failed to open: " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// the max length includes the null character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//provide the info log in whatever manner you deem best
		// exit with failure
		glDeleteShader(id);// don't leak the shader;
		std::printf("%s\n", &errorLog[0]);
		FatalError("Shader " + filePath + " failed to compile");
	}
}

void GLSLProgram::LinkShaders()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program
	

	//attach our shaders to our program
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);

	//link our program
	glLinkProgram(_programId);

	// note the differetn functions here: glGetProgram* instead of glGetShader*
	GLint isLinked = 0;
	glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

		//the maxlength includes the null character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programId, maxLength, &maxLength, &infoLog[0]);

		//we don't need the program anymore
		glDeleteProgram(_programId);
		//dont leak the shaders either
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		// use the info log as you see fit
		
		std::printf("%s\n", &infoLog[0]);
		FatalError("Shaders failed to link.");
	}

	//always detach the shaders after a successful link
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
}

void GLSLProgram::AddAttributes(const std::string& attributeName)
{
	glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::Use()
{
	glUseProgram(_programId);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint GLSLProgram::GetUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programId, uniformName.c_str());

	if (location == GL_INVALID_INDEX)
	{
		FatalError("Uniform " + uniformName + " not found in shader.");
	}

	return location;
}