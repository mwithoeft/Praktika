#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

enum Mat { EMERALD, RUBY, RED, GREEN, BLUE, WHITE, YELLOW, CYAN, MAGENTA };
struct MaterialStr {
	glm::vec3 surfKa;
	glm::vec3 surfKd;
	glm::vec3 surfKs;
	float surfShininess;
};

class Material {
public:
	Material();
	void setMaterial(Mat m);
	MaterialStr getMaterial();

private:
	Mat material;
};