#include <string>
#include "Mesh.h"
#include <fstream>

class ObjParser {

public:
	ObjParser();
	~ObjParser();

	bool parseObj(const std::string &path, Mesh &mesh);

private:
	std::ofstream logfile;

	bool triangulateObj(Mesh& mesh);
};