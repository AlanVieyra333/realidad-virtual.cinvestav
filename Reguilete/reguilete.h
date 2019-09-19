#ifndef REGUILETE_H
#define REGUILETE_H

class Reguilete
{
public:
	Reguilete(float l);
	void dibuja_figura(float angle);
	void dibuja_aspa(float angle);

private:
	float aspa[3][3];
};

#endif // REGUILETE_H
