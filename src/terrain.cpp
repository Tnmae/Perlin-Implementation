#include "../include/terrain.hpp"
#include <glm/integer.hpp>

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

void Terrain::InitTerrain(std::string file_name, GLuint shaderProgram,
                          float scalingFactor) {
  Terrain::m_worldScale = scalingFactor;

  size_t size;
  float *data = (float *)loadTerrainData(file_name, size);
  int terrain_size = std::sqrt((float)size / sizeof(float));

  Terrain::terrain_size = terrain_size;

  float array2D[terrain_size][terrain_size];
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      array2D[i][j] = *(data + i * terrain_size + j);
    }
  }

  Terrain::array2D = &array2D[0][0];

  free(data);

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  float initial_x = 0;
  float initial_z = 0;
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      vertices.push_back(
          Vertex(glm::vec3(initial_x * m_worldScale, array2D[i][j],
                           initial_z * m_worldScale),
                 glm::vec3(1.0, 1.0, 1.0)));
      initial_x++;
    }
    initial_z++;
    initial_x = 0;
  }

  for (int i = 0; i < terrain_size - 1; i++) {
    for (int j = 0; j < terrain_size - 1; j++) {
      indices.push_back(i * terrain_size + j);
      indices.push_back((i + 1) * terrain_size + j);
      indices.push_back(i * terrain_size + j + 1);
      indices.push_back((i + 1) * terrain_size + j + 1);
      indices.push_back(i * terrain_size + j + 1);
      indices.push_back((i + 1) * terrain_size + j);
    }
  }

  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::FaultFormationTechnique(int terrain_size, int Iteration,
                                      float minHeight, float maxHeight) {
  Terrain::terrain_size = terrain_size;
}

void Terrain::RenderTerrain(GLenum mode, bool wireframe) {
  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  terrain_mesh->Draw(mode);
}

void Terrain::Delete() { terrain_mesh->Delete(); }

void Terrain::printArray2D() {
  float *ptr = array2D;
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      std::cout << *ptr << " ";
      ptr++;
    }
    std::cout << "\n";
  }
}
