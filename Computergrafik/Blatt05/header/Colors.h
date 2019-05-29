#pragma once
#include <glm/glm.hpp>

glm::vec3 rgbToCMY(glm::vec3 rgbColors);
glm::vec3 rgbToHSV(glm::vec3 rgbColors);
glm::vec3 cmyToRGB(glm::vec3 cmyColors);
glm::vec3 cmyToHSV(glm::vec3 cmyColors);
glm::vec3 hsvToRGB(glm::vec3 hsvColors);
glm::vec3 hsvToCMY(glm::vec3 hsvColors);