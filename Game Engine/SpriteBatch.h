#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace GameEngine
{
	enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

	struct Glyph
	{
		GLuint texture;
		float depth;
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
		public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
		public:
		SpriteBatch();
		~SpriteBatch();
		void Init();
		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();
		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void RenderBatches();
		private:
		void CreateRenderBatches();
		void CreateVertexArray();
		void SortGlyphs();

		static bool CompareFrontToBack(Glyph* a, Glyph* b);
		static bool CompareBackToFront(Glyph* a, Glyph* b);
		static bool CompareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao; //vertex array object
		GlyphSortType _sortType;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
	};
}