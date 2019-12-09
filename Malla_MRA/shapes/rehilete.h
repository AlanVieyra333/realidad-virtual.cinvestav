#ifndef REHILETE_H
#define REHILETE_H

#include "shape.h"

class Rehilete: public Shape
{
public:
	Rehilete(float l);
	void dibuja_figura(void* data);
	void dibuja_aspa(float angle);

private:
	float aspa[3][3];
};

#endif // REHILETE_H
