#include "mra.h"
#include "geom_func.h"
#include <cmath>

MRA::MRA()
{
    k = 0.2;
    m = 0.01;
    b = 0.02667;
    dt = 1.0/30.0;

    k1 = 2.0 - dt*(k*dt + b)/m;
	k2 = 1.0 - dt*b/m;
    k3x = k3y = k3z = 0.0;

    set_alpha(0.0);
    set_beta(90.0);
    set_force(0.2);

    x_1 = x = 0.0;
    y_1 = y = 0.0;
    z_1 = z = 0.0;
}

MRA::~MRA(){}

void MRA::set_force(float f) {
    v_force = {0,0,0};
    v_force[0] = cos(beta) * cos(alpha);
    v_force[1] = sin(beta) * cos(alpha);
    v_force[2] = sin(alpha);

    // Normalize
    v_force = normalize_vector(v_force);
    // Establecer fuerza
    v_force = escalar_product(v_force, f);
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

void MRA::set_alpha(float alpha) {
    this->alpha = deg_to_rad(alpha);
}

void MRA::set_beta(float beta) {
    this->beta = deg_to_rad(beta);
}
