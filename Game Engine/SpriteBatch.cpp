#include "SpriteBatch.h"
#include <algorithm>

namespace GameEngine
{
	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType) //GlyphSortType::TEXTURE
	{
		_sortType = sortType;
		_renderBatches.clear();
		for (int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i];
		}
		_glyphs.clear();
	}

	void SpriteBatch::End()
	{
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.SetPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::RenderBatches()
	{
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);
		if (_glyphs.empty())
			return;
		int offset = 0;
		int currentVertex = 0;
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		vertices[currentVertex++] = _glyphs[0]->topLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomLeft;
		vertices[currentVertex++] = _glyphs[0]->bottomRight;
		vertices[currentVertex++] = _glyphs[0]->bottomRight;
		vertices[currentVertex++] = _glyphs[0]->topRight;
		vertices[currentVertex++] = _glyphs[0]->topLeft;
		offset += 6;

		for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++)
		{
			if (_glyphs[currentGlyph]->texture != _glyphs[currentGlyph - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphs[currentGlyph]->texture);
			else
				_renderBatches.back().numVertices += 6;
			vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->topRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::CreateVertexArray()
	{
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);
		if (_vbo == 0)
			glGenBuffers(1, &_vbo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		// this is position attribute pointer
		// stride is size of struct
		// const void pointer is just the offset in bytes
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		// color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		// this is the uv attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::SortGlyphs()
	{
		switch (_sortType)
		{
			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareFrontToBack);
				break;
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareTexture);
				break;
		}

	}

	bool SpriteBatch::CompareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}

	bool SpriteBatch::CompareBackToFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}

	bool SpriteBatch::CompareTexture(Glyph* a, Glyph* b)
	{
		return a->texture < b->texture;
	}
}