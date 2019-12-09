#include "mra.h"
#include "geom_func.h"
#include <cmath>

MRA::MRA()
{
    T = 3.0;

    k = 0.2;
    m = 0.01;
    b = 8.0*m/T; //0.02667
    dt = 1.0/30.0;

    k1 = 2.0 - dt*(k*dt + b)/m;
	k2 = 1.0 - dt*b/m;
    k3x = k3y = k3z = 0.0;

    set_T(3.0);
    set_v_force({0,0.2,0});

    x_1 = x = 0.0;
    y_1 = y = 0.0;
    z_1 = z = 0.0;

    control = true;
}

MRA::~MRA(){}

void MRA::set_v_force(vector<float> v_force) {
    this->v_force = v_force;
}

void MRA::apply_force() {
    k3x = ( v_force[0] * dt * dt ) / m;
    k3y = ( v_force[1] * dt * dt ) / m;
    k3z = ( v_force[2] * dt * dt ) / m;
}

void MRA::quit_force() {
    k3x = k3y = k3z = 0.0;
}

void MRA::step_deformation() {
    float x_next, y_next, z_next;

    if (control)
    {
        if (vector_mod(this->v_force) != 0 && (k3x != 0 || k3y != 0 || k3z != 0))
        {
            set_T(1.0);
        } else {
            set_T(3.0);
        }
    }
    

    x_next = k1 * x - k2 * x_1 + k3x;
    x_1 = x;
    x   = x_next;

    y_next = k1 * y - k2 * y_1 + k3y;
    y_1 = y;
    y   = y_next;

    z_next = k1 * z - k2 * z_1 + k3z;
    z_1 = z;
    z   = z_next;
}


void MRA::set_T(float T) {
    this->T = T;
    b = 8.0*m/T;                        //0.02667
    k1 = 2.0 - dt*(k*dt + b)/m;
	k2 = 1.0 - dt*b/m;
}