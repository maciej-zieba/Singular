option(noredefine);
option(noloadLib);
LIB "elim.lib";
int n, counter, IsWeddle;

ring r = (0, t), (x(1..4)), dp;

< "procedures.c";

int i, j;

// basis points
list P(1) = 1, 0;
list P(2) = 0, 1;
list P(3) = 1, 1;
list P(4) = 2, 3;
list P(5) = 5, 7;
list P(6) = 11, 13;

system("random", n);
list P(7) = random(-1000, 1000), random(-1000, 1000);
list P(8) = random(-1000, 1000), random(-1000, 1000);

ideal Intersection = 1;
for (i = 1; i <= 8; i++)
{
    P(i) = TwistedCubic(P(i));
}

ideal TwistedCubicIdeal = x(1) * x(3) - x(2) ^ 2,
      x(2) * x(4) - x(3) ^ 2,
      x(1) * x(4) - x(2) * x(3);

list QuadricEquation = x(1) ^ 2, x(1) * x(2), x(1) * x(3), x(1) * x(4), x(2) ^ 2, x(2) * x(3), x(2) * x(4), x(3) ^ 2, x(3) * x(4), x(4) ^ 2;

for (i = 1; i <= 4; i++)
{
    list QuadricEquation_dx(i) = DerivativeEquationList(QuadricEquation, x(i));
}

list ListSevenPointsInterpolation =
    PointToEquationList(P(1), QuadricEquation) +
    PointToEquationList(P(2), QuadricEquation) +
    PointToEquationList(P(3), QuadricEquation) +
    PointToEquationList(P(4), QuadricEquation) +
    PointToEquationList(P(5), QuadricEquation) +
    PointToEquationList(P(6), QuadricEquation) +
    PointToEquationList(P(7), QuadricEquation) +
    QuadricEquation_dx(1) +
    QuadricEquation_dx(2) +
    QuadricEquation_dx(3) +
    QuadricEquation_dx(4);

matrix SevenPointsInterpolation[11][10] = ListSevenPointsInterpolation[1..size(ListSevenPointsInterpolation)];

ideal SevenPointsWeddle = wedge(SevenPointsInterpolation, 10);

space();

list SecondListSevenPointsInterpolation =
    PointToEquationList(P(1), QuadricEquation) +
    PointToEquationList(P(2), QuadricEquation) +
    PointToEquationList(P(3), QuadricEquation) +
    PointToEquationList(P(4), QuadricEquation) +
    PointToEquationList(P(5), QuadricEquation) +
    PointToEquationList(P(6), QuadricEquation) +
    PointToEquationList(P(8), QuadricEquation) +
    QuadricEquation_dx(1) +
    QuadricEquation_dx(2) +
    QuadricEquation_dx(3) +
    QuadricEquation_dx(4);

matrix SecondSevenPointsInterpolation[11][10] = SecondListSevenPointsInterpolation[1..size(SecondListSevenPointsInterpolation)];

ideal SecondSevenPointsWeddle = wedge(SecondSevenPointsInterpolation, 10);

// print(reduce(SevenPointsWeddle, SecondSevenPointsWeddle));
// print(reduce(SecondSevenPointsWeddle, SevenPointsWeddle));
