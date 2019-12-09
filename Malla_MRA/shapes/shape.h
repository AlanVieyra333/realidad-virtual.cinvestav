#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
protected:
	float color[3];
public:
	Shape() {
		this->color[0] = 0.5;
		this->color[1] = 0.5;
		this->color[2] = 0.5;
	}

	Shape(float color[]) {
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
	}

	virtual void dibuja_figura(void* data) = 0;
};

#endif // SHAPE_H
