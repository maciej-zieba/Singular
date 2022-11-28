option(noredefine);
option(noloadLib);
// option(prot);

LIB "primitiv.lib";

for (int n = 2; n <= 15; n++)
{
    ring r(1) = (0), (a, b), dp;

    < "minimal_polynomials.c";

    ideal I = cc(n), ss(n), a ^ 2 + b ^ 2 - 1;
    ideal J = primitive(I);
    string s = "minpoly = " + string(J[1]) + ";";

    ring r(2) = (0, b), (x(1..4)), dp;
    execute(s);
    < "procedures.c";
    int i, j, k;

    ideal JJ = imap(r(1), J);

    poly cos = JJ[2];
    poly sin = JJ[3];

    n--;

    list P(0..n);
    list Q(0..n);

    P(0) = 1, 0, 0, 1;
    Q(0) = 1, 0, 1, 1;

    for (i = 1; i <= n; i++)
    {
        P(i) = P(i - 1)[1] * cos - P(i - 1)[2] * sin, P(i - 1)[1] * sin + P(i - 1)[2] * cos, 0, 1;
        Q(i) = P(i);
        Q(i)
        [3] = 1;
    }

    ideal red(0..n);
    ideal blue(0..n);

    int twist = 1;

    for (i = 0; i <= n; i++)
    {
        red(i) = LineIdeal(P(i % (n + 1)), Q((i + twist) % (n + 1)));
        blue(i) = LineIdeal(Q((i + twist) % (n + 1)), P((i + 2 * twist) % (n + 1)));
    }
    k = 0;
    space();
    // "intersection of red and blue";
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (dim(std(ideal(red(i)[1..2], blue(j)[1..2]))) == 1)
            {
                k++;
            }
        }
    }
    print(string(k) + " ? " + string((n + 1) ^ 2));
    // "intersection of red and red (analogously for blue)";
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == j)
            {
                // "i==j"; // 2
                if (dim(std(ideal(red(i)[1..2], red(j)[1..2]))) < 2)
                {
                    print("Error");
                };
                if (dim(std(ideal(blue(i)[1..2], blue(j)[1..2]))) < 2)
                {
                    print("Error");
                };
            }
            else
            {
                // "i<>j"; // 0
                if (dim(std(ideal(red(i)[1..2], red(j)[1..2]))) > 0)
                {
                    print("Error");
                };
                if (dim(std(ideal(blue(i)[1..2], blue(j)[1..2]))) > 0)
                {
                    print("Error");
                };
            }
        }
    }
    n++;
    print(n);
}