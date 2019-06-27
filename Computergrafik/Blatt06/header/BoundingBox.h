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
};