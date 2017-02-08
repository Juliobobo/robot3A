%Période d'échantillonage
T = 0.02; 

a = 4/(T*T);
b = 2 * kp_teta / (l * T);
c = ki_teta / l;
n = 2;
p = [a b c];
H = hurwitz(p,n);