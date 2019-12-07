#ifndef MRA_H
#define MRA_H

#include <vector>

using namespace std;

class MRA
{
private:
    float dt, k, m, b;
    float k1, k2;

    void set_T(float T);
public:
    vector<float> v_force;

    float x_1, x;
    float k3x;

    float y_1, y;
    float k3y;

    float z_1, z;
    float k3z;

    float T;
    bool control;

    MRA(/* args */);
    ~MRA();
    void init();
    void set_v_force(vector<float> v_force);
    void apply_force();
    void quit_force();
    void step_deformation();
};


#endif // MRA_H