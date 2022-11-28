/*
Twisted quartic
*/
option(redSB);
option(noredefine);
option(noloadLib);
option(prot);
LIB "primdec";
LIB "elim.lib";
int n, counter, IsWeddle;

ring r = (32003), (x(1..4)), dp;

< "procedures.c";

int i, j, k, l;

// basis points
list P(1) = 47, 51;
list P(2) = 53, 57;
list P(3) = 1, 1;
list P(4) = 2, 3;
list P(5) = 5, 7;
list P(6) = 11, 13;
list P(7) = 17, 19;
list P(8) = 23, 29;
list P(9) = 31, 37;
list P(10) = 41, 43;

for (i = 1; i <= 10; i++)
{
    P(i) = TwistedQuartic(P(i));
}

list CubicEquation = x(1) ^ 3, x(1) ^ 2 * x(2), x(1) ^ 2 * x(3), x(1) ^ 2 * x(4), x(1) * x(2) ^ 2, x(1) * x(2) * x(3), x(1) * x(2) * x(4), x(1) * x(3) ^ 2, x(1) * x(3) * x(4), x(1) * x(4) ^ 2,

     x(2) ^ 3, x(2) ^ 2 * x(3), x(2) ^ 2 * x(4), x(2) * x(3) ^ 2, x(2) * x(3) * x(4), x(2) * x(4) ^ 2, x(3) ^ 3, x(3) ^ 2 * x(4), x(3) * x(4) ^ 2, x(4) ^ 3;

for (i = 1; i <= 4; i++)
{
    for (j = i; j <= 4; j++)
    {
        list CubicEquation_dx(i, j) = DerivativeEquationList(CubicEquation, x(i));
        CubicEquation_dx(i, j) = DerivativeEquationList(CubicEquation_dx(i, j), x(j));
    }
}

list ListTenPointsInterpolation =
    PointToEquationList(P(1), CubicEquation) +
    PointToEquationList(P(2), CubicEquation) +
    PointToEquationList(P(3), CubicEquation) +
    PointToEquationList(P(4), CubicEquation) +
    PointToEquationList(P(5), CubicEquation) +
    PointToEquationList(P(6), CubicEquation) +
    PointToEquationList(P(7), CubicEquation) +
    PointToEquationList(P(8), CubicEquation) +
    PointToEquationList(P(9), CubicEquation) +
    PointToEquationList(P(10), CubicEquation) +
    CubicEquation_dx(1, 1) +
    CubicEquation_dx(1, 2) +
    CubicEquation_dx(1, 3) +
    CubicEquation_dx(1, 4) +
    CubicEquation_dx(2, 2) +
    CubicEquation_dx(2, 3) +
    CubicEquation_dx(2, 4) +
    CubicEquation_dx(3, 3) +
    CubicEquation_dx(3, 4) +
    CubicEquation_dx(4, 4);

matrix TenPointsInterpolation[20][20] = ListTenPointsInterpolation[1..size(ListTenPointsInterpolation)];

poly TenPointWeddle = det(TenPointsInterpolation);

space();

deg(TenPointWeddle);
int counter;
ideal Intersection = 0;
for (i = 1; i <= 10; i++)
{
    poly T(i) = 0;
    for (j = 1; j <= 4; j++)
    {
        for (k = j; k <= 4; k++)
        {
            for (l = k; l <= 4; l++)
            {
                counter++;
                // print(string(i) + " " + string(j) + string(k) + string(l));
                T(i) = T(i) + subst(diff(diff(diff(TenPointWeddle, x(j)), x(k)), x(l)), x(1), P(i)[1], x(2), P(i)[2], x(3), P(i)[3], x(4), P(i)[4]) * x(j) * x(k) * x(l);
            }
        }
    }
}
Intersection = T(1..10);
Intersection = std(Intersection);
space();

print("dim = " + string(dim(Intersection)));
print("mult = " + string(mult(Intersection)));
print("degs = ");
deg(T(1..10));

counter;

size(T(1..10));

space();
reduce(T(1), PointIdeal(P(1)) ^ 1);
reduce(T(1), PointIdeal(P(1)) ^ 2);
reduce(T(1), PointIdeal(P(1)) ^ 3);
reduce(T(1), PointIdeal(P(1)) ^ 4);

ideal weddlejacobian = jacob(TenPointWeddle);

weddlejacobian = std(weddlejacobian);
weddlejacobian = radical(weddlejacobian);
weddlejacobian = std(weddlejacobian);

space();
dim(weddlejacobian);
mult(weddlejacobian);