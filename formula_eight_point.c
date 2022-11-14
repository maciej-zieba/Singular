
// option(prot);

LIB "ring.lib";
ring r = (3, a(1..4), b(1..4), c(1..4)), (x(1..4)), dp;

< "procedures.c";

int i;
list P(1) = 1, 0, 0, 0;
list P(2) = 0, 1, 0, 0;
list P(3) = 0, 0, 1, 0;
list P(4) = 0, 0, 0, 1;
list P(5) = 1, 1, 1, 1;
list P(6) = a(1..4);
// list P(6) = 1,2,3,5;
list P(7) = b(1..4);
// list P(7) = -1,2,-3,2;
list P(8) = c(1..4);

// formula for the eight point from the set of seven points

// list SixPoints = P(1..6); // list of 6 points
list SevenPoints = P(1..7); // list of 7 points
// list EightPoints = P(1..8); // list of 8 points

// ideal SixPointsIdeal = SetIdeal(SixPoints);
ideal SevenPointsIdeal = SetIdeal(SevenPoints);
size(SevenPointsIdeal);
// ideal EightPointsIdeal = SetIdeal(EightPoints);

ideal NetQuadric = SevenPointsIdeal[1..3];

for (i = 1; i <= 7; i++)
{
    NetQuadric = sat(NetQuadric, PointIdeal(P(i)))[1];
}
ideal EightPointIdeal = NetQuadric;
EightPointIdeal = std(EightPointIdeal);

space();

size(EightPointIdeal);
deg(EightPointIdeal[1..3]);

space();

formula_eight_point.c
    Displaying locus_eight_points.c.