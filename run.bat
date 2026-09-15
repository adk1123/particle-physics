gcc -c vec3_equations.c map.c equations.c projectile.c
gcc vec3_equations.o map.o equations.o projectile.o -o sim
.\sim