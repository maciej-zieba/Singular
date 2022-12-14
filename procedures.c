proc space()
{
    print("");
    print("----------------------------------------------------------------");
    print("");
}

proc PointIdeal(list @P)
{
    matrix M[2][4] = @P[1], @P[2], @P[3], @P[4],
           x(1), x(2), x(3), x(4);
    ideal I = wedge(M, 2);

    return (I)
}

proc SetIdeal(list @P)
{
    int i;
    ideal I = 1;
    for (i = 1; i <= size(@P); i++)
    {
        I = intersect(I, PointIdeal(P(i)));
    }
    print(I);

    return (std(I))
}

proc LineIdeal(list @P(1), list @P(2))
{
    ideal I = intersect(PointIdeal(@P(1)), PointIdeal(@P(2)));
    return (std(I))
}

proc SecondOrdinaryPower(list @P)
{
    ideal I = SetIdeal(@P) ^ 2;

    return (std(I))
}

proc FifthSymbolicPower(list @P)
{
    int i;
    ideal I = 1;
    for (i = 1; i <= size(@P); i++)
    {
        I = intersect(I, PointIdeal(P(i)) ^ 5);
    }

    return (std(I))
}

proc IsContainment(list @P)
{
    ideal I = reduce(FifthSymbolicPower(@P), SecondOrdinaryPower(@P));
    I = std(I);
    if (I[1] == poly(0))
    {
        print("Containment is true.");
    }
    else
    {
        print("Containment is false.");
        // print(n);
        quit;
    }
}

proc PointToEquationList(list @P, list @eq)
{
    int i;
    for (i = 1; i <= size(@eq); i++)
    {
        @eq[i] = subst(@eq[i],
                       x(1), @P[1],
                       x(2), @P[2],
                       x(3), @P[3],
                       x(4), @P[4]);
    }
    @eq[1] = subst(@eq[1], x(1), 1);

    return (@eq);
}

proc DerivativeEquationList(list @eq, poly @f)
{
    int i;
    for (i = 1; i <= size(@eq); i++)
    {
        @eq[i] = diff(@eq[i], @f);
    }

    return (@eq);
}

// fix or trash
// proc ComplexMult(list @P(1), list @P(2))
// {
//     if (@P(1) * @P(2) == 0)
//     {
//         exit;
//     }

//     list P = @P(1)[1] * @P(2)[1] - @P(1)[2] * @P(2)[2],
//          @P(1)[1] * @P(2)[2] + @P(1)[2] * @P(2)[1],
//          @P(1)[3] * @P(2)[3];

//     return (P);
// }

proc TwistedCubic(list @P)
{
    list P = poly(@P[1] ^ 3), poly(@P[1] ^ 2 * @P[2]), poly(@P[1] * @P[2] ^ 2), poly(@P[2] ^ 3);
    return (P);
}

proc TwistedQuartic(list @P)
{
    int a = 1;
    int b = 7;
    list P = poly(@P[1] ^ 4 - a * @P[1] ^ a * @P[2]), poly(@P[1] ^ 3 * @P[2] - 3 * @P[1] ^ 2 * @P[2] ^ 2), poly(b * @P[1] ^ 2 * @P[2] ^ 2 - @P[1] * @P[2] ^ 3), poly(b * @P[1] * @P[2] ^ 3 - @P[2] ^ 4);
    return (P);
}

proc VarietyEquality(ideal @I, ideal @J)
{
    @I = std(radical(std(@I)));
    @J = std(radical(std(@J)));
    if ((reduce(@I, @J) == 0) * (reduce(@J, @I) == 0))
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

proc PointFromIdeal(ideal @I)
{
    list point;
    @I = std(I);
    if (size(@I) < 3 + size(@I) > 3)
    {
        exit;
    }
    if (size(coef(@I[1], x(1))) == 4)
    {
        point[1]
    }
    if ((size(coef(@I[1], x(2))) == 4))
}