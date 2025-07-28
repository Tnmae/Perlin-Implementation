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

void Filter::FIRFilter(float *array2D, int terrain_size, double Filter) {
  // left to right
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 1; j < terrain_size; j++) {
      *(array2D + i * terrain_size + j) =
          *(array2D + i * terrain_size + j - 1) * Filter +
          (1 - Filter) * *(array2D + i * terrain_size + j);
    }
  }

  // right to left
  for (int i = 0; i < terrain_size; i++) {
    for (int j = terrain_size - 2; j >= 0; j--) {
      *(array2D + i * terrain_size + j) =
          *(array2D + i * terrain_size + j - 2) * Filter +
          (1 - Filter) * *(array2D + i * terrain_size + j);
    }
  }

  // top to bottom
  for (int j = 0; j < terrain_size; j++) {
    for (int i = 1; i < terrain_size; i++) {
      *(array2D + i * terrain_size + j) =
          *(array2D + i * terrain_size + j - 1) * Filter +
          (1 - Filter) * *(array2D + i * terrain_size + j);
    }
  }

  // bottom to top
  for (int j = 0; j < terrain_size; j++) {
    for (int i = 1; i < terrain_size; i++) {
      *(array2D + i * terrain_size + j) =
          *(array2D + i * terrain_size + j - 1) * Filter +
          (1 - Filter) * *(array2D + i * terrain_size + j);
    }
  }
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

  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      vertices.push_back(
          Vertex(glm::vec3(j * m_worldScale, array2D[i][j], i * m_worldScale),
                 glm::vec3(1.0, 1.0, 1.0)));
    }
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
                                      float minHeight, float maxHeight,
                                      float scalingFactor, GLuint shaderProgram,
                                      double Filter) {
  Terrain::terrain_size = terrain_size;
  Terrain::m_worldScale = scalingFactor;
  Terrain::m_maxHeight = maxHeight;
  Terrain::m_minHeight = minHeight;

  float delta_height = maxHeight - minHeight;

  float array2D[terrain_size][terrain_size];

  // initialising a 0 numbered 2D array
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      array2D[i][j] = 0;
    }
  }

  for (int cur_iter = 0; cur_iter < Iteration; cur_iter++) {
    float iteration_ratio = ((float)cur_iter / (float)Iteration);
    float height = maxHeight - iteration_ratio * delta_height;

    int randX1 = rand() % terrain_size;
    int randZ1 = rand() % terrain_size;

    int counter = 0;

    int randX2, randZ2;

    do {
      randX2 = rand() % terrain_size;
      randZ2 = rand() % terrain_size;

      if (counter++ == 1000) {
        std::cout << "endless loop detected" << __FILE__ << __LINE__
                  << std::endl;
        assert(0);
      }
    } while (randX1 == randX2 && randZ1 == randZ2);

    int dirX = randX2 - randX1;
    int dirZ = randZ2 - randZ1;

    for (int i = 0; i < terrain_size; i++) {
      int dirZ_in = i - randZ1;
      for (int j = 0; j < terrain_size; j++) {
        int dirX_in = j - randX1;

        int cross_product = dirX_in * dirZ - dirX * dirZ_in;

        if (cross_product > 0) {
          array2D[i][j] += height;
        }
      }
    }
  }

  // Normalizing the heightmap array
  float max = array2D[0][0];
  float min = array2D[0][0];
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      if (array2D[i][j] > max) {
        max = array2D[i][j];
      }
      if (array2D[i][j] < min) {
        min = array2D[i][j];
      }
    }
  }

  float min_max_del = max - min;

  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      array2D[i][j] =
          ((array2D[i][j] - min) / min_max_del) * delta_height + minHeight;
    }
  }

  Filter::FIRFilter(&array2D[0][0], terrain_size, Filter);

  Terrain::array2D = &array2D[0][0];

  // Populating the vbo and ebo
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  int initial_x = 0;
  int initial_z = 0;

  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      vertices.push_back(
          Vertex(glm::vec3(initial_x * m_worldScale, array2D[i][j],
                           initial_z * m_worldScale),
                 glm::vec3(1.0f, 1.0f, 1.0f)));
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
      indices.push_back(i * terrain_size + j + 1);
      indices.push_back((i + 1) * terrain_size + j);
      indices.push_back((i + 1) * terrain_size + j + 1);
    }
  }

  // Initialising Mesh
  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::MidpointDisplacementTechnique(int terrain_size) {}

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
