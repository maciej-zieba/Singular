ring r = (0, u), (x(1..4)), dp;
minpoly = u2 - 3;

< "procedures.c";

int i, j;

list P(1..6);
list Q(1..6);

P(1) = 1, 0, 0, 1;
Q(1) = 1, 0, 1, 1;
P(2) = 1, u, 0, 2;
Q(2) = 1, u, 2, 2;
P(3) = -1, u, 0, 2;
Q(3) = -1, u, 2, 2;
P(4) = -1, 0, 0, 1;
Q(4) = -1, 0, 1, 1;
P(5) = -1, -u, 0, 2;
Q(5) = -1, -u, 2, 2;
P(6) = 1, -u, 0, 2;
Q(6) = 1, -u, 2, 2;

ideal red(1..6);
ideal blue(1..6);

red(1) = LineIdeal(P(1), Q(3));
red(2) = LineIdeal(P(2), Q(4));
red(3) = LineIdeal(P(3), Q(5));
red(4) = LineIdeal(P(4), Q(6));
red(5) = LineIdeal(P(5), Q(1));
red(6) = LineIdeal(P(6), Q(2));

blue(1) = LineIdeal(P(1), Q(5));
blue(2) = LineIdeal(P(2), Q(6));
blue(3) = LineIdeal(P(3), Q(1));
blue(4) = LineIdeal(P(4), Q(2));
blue(5) = LineIdeal(P(5), Q(3));
blue(6) = LineIdeal(P(6), Q(4));

for (i = 1; i <= 6; i++)
{
    red(i) = red(i)[1..2];
    blue(i) = blue(i)[1..2];
}

space();
"intersection of red and blue";
for (i = 1; i <= 6; i++)
{
    for (j = 1; j <= 6; j++)
    {
        dim(std(ideal(red(i)[1..2], blue(j)[1..2])));
    }
}

space();
"intersection of red and red";
for (i = 1; i <= 6; i++)
{
    for (j = 1; j <= 6; j++)
    {
        if (i == j)
        {
            "i==j";
            dim(std(ideal(red(i)[1..2], red(j)[1..2])));
        }
        else
        {
            "i<>j";
            dim(std(ideal(red(i)[1..2], red(j)[1..2])));
        }
    }
}

space();
"analogously for blue";