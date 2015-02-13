#pragma once

#include <GL/glew.h>
namespace GameEngine
{
	struct Position
	{
		float x;
		float y;
	};

	struct ColorRGBA8
	{
		ColorRGBA8() : r(0), g(0), b(0), a(0) { }
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A)  { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		void SetColor(GLubyte R, GLubyte G, GLubyte B, GLubyte A)
		{
			r = R;
			g = G;
			b = B;
			a = A;
		}
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		// 4 bytes for r g b a color
		ColorRGBA8 color;
		// uv texture coordinates
		UV uv;

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		void SetPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}
	};
}