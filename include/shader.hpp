#ifndef SHADER_HPP
#define SHADER_HPP

#include "../lib/glad/glad.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace shaderContents {
std::string read_file_contents(std::string &path);
};

namespace fs = std::filesystem;

class Shader {
public:
  Shader(std::string vertex_shader_name, std::string fragment_shader_name);
  void Activate();
  GLuint shaderProgram;
  void Delete();

private:
};

#endif /* SHADER_HPP */
