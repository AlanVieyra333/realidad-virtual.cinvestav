import numpy
import math

t = 3.0

k = 0.2         #(Kg/s^2)
m = 0.01        #(Kg)
b = 8.0*m/t      #(Kg/s) - 0.02667
dt = 1.0/30.0   #(s)
f = 0.2

k1 = 2 - (b/m)*dt - (k/m)*dt*dt
k2 = (b/m)*dt - 1
k3 = (f/m)*dt*dt

x_next = 0.0    # X siguiente
x = 0.0         # X actual
x_1 = 0.0       # x anterior

## Pruebas
def set_t(_t):
    global t, b, k1, k2
    t = _t
    b = 8.0*m/_t
    k1 = 2 - (b/m)*dt - (k/m)*dt*dt
    k2 = (b/m)*dt - 1

def set_f(_f):
    global f, k3
    f = _f
    k3 = (f/m)*dt*dt

set_t(1.0)

for s in numpy.arange(0.0, 10.0, dt):
    if s == 2.0:
        set_f(0.1)
    if s == 5.0:
        set_t(3.0)
        set_f(0.0)
    x_next = k1*x + k2*x_1 + k3
    x_1 = x
    x = x_next
    print(s, x_next, end="\n")


