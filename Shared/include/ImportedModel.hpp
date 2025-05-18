#pragma once
#include <glm/glm.hpp>
#include <vector>

class ImportedModel {
private:
	int numVertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normalVecs;

public:
	ImportedModel();
	ImportedModel(const char* filePath);
	inline int getNumVertices() { return numVertices; }
	inline std::vector<glm::vec3> getVertices() { return vertices; }
	inline std::vector<glm::vec2> getTextureCoords() { return texCoords; }
	inline std::vector<glm::vec3> getNormals() { return normalVecs; }

	//const &
	inline const int getNumVertices() const { return numVertices; }
	inline const std::vector<glm::vec3>& getVertices() const { return vertices; }
	inline const std::vector<glm::vec2>& getTextureCoords() const { return texCoords; }
	inline const std::vector<glm::vec3>& getNormals() const { return normalVecs; }
};

class ModelImporter {
private:
	std::vector<float> vertVals;
	std::vector<float> triangleVerts;
	std::vector<float> textureCoords;
	std::vector<float> stVals;
	std::vector<float> normals;
	std::vector<float> normVals;

public:
	ModelImporter();
	void parseOBJ(const char* filePath);
	int getNumVertices() { return (triangleVerts.size() / 3); }
	std::vector<float> getVertices() { return triangleVerts; }
	std::vector<float> getTextureCoordinates() { return textureCoords; }
	std::vector<float> getNormals() { return normals; }

    //const& 
    const std::vector<float>& getVertices() const { return triangleVerts; }
	const std::vector<float>& getTextureCoordinates() const{ return textureCoords; }
	const std::vector<float>& getNormals() const{ return normals; }
};