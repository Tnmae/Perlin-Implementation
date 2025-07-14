#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../lib/glad/glad.h"
#include "stb_image.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

unsigned char *load_image(std::string path);

class Texture {
public:
  Texture(std::string texName);
  void TextureData(GLuint shaderProgram, std::string uniform_name, GLuint unit);
  void DrawTexture(GLuint unit);

private:
  GLuint texID;
};

#endif /* TEXTURE_HPP */
