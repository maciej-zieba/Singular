option(noredefine);
option(noloadLib);
LIB "elim.lib";
int n, counter, IsWeddle;

for (n = 1; n <= 1000; n++)
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
        list P(i) = random(-1000, 1000), random(-1000, 1000);
        // print(P(i));
    }

    ideal Intersection = 1;
    for (i = 1; i <= 7; i++)
    {
        P(i) = TwistedCubic(P(i));
        Intersection = intersect(Intersection, PointIdeal(P(i)));
    }
    if (mult(std(Intersection)) < 7)
    {
        print(mult(std(Intersection)));
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
    poly OutputIdealSatCounter = sat(SevenPointsInterpolationIdeal, TwistedCubicIdeal)[2];

    if (deg(OutputIdeal) == 4)
    {
        counter++;

        "";
        // print(OutputIdeal);
        if (VarietyEquality(OutputIdeal, SixPointsWeddle) == 1)
        {
            IsWeddle++;
        };
    }
    if (deg(OutputIdeal) > 0)
    {
        OutputIdeal;
    }
    else
    {
        // OutputIdealSatCounter;
    }
    // if (mult(std(Intersection)) < 7)
    // {
    //     // print(VarietyEquality(Intersection, OutputIdeal));
    //     mult(OutputIdeal);
    // }
}

space();
print(string(counter) + "/" + string(n - 1) + " passed.");
print(string(IsWeddle) + "/" + string(counter) + " is Weddle.");