#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}


Mesh* object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	fill = true;
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length / 2, length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2 };

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* object2D::CreateCircle(std::string name, glm::vec3 circleCenter, float radius, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices_c;
	std::vector<unsigned int> indices_c;
	glm::vec3 center = circleCenter;


	for (int i = 0; i < 360; i++) {
		vertices_c.push_back(VertexFormat(center + glm::vec3(radius * cos(i), radius * sin(i), 0), color));
	}

	indices_c.push_back(0);

	for (unsigned short i = 1; i < 360; i++)
		indices_c.push_back(i);

	indices_c.push_back(1);

	Mesh* circle = new Mesh(name);


	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices_c.push_back(0);
		indices_c.push_back(2);
	}

	circle->InitFromData(vertices_c, indices_c);
	circle->SetDrawMode(GL_TRIANGLE_FAN);
	return circle;
}