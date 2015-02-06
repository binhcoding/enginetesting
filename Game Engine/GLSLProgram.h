#pragma once
#include <string>
#include <GL/glew.h>
//GLSL - Open GL Shading Language

namespace GameEngine
{
	class GLSLProgram
	{
		public:
		GLSLProgram();
		~GLSLProgram();
		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void LinkShaders();
		void AddAttributes(const std::string& attributeName);
		void Use();
		void Unuse();
		GLint GetUniformLocation(const std::string& uniformName);
		private:
		void CompileShader(const std::string& filePath, GLuint id);

		int _numAttributes;
		GLuint _programId;
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;

	};

}