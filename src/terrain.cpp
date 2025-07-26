#include "../include/terrain.hpp"

void *loadTerrainData(std::string file_name, size_t &out_size) {
  std::string current_path = fs::current_path().string();

  std::string path = current_path + "/../resources/textures/" + file_name;
  std::cout << "Loading height map from location : " << path << std::endl;
  std::ifstream file(path, std::ios::binary);

  if (!file) {
    std::cerr << "error loading height map" << std::endl;
    out_size = 0;
    return nullptr;
  }

  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);

  char *p = (char *)malloc(size);
  if (!p) {
    std::cerr << "data allocation failed" << std::endl;
    out_size = 0;
    return nullptr;
  }

  file.read(p, size);
  if (!file) {
    std::cerr << "failed to read the contents of the file" << std::endl;
    out_size = 0;
    free(p);
    return nullptr;
  }

  out_size = size;
  return p;
}

Terrain::Terrain(std::string file_name, GLuint shaderProgram) {
  size_t size;
  float *data = (float *)loadTerrainData(file_name, size);
  std::cout << "size of height map =" << size << std::endl;
  int terrain_size = std::sqrt((float)size / sizeof(float));
  float array2D[terrain_size][terrain_size];
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      array2D[i][j] = *(data + i * terrain_size + j);
    }
  }

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  float initial_x = 0;
  float initial_z = 0;
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      vertices.push_back(Vertex(glm::vec3(initial_x, array2D[i][j], initial_z),
                                glm::vec3(1.0, 1.0, 1.0)));
      initial_x++;
    }
    initial_z++;
    initial_x = 0;
  }
  std::cout << "size of vertices is = " << vertices.size() << std::endl;

  for (int i = 0; i < terrain_size - 1; i++) {
    for (int j = 0; j < terrain_size - 1; j++) {
      indices.push_back(i * terrain_size + j);
      indices.push_back((i + 1) * terrain_size + j);
      indices.push_back(i * terrain_size + j + 1);
      indices.push_back(i * terrain_size + j + 1);
      indices.push_back((i + 1) * terrain_size + j + 1);
      indices.push_back((i + 1) * terrain_size + j);
    }
  }

  std::cout << "size of indices is = " << indices.size() << std::endl;

  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::RenderTerrain(GLenum mode) { terrain_mesh->Draw(mode); }

void Terrain::Delete() { terrain_mesh->Delete(); }
