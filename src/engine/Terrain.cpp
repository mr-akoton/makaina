#include <engine/Terrain.hpp>
#include <utils/utils.hpp>

#include <glm/gtc/matrix_transform.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Terrain::Terrain(int width, int height, float gridSize, float amplitude):
	width(width),
	height(height),
	gridSize(gridSize),
	amplitude(amplitude),
	color0(hexToRGB("#0f6a2e")),
	color1(hexToRGB("#0f6a2e")),
	color2(hexToRGB("#0f6a2e")),
	position(Vector3(0.0f)),
	model(Matrix4(1.0f))
{
	model = glm::translate(model, position);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- Setter --------------------------------- */

void	Terrain::setPosition(Vector3 position)
{
	this->position = position;
	model = glm::translate(model, position);
}

/* --------------------------- Terrain Generation --------------------------- */

Vector3	interpolateColor(
	const Vector3& color1,
	const Vector3& color2,
	float fraction
)
{
    Vector3 interpolated;
    interpolated.x = (color1.r + (color2.r - color1.r) * fraction);
    interpolated.y = (color1.g + (color2.g - color1.g) * fraction);
    interpolated.z = (color1.b + (color2.b - color1.b) * fraction);
    return interpolated;
}

Vector3	getTriangleNormal(Vector3 a, Vector3 b, Vector3 c)
{
	return glm::normalize(glm::cross(b - a, c - a));
}


Vector3 Terrain::getColorBySlope(Vector3 normal)
{
	const float	slopeMax = 0.4f;	
	float		slope = 1.0f - normal.y;

	if (slope < slopeMax)
	{
		return interpolateColor(color2, color0, 1.0f - (slope / slopeMax));
	}
	else
	{
		return color2;
	}
}

#include <iostream>

void	Terrain::generateTerrain(void)
{
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.003f);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFractalOctaves(8);
	noise.SetFractalLacunarity(2.0f);
	noise.SetFractalGain(0.4f);

	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			auto createVertex = [&](int px, int pz) -> Vertex
			{
				return 
				{
					Vector3(
						px * gridSize,
						0.0f,
						pz * gridSize
					),
					Vector3(0.0f),
					Vector3(1.0f),
					Vector2((float)px /( width - 1), (float)pz / (height - 1))
				};
			};

			Vertex topLeft = createVertex(x, z);
			Vertex topRight = createVertex(x + 1, z);
			Vertex bottomLeft = createVertex(x, z + 1);
			Vertex bottomRight = createVertex(x + 1, z + 1);

			auto addTriangle = [&](Vertex& v1, Vertex& v2, Vertex& v3) -> void
			{
				Vector3 normal = getTriangleNormal(
					v1.position,
					v2.position,
					v3.position
				);
				Vector3 color = getColorBySlope(normal);

				v1.normal = normal;
				v2.normal = normal;
				v3.normal = normal;
				v1.color = color;
				v2.color = color;
				v3.color = color;
				mesh.vertices.push_back(v1);
				mesh.vertices.push_back(v2);
				mesh.vertices.push_back(v3);
			};

			addTriangle(bottomLeft, topRight, topLeft);
			addTriangle(bottomLeft, bottomRight, topRight);
		}
	}

	mesh.assignBuffer();
}

/* ---------------------------------- State --------------------------------- */

void	Terrain::render(Shader& shader, Camera& camera)
{
	mesh.draw(shader, camera, "buffer");
}
