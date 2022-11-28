option(redSB);
option(noredefine);
option(noloadLib);
// option(prot);

LIB "primitiv.lib";

int i, j, k;

ring r(1) = (0), (a, b), dp;

poly f(1) = a ^ 2 + 1; // i
poly f(2) = b ^ 2 - 3; // sqrt(3)

ideal I = f(1), f(2);
ideal J = primitive(I);
string s = "minpoly = " + string(J[1]) + ";";

ring r(2) = (0, b), (x(1..4)), dp;
execute(s);
< "procedures.c";
int i, j, k;

ideal JJ = imap(r(1), J);

poly ii = JJ[2];
poly ss = JJ[3];

list Points = 1 - ii, (1 - ii) * ss, -ss, 1 + 2 * ii, 1 + ii, (-1 - ii) * ss, (-1 + ii) * ss, -1 + ii, 2 - 2 * ii, 0, ii *ss, 2 + ii, -1 - ii, (-1 - ii) * ss, (-1 + ii) * ss, 1 - ii, 1 - ii, (-1 + ii) * ss, (1 + ii) * ss, 1 - ii, -2 - 2 * ii, 0, 0, 2 - 2 * ii, -1 + ii, (-1 + ii) * ss, ss, -1 - 2 * ii, -1 - ii, (1 + ii) * ss, (1 - ii) * ss, 1 - ii, -2 + 2 * ii, 0, -ii *ss, -2 - ii, 1 + ii, (1 + ii) * ss, (1 - ii) * ss, -1 + ii, -1 + ii, (1 - ii) * ss, (-1 - ii) * ss, -1 + ii, 2 + 2 * ii, 0, 0, -2 + 2 * ii;

ideal Intersection = 1;
for (i = 0; i < size(Points) div 4; i++)
{
    Intersection = intersect(Intersection, PointIdeal(list(Points[4 * i + 1], Points[4 * i + 2], Points[4 * i + 3], Points[4 * i + 4])));
}

ideal P(1) = PointIdeal(list(Points[1], Points[2], Points[3], Points[4]));

P(1) = P(1) ^ 5;

deg(std(intersect(P(1), Intersection))[1]);
deg(std(intersect(P(1), Intersection))[2]);
deg(std(intersect(P(1), Intersection))[3]);