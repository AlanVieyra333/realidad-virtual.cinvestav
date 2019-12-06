#ifndef FIGURA_H
#define FIGURA_H

class Figura
{
protected:
	float color[3];
public:
	Figura() {
		this->color[0] = 0.5;
		this->color[1] = 0.5;
		this->color[2] = 0.5;
	}

	Figura(float color[]) {
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
	}

	virtual void dibuja_figura(void* data) = 0;
};

#endif // FIGURA_H
