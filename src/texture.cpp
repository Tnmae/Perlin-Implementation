#include "../include/texture.hpp"

unsigned char *load_image(std::string texName, int &width, int &height,
                          int &channels) {
  std::string fullpath = fs::current_path();
  std::string imgPath = fullpath + "/../resources/textures/" + texName;
  unsigned char *imgData =
      stbi_load(imgPath.c_str(), &width, &height, &channels, 0);
  if (imgData) {
    std::cout << "texture loaded successfully" << std::endl;
    return imgData;
  } else {
    std::cerr << "error loading texture" << std::endl;
    throw(errno);
  }
}

Texture::Texture(std::string texName) {

  int width, height, channels;

  unsigned char *imgData = load_image(texName, width, height, channels);

  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

  GLenum format;
  if (channels == 4)
    format = GL_RGBA;
  else if (channels == 3)
    format = GL_RGB;
  else
    format = GL_RED;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format,
               GL_UNSIGNED_BYTE, imgData);
  stbi_image_free(imgData);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TextureData(GLuint shaderProgram, std::string uniform_name,
                          GLuint unit) {
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, uniform_name.c_str()), unit);
}

void Texture::DrawTexture(GLuint unit) {
  glBindTexture(GL_TEXTURE_2D, texID);
  glActiveTexture(GL_TEXTURE0 + unit);
}
