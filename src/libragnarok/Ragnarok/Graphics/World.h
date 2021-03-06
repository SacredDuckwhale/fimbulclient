/*	This file is part of FimbulwinterClient.

	FimbulwinterClient is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FimbulwinterClient is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FimbulwinterClient.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef FCLIENT_WORLD_H
#define FCLIENT_WORLD_H

#include <list>
#include <vector>

#include <YA3DE/Helpers.h>
#include <YA3DE/Scene/FpsCamera.h>
#include <YA3DE/Scene/SceneManager.h>

#include <YA3DE/FileSystem/FileManager.h>
#include <YA3DE/Content/ContentManager.h>

#include <YA3DE/Graphics/ShaderProgram.h>
#include <YA3DE/Graphics/VertexDeclaration.h>
#include <YA3DE/Graphics/VertexBuffer.h>
#include <YA3DE/Graphics/IndexBuffer.h>
#include <YA3DE/Graphics/Texture2D.h>

namespace Ragnarok
{
	using namespace YADE;

	class WorldModel;
	class World : public Resource, public SceneManager
	{
	public:
#pragma region Internal Data Structs
		#include <YA3DE/Pack1.h>
		struct GndHeader
		{
			char Magic[4];
			union
			{
				struct
				{
					unsigned char Major;
					unsigned char Minor;
				};
				unsigned short Version;
			} Version;
			int Width;
			int Height;
			float Zoom;
			int TextureCount;
			int TextureSize;
		} STRUCT_PACKED;

		struct LightmapCell
		{
			unsigned char Brightness[8 * 8];
			struct
			{
				unsigned char R;
				unsigned char G;
				unsigned char B;
			} Color[8 * 8];
		} STRUCT_PACKED;

		struct Surface
		{
			float U[4];
			float V[4];
			short TextureID;
			short LightmapID;
			struct
			{
				unsigned char B;
				unsigned char G;
				unsigned char R;
				unsigned char A;
			} Color;
		} STRUCT_PACKED;

		struct GroundCell
		{
			float Height[4];
			int TopSurfaceID;
			int FrontSurfaceID;
			int RightSurfaceID;
		} STRUCT_PACKED;

		struct GatHeader
		{
			char Magic[4];
			union
			{
				struct
				{
					unsigned char Major;
					unsigned char Minor;
				};
				unsigned short Version;
			} Version;
			int Width;
			int Height;
		} STRUCT_PACKED;

		struct AltitudeCell
		{
			float Height[4];
			int Type;
		} STRUCT_PACKED;

		struct RswHeader
		{
			char Magic[4];
			union
			{
				struct
				{
					unsigned char Major;
					unsigned char Minor;
				};
				unsigned short Version;
			} Version;
		} STRUCT_PACKED;

		struct WaterInfo
		{
			float Level;
			int Type;
			float WaveHeight;
			float WaveSpeed;
			float WavePitch;
			int AnimSpeed;
		} STRUCT_PACKED;

		struct LightInfo
		{
			int Longitude;
			int Latitude;
			glm::vec3 Diffuse;
			glm::vec3 Ambient;
			glm::vec3 Position;
			float Intensity;
		} STRUCT_PACKED;

		struct GroundInfo
		{
			int Top;
			int Bottom;
			int Left;
			int Right;
		} STRUCT_PACKED;
		#include <YA3DE/PackEnd.h>
#pragma endregion

		World();

		bool LoadFromRsw(YADE::FilePtr rswFile);

		virtual void Update(double elapsed);
		virtual void RenderStaticGeometry(double elapsed);
		
		/* Ground */
		DEFPROP_RO(public, int, GroundWidth);
		DEFPROP_RO(public, int, GroundHeight);
		DEFPROP_RO(public, float, GroundZoom);
		DEFPROP_RO(public, std::vector<Texture2DPtr>, GroundTextures);
		DEFPROP_RO(public, Texture2DPtr, Lightmap);
		DEFPROP_RO(public, VertexBufferPtr, GroundVBuffer);
		DEFPROP_RO(public, std::vector<IndexBufferPtr>, GroundIBuffers);

		/* Altitude */
		DEFPROP_RO(public, unsigned int, AltitudeWidth);
		DEFPROP_RO(public, unsigned int, AltitudeHeight);
		DEFPROP_RO(public, std::vector<AltitudeCell>, AltitudeCells);

		/* Water */
		DEFPROP_RO(public, WaterInfo, Water);
		DEFPROP_RO(public, VertexBufferPtr, WaterVBuffer);
		DEFPROP_RO(public, IndexBufferPtr, WaterIBuffer);
		DEFPROP_RO(public, std::vector<Texture2DPtr>, WaterTextures);
		DEFPROP_RO(public, unsigned int, WaterTextureIndex);
		DEFPROP_RO(public, double, WaterElapsed);
		
		/* World */
		DEFPROP_RO(public, LightInfo, Light);
		DEFPROP_RO(public, GroundInfo, Ground);
		
	private:
		ShaderProgramPtr _GroundShader;
		ShaderProgramPtr _CommonShader;
		std::vector<WorldModel *> _Models;
		
		void SetupGroundLightmap(std::vector<LightmapCell> &lmaps);
		void SetupGroundVertices(std::vector<LightmapCell> &lmaps, std::vector<Surface> &surfaces, std::vector<GroundCell> &cells);
		bool SetupWaterVertices();

		bool LoadGround(YADE::FilePtr stream);
		bool LoadAltitude(YADE::FilePtr stream);
		bool LoadWorld(YADE::FilePtr stream);
	};
	typedef std::shared_ptr<World> WorldPtr;
}

#endif
