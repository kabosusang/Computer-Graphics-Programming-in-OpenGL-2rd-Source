#pragma once
#include <glm/glm.hpp>
#include <vector>

class Torus {
private:
	int numVertices;
	int numIndices;
	int prec;
	float inner;
	float outer;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> sTangents;
	std::vector<glm::vec3> tTangents;
	void init();
	float toRadians(float degrees);

public:
	Torus();
	Torus(float inner, float outer, int prec);
	inline int getNumVertices() { return numVertices; }
	inline int getNumIndices() { return numIndices; }

	inline std::vector<int> getIndices() { return indices; }
	inline std::vector<glm::vec3> getVertices() { return vertices; }
	inline std::vector<glm::vec2> getTexCoords() { return texCoords; }
	inline std::vector<glm::vec3> getNormals() { return normals; }
	inline std::vector<glm::vec3> getStangents() { return sTangents; }
	inline std::vector<glm::vec3> getTtangents() { return tTangents; }

	//const &
	inline const std::vector<int>& getIndices() const { return indices; }
	inline const std::vector<glm::vec3>& getVertices() const { return vertices; }
	inline const std::vector<glm::vec2>& getTexCoords() const { return texCoords; }
	inline const std::vector<glm::vec3>& getNormals() const { return normals; }
	inline const std::vector<glm::vec3>& getStangents() const { return sTangents; }
	inline const std::vector<glm::vec3>& getTtangents() const { return tTangents; }
};