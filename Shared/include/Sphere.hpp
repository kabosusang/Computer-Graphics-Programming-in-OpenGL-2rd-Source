#pragma once
#include <glm/glm.hpp>
#include <vector>

class Sphere {
private:
	int numVertices;
	int numIndices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	void init(int);
	float toRadians(float degrees);

public:
	Sphere();
	Sphere(int prec);
	inline int getNumVertices() { return numVertices; }
	inline int getNumIndices() { return numIndices; }
	inline std::vector<int> getIndices() { return indices; }
	inline std::vector<glm::vec3> getVertices() { return vertices; }
	inline std::vector<glm::vec2> getTexCoords() { return texCoords; }
	inline std::vector<glm::vec3> getNormals() { return normals; }
	inline std::vector<glm::vec3> getTangents() { return tangents; }
	//cont &
	inline const std::vector<int>& getIndices() const { return indices; }
	inline const std::vector<glm::vec3>& getVertices() const { return vertices; }
	inline const std::vector<glm::vec2>& getTexCoords() const { return texCoords; }
	inline const std::vector<glm::vec3>& getNormals() const { return normals; }
	inline const std::vector<glm::vec3>& getTangents() const { return tangents; }

	//&&
	//inline std::vector<int>&& getIndices() { return std::move(indices); }

	~Sphere();
};