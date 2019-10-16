#ifndef REHILETE_H
#define REHILETE_H

class Rehilete
{
public:
	Rehilete(float l);
	void dibuja_figura(float angle);
	void dibuja_aspa(float angle);

private:
	float aspa[3][3];
};

#endif // REHILETE_H
