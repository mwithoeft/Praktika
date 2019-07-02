#include "header/Material.h"


Material::Material() {
	material = RUBY;
}

void Material::setMaterial(Mat m) {
	material = m;
}

MaterialStr Material::getMaterial() {
	MaterialStr str;
	switch (material) {
	case RUBY:
		str.surfKa = glm::vec3{ 0.1745f, 0.01175f, 0.01175f };
		str.surfKd = glm::vec3{ 0.61424f, 0.04136f, 0.04136f };
		str.surfKs = glm::vec3{ 0.727811f, 0.626959f, 0.626959f };
		str.surfShininess = 0.6f;
		break;
	case EMERALD:
		str.surfKa = glm::vec3{ 0.0215f, 0.1745f, 0.0215f };
		str.surfKd = glm::vec3{ 0.07568f, 0.61424f, 0.07568f };
		str.surfKs = glm::vec3{ 0.633f, 0.727811f, 0.633f };
		str.surfShininess = 0.6f;
		break;
	case YELLOW:
		str.surfKa = glm::vec3{ 0.5f, 0.5f, 0.0f };
		str.surfKd = glm::vec3{ 0.5f, 0.5f, 0.0f };
		str.surfKs = glm::vec3{ 0.6f, 0.6f, 0.5f };
		str.surfShininess = 0.32f;
		break;
	case BLUE:
		str.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		str.surfKd = glm::vec3{ 0.0f, 0.0f, 0.5f };
		str.surfKs = glm::vec3{ 0.6f, 0.6f, 0.7f };
		str.surfShininess = 0.25f;
		break;
	case GREEN:
		str.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		str.surfKd = glm::vec3{ 0.1f, 0.35f, 0.1f };
		str.surfKs = glm::vec3{ 0.45f, 0.55f, 0.45f };
		str.surfShininess = 32.0f;
		break;
	case WHITE:
		str.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		str.surfKd = glm::vec3{ 0.55f,0.55f,0.55f };
		str.surfKs = glm::vec3{ 0.70f,0.70f,0.70f };
		str.surfShininess = 32.0f;
		break;
	case CYAN:
		str.surfKa = glm::vec3{ 0.0f,0.1f,0.06f };
		str.surfKd = glm::vec3{ 0.0f,0.50980392f,0.50980392f };
		str.surfKs = glm::vec3{ 0.50196078f,0.50196078f,0.50196078f };
		str.surfShininess = 32.0f;
		break;
	case MAGENTA:
		str.surfKa = glm::vec3{ 0.6f,0.0f,0.3f };
		str.surfKd = glm::vec3{ 0.50980392f,0.50980392f, 0.0f };
		str.surfKs = glm::vec3{ 0.50196078f,0.50196078f,0.50196078f };
		str.surfShininess = 32.0f;
		break;
	case RED:
		str.surfKa = glm::vec3{ 0.0f,0.0f,0.06f };
		str.surfKd = glm::vec3{ 0.5f,0.0f,0.0f };
		str.surfKs = glm::vec3{ 0.7f,0.6f,0.6f };
		str.surfShininess = 32.0f;
		break;
	}
	return str;
}