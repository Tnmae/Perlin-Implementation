#include "../include/shader.hpp"
#include <filesystem>

std::string shaderContents::read_file_contents(std::string &fileName) {
  std::string current_dir = fs::current_path();
  std::string path = current_dir + "/../resources/shaders/" + fileName;
  std::cout << path << std::endl;
  std::ifstream file(path, std::ios::binary);
  if (file) {
    std::string file_contents;
    file.seekg(0, std::ios::end);
    file_contents.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&file_contents[0], file_contents.size());
    file.close();
    return file_contents;
  } else {
    throw(errno);
  }
}

Shader::Shader(std::string vertex_shader_name,
               std::string fragment_shader_name) {

  std::string vertexShaderC =
      shaderContents::read_file_contents(vertex_shader_name);
  std::string fragmentShaderC =
      shaderContents::read_file_contents(fragment_shader_name);

  const char *vert = vertexShaderC.c_str();
  const char *frag = fragmentShaderC.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vert, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, NULL);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate() { glUseProgram(shaderProgram); }

void Shader::Delete() { glDeleteProgram(shaderProgram); }
