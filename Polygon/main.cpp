#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;
const int triangleSize = 3;
const int squareSize = 4;
struct Point
{
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    double x;
    double y;
};

class Polygon
{
public:
    virtual ~Polygon() {}
    void showCoord();
    double getPerimetr();
    double* getSides();
    virtual void figureType() = 0;
    virtual double getSquare() = 0;
protected:
    Point* arr;
    int numOfTops;
};

void Polygon::showCoord()
{
    for(int i = 0; i < numOfTops; ++i)
    {
        cout << i << ". [" << arr[i].x << ", " << arr[i].y << "]" << endl;
    }
}

double* Polygon::getSides()
{
    Point* temp = new Point[numOfTops];
    for(int i = 0; i < numOfTops; ++i)
    {
        if(i == numOfTops-1)
        {
            temp[i].x = pow(arr[0].x - arr[i].x, 2);
            temp[i].y = pow(arr[0].y - arr[i].y, 2);
        }
        else
        {
            temp[i].x = pow(arr[i+1].x - arr[i].x, 2);
            temp[i].y = pow(arr[i+1].y - arr[i].y, 2);
        }
    }
    double* tempSum = new double[numOfTops];
    for(int i = 0; i < numOfTops; ++i)
    {
        tempSum[i] = sqrt(temp[i].x +temp[i].y);
    }
    delete temp;
    return tempSum;
}

