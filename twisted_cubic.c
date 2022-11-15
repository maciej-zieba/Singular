option(noredefine);
option(noloadLib);
LIB "elim.lib";
int n, counter, IsWeddle;

for (n = 1; n <= 10000; n++)
{
    ring r = (0), (x(1..4)), dp;

    < "procedures.c";

    int i, j;

    // basis points
    list P(1) = 1, 0;
    list P(2) = 0, 1;
    list P(3) = 1, 1;
    system("random", n);
    for (i = 4; i <= 7; i++)
    {
        list P(i) = random(-100, 100), random(-100, 100);
        // print(P(i));
    }

    for (i = 1; i <= 7; i++)
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

    list ListSixPointsInterpolation =
        PointToEquationList(P(1), QuadricEquation) +
        PointToEquationList(P(2), QuadricEquation) +
        PointToEquationList(P(3), QuadricEquation) +
        PointToEquationList(P(4), QuadricEquation) +
        PointToEquationList(P(5), QuadricEquation) +
        PointToEquationList(P(6), QuadricEquation) +
        QuadricEquation_dx(1) +
        QuadricEquation_dx(2) +
        QuadricEquation_dx(3) +
        QuadricEquation_dx(4);

    matrix SixPointsInterpolation[10][10] = ListSixPointsInterpolation[1..size(ListSixPointsInterpolation)];

    ideal SixPointsWeddle = det(SixPointsInterpolation);

    list ListSevenPointsInterpolation =
        ListSixPointsInterpolation + PointToEquationList(P(7), QuadricEquation);

    matrix SevenPointsInterpolation[11][10] = ListSevenPointsInterpolation[1..size(ListSevenPointsInterpolation)];

    ideal SevenPointsInterpolationIdeal = wedge(SevenPointsInterpolation, 10);

    ideal OutputIdeal = sat(SevenPointsInterpolationIdeal, TwistedCubicIdeal)[1];

    if (deg(OutputIdeal) == 4)
    {
        counter++;
        "";
        print(OutputIdeal);
        if (VarietyEquality(OutputIdeal, SixPointsWeddle) == 1)
        {
            IsWeddle++;
        };
    }
}
space();
print(string(counter) + "/" + string(n - 1) + " passed.");
print(string(IsWeddle) + "/" + string(counter) + " is Weddle.");