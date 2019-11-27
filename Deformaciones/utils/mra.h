#ifndef MRA_H
#define MRA_H

class MRA
{
private:
    /* data */
public:
    float x0 = 0;
    float x_1, x, x1;
    float k3x;

    float y0 = 0;
    float y_1, y, y1;
    float k3y;

    float z0 = 0;
    float z_1, z, z1;
    float k3z;

    MRA(/* args */);
    ~MRA();
};


#endif // MRA_H