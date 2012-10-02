/*	This file is part of FimbulwinterClient.

	FimbulwinterClient is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FimbulwinterClient.  If not, see <http://www.gnu.org/licenses/>. */

#include "VertexDeclarations.h"

using namespace YA3DE::Graphics;

VertexElement VertexPositionTextureNormalLightmapDeclarationElements[] =
{
	VertexElement(VertexElementFormat::Vector3, VertexElementUsage::Position),
	VertexElement(VertexElementFormat::Vector3, VertexElementUsage::Normal),
	VertexElement(VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0),
};
VertexDeclaration VertexPositionTextureNormalLightmap::Declaration(VertexPositionTextureNormalLightmapDeclarationElements, 4);

VertexElement VertexPositionTextureNormalDeclarationElements[] =
{
	VertexElement(VertexElementFormat::Vector3, VertexElementUsage::Position),
	VertexElement(VertexElementFormat::Vector3, VertexElementUsage::Normal),
	VertexElement(VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0),
};
VertexDeclaration VertexPositionTextureNormal::Declaration(VertexPositionTextureNormalDeclarationElements, 3);