double Polygon::getPerimetr()
{
    double* temp = this->getSides();
    double perimetr = 0;
    for(int i = 0; i < numOfTops; ++i)
    {
        perimetr += temp[i];
    }
    return perimetr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class Square:public Polygon
{
public:
    Square();
    ~Square() { cout<<"deleted"<<endl; }
    Square(Point forA, Point forB, Point forC, Point forD);
    void figureType();
    double getSquare();
    double diagonalLength();
};

Square::Square()
{
    arr = new Point[squareSize];
    numOfTops = squareSize;
}

Square::Square(Point forA, Point forB, Point forC, Point forD)
{
    arr = new Point[squareSize];
    numOfTops = squareSize;
    arr[0] = forA;
    arr[1] = forB;
    arr[2] = forC;
    arr[3] = forD;
}

void Square::figureType()
{
    cout<<"It's a square"<<endl;
}

double Square::getSquare()
{
    double* sides = this->getSides();
    double square = sides[0] * sides[1];
    delete sides;
    return square;
}

double Square::diagonalLength()
{
    double* sides = this->getSides();
    double diagonal = sqrt(2) * sides[0];
    delete sides;
    return diagonal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class Triangle:public Polygon
{
public:
    Triangle();
    ~Triangle() { cout<<"deleted"<<endl; }
    Triangle(Point forA, Point forB, Point forC);
    void figureType();
    double getSquare();
    double* heights();
    double* mediansLength();
    double* bisectorsLength();
    Point medianIntesect();
    Point bisectorsIntersect();
    Point heightsIntersect();
};

Triangle::Triangle()
{
    arr = new Point[triangleSize];
    numOfTops = triangleSize;
}

Triangle::Triangle(Point forA, Point forB, Point forC)
{
    arr = new Point[triangleSize];
    numOfTops = triangleSize;
    arr[0] = forA;
    arr[1] = forB;
    arr[2] = forC;
}

void Triangle::figureType()
{
    cout<<"It's a triangle"<<endl;
}

double Triangle::getSquare()
{
    double* h = heights();
    double* sides = this->getSides();
    double base = sides[0];
    double triangleSqr = (h[0] * base)/2;
    return triangleSqr;
}

Point Triangle::medianIntesect()
{
    Point centr;
    centr.x = (arr[0].x + arr[1].x + arr[2].x)/3;
    centr.y = (arr[0].y + arr[1].y + arr[2].y)/3;
    return centr;
}

double* Triangle::mediansLength()
{
    int a = 0;
    int b = 0;
    int c = 0;
    double redicant = 0;
    double* medians = new double[triangleSize];
    Point* medianPoint = new Point[triangleSize];
    for(int i = 0; i < triangleSize; ++i)
    {
        if(i == 0)
        {
            a = 0;
            b = 1;
            c = 2;
        }
        else if(i == 1)
        {
            a = 1;
            b = 2;
            c = 0;
        }
        else if(i == 2)
        {
            a = 2;
            b = 1;
            c = 0;
        }
        medianPoint[a].x = (arr[b].x + arr[c].x) / 2;
        medianPoint[a].y = (arr[b].y + arr[c].y) / 2;
        redicant = pow((arr[a].x - medianPoint[a].x),2) + pow((arr[a].y - medianPoint[a].y), 2);
        medians[i] = sqrt(redicant);
    }
    delete[] medianPoint;
    return medians;
}

double* Triangle::bisectorsLength()
{
    int a = 0;
    int b = 0;
    int c = 0;
    double redicant = 0;
    double semiperimetr = (this->getPerimetr())/2;
    double* sides = this->getSides();
    double* bisectors = new double[triangleSize];
    for(int i = 0; i < triangleSize; ++i)
    {
        if(i == 0)
        {
            a = 2;
            b = 0;
            c = 1;
        }
        else if(i == 1)
        {
            a = 0;
            b = 1;
            c = 2;
        }
        else if(i == 2)
        {
            a = 1;
            b = 2;
            c = 0;
        }
        redicant = (sides[a] * sides[b]) * (semiperimetr *(semiperimetr - sides[c]));
        bisectors[i] = (2 * sqrt(redicant)) / (sides[a] + sides[b]);
    }
    delete[] sides;
    return bisectors;
}

Point Triangle::bisectorsIntersect()
{
    Point P;//Projection point of bisectors' intersection point on AB
    double* sides = this->getSides();
    double BC = sides[1];
    double AB = sides[2];
    Point A  = arr[0];
    Point B = arr[1];
    Point C = arr[2];
    double ratioProjection = BC / AB;
    P.x = (A.x + (B.x *ratioProjection)) / (1 + ratioProjection);
    P.y = (A.y + (B.y *ratioProjection)) / (1 + ratioProjection);
    double AP = sqrt(pow((P.x - A.x), 2) + pow((P.y - A.y), 2));
    double ratioIntersect = AB / AP;
    Point intersectPoint;
    intersectPoint.x = (C.x + (P.x * ratioIntersect)) / (1 + ratioIntersect);
    intersectPoint.y = (C.y + (P.y * ratioIntersect)) / (1 + ratioIntersect);
    delete[] sides;
    return intersectPoint;
}

double* Triangle::heights()
{
    int a = 0;
    int b = 0;
    int c = 0;
    double semiperimetr = (this->getPerimetr())/2;
    double redicant = 0;
    double* heights = new double[triangleSize];
    double* sides = this->getSides();
    for(int i = 0; i < triangleSize; ++i)
    {
        if(i == 0)
        {
            a = 2;
            b = 0;
            c = 1;
        }
        else if(i == 1)
        {
            a = 0;
            b = 1;
            c = 2;
        }
        else if(i == 2)
        {
            a = 1;
            b = 2;
            c = 0;
        }
        redicant = semiperimetr * (semiperimetr - sides[a]) * (semiperimetr - sides[b]) * (semiperimetr - sides[c]);
        heights[i] = (2 * sqrt(redicant))/sides[a];
    }
    delete[] sides;
    return heights;
}

Point Triangle::heightsIntersect()
{
    Point P;//Projection point of C point on AB
    double* sides = this->getSides();
    double AB = sides[0];
    double BC = sides[1];
    double AC = sides[2];
    Point A  = arr[0];
    Point B = arr[1];
    Point C = arr[2];
    double AP;
    double PB;
    double ACsqr = AC*AC;
    double BCsqr = BC*BC;
    if(ACsqr == BCsqr)
    {
        AP = AB / 2;
        PB = AB / 2;
    }
    else
    {
        AP = ((((ACsqr) - (BCsqr))/ AB) + AB) / 2;
        PB = ((AB + (((BCsqr) - (ACsqr))/AB))) / 2;
    }
    double ratioProjection = AP / PB;
    P.x = (A.x + (B.x *ratioProjection)) / (1 + ratioProjection);
    P.y = (A.y + (B.y *ratioProjection)) / (1 + ratioProjection);
    //similar tiangles CPB and OPA
    double CP = sqrt(pow(AC, 2) - (pow(AP, 2)));
    double sidesRatio = CP / AP;
    double insideRatio = CP / PB;
    double intersectRatio = sidesRatio * insideRatio;//PB ratio to BO
    double PO = CP * intersectRatio;
    double BO = PO - CP;
    double mainCoeff = 0;
    if(BO == 0){ return C;}
    else { mainCoeff = CP / BO; }
    Point inters;
    inters.x = (P.x + (C.x *mainCoeff)) / (1 + mainCoeff);
    inters.y = (P.y + (C.y *mainCoeff)) / (1 + mainCoeff);
    return inters;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void showPoint(Point toShow)
{
    cout<<"["<<toShow.x<<", "<<toShow.y<<" ]"<<endl;
}

void showLengths(double* lengths, int size)
{
    cout<<"----------------------------------------------------------------"<<endl;
    for(int i = 0 ; i < size; ++i)
    {
        cout<<i<<". "<<lengths[i]<<endl;
    }
    cout<<"----------------------------------------------------------------"<<endl;
}

void menu(Polygon* polygonArr[], int polygonSize, Triangle* triangle, Square* square)
{
    system("clear");
    cout<<"------------------------------MENU------------------------------"<<endl;
    cout<<"----------------------------POLYGON-----------------------------"<<endl;
    cout<<"1. Show type and tops of polygon"<<endl;
    cout<<"2. Calculate perimetr"<<endl;
    cout<<"3. Calculate square"<<endl;
    cout<<"---------------------------TRIANGLE-----------------------------"<<endl;
    cout<<"4. Mediands lengths"<<endl;
    cout<<"5. Bisectors lengths"<<endl;
    cout<<"6. Heights lengths"<<endl;
    cout<<"7. Medians intersection point"<<endl;
    cout<<"8. Bisectors intersection point"<<endl;
    cout<<"9. Hights intersection point"<<endl;
    cout<<"----------------------------SQUARE------------------------------"<<endl;
    cout<<"10. Diagonal's length"<<endl;
    cout<<"11. EXIT"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"Please enter your destination\t";
    int target = 0;
    int toAct = 0;
    cin >> target;
    if(target == 11) return;
    if((int)target < 1 || (int)target > 11 )
    {
        cout<<"-------------!!!no such destination!!!-------------"<<endl;
        return;
    }
    if(target == 2 || target == 3)
    {
        cout<<"Please enter a polygon number (0 - triangle / 1 - square)\t";
        cin >> toAct;
        if((toAct != 1) && (toAct != 0))
        {
            cout<<"No such polygon"<<endl;
            return;
        }
    }
    switch(target)
    {
        case 1:
        {
            for(int i = 0; i < polygonSize; ++i)
            {
                polygonArr[i]->figureType();
                polygonArr[i]->showCoord();
            }
            break;
        }
        case 2:
        {
            double perimetr = polygonArr[toAct]->getPerimetr();
            cout << perimetr << endl;
            break;
        }
        case 3:
        {
            double square = polygonArr[toAct]->getSquare();
            cout << square << endl;
            break;
        }
        case 4:
        {
            double* medians =  triangle->mediansLength();
            showLengths (medians, triangleSize);
            delete[] medians;
            break;
        }
        case 5:
        {
            double* bisectors =  triangle->bisectorsLength();
            showLengths (bisectors, triangleSize);
            delete[] bisectors;
            break;
        }
        case 6:
        {
            double* hights =  triangle->heights();
            showLengths (hights, triangleSize);
            delete[] hights;
            break;
        }
        case 7:
        {
            Point mediansIntersect = triangle->medianIntesect();
            showPoint(mediansIntersect);
            break;
        }
        case 8:
        {
            Point bisectorsIntersect = triangle->bisectorsIntersect();
            showPoint(bisectorsIntersect);
            break;
        }
        case 9:
        {
            Point hightsIntersect = triangle->heightsIntersect();
            showPoint(hightsIntersect);
            break;
        }
        case 10:
        {
            double diagonal = square->diagonalLength();
            cout<<diagonal<<endl;
            break;
        }
        default:
        {
            cout<<"-------------no such destination-----------"<<endl;
            break;
        }
    }
    cout<<"Show the menu again?(y/n)\t";
    char ans;
    cin >> ans;
    if(ans == 'y')
    {
        menu(polygonArr, polygonSize, triangle, square);
    }
    else return;
}

int main()
{
    Point A, B, C;
    A.x = 1;
    A.y = 1;
    B.x = 2;
    B.y = 4;
    C.x = 3;
    C.y = 2;
//    A.x = 2;
//    A.y = 1;
//    B.x = 2;
//    B.y = 7;
//    C.x = 4;
//    C.y = 4;
    Triangle* triangle = new Triangle(A, B, C);
    Point I, J, K, L;
    I.x = -1;
    I.y = 1;
    J.x = -1;
    J.y = 6;
    K.x = 4;
    K.y = 6;
    L.x = 4;
    L.y = 1;
    Square* square = new Square(I, J, K, L);
    int polygonSize = 2;
    Polygon* polygonArr[polygonSize];
    polygonArr[0] = triangle;
    polygonArr[1] = square;
    menu(polygonArr, polygonSize, triangle, square);
    delete triangle;
    delete square;
    return 0;
}

