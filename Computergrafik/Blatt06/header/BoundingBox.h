#pragma once

class BoundingBox {
public:
	BoundingBox();
	~BoundingBox();

	float max_x = 0;
	float max_y = 0;
	float max_z = 0;
	float min_x = 0;
	float min_y = 0;
	float min_z = 0;

	float sizeX = 0;
	float sizeY = 0;
	float sizeZ = 0;

	float centerX = 0;
	float centerY = 0;
	float centerZ = 0;
};