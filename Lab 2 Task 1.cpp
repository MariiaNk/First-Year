/* За допомогю SFML намалювати трикутник та точку.
Визначити чи належить точка трикутнику*/
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

using namespace sf;
using namespace std;
const int xSizeWin = 1000, ySizeWin = 800;

int vectMult(Vector2f a, Vector2f b)
{
    return a.x * b.y - a.y * b.x;
}

Vector2f vectMinus(Vector2f a, Vector2f b)
{
    Vector2f tmp(a.x-b.x, a.y-b.y);
    return tmp;
}

int main()
{
    Vector2f Coord[4], ranPoint;
    int cntPoint = 0;
    RenderWindow window(VideoMode(xSizeWin, ySizeWin), "SFML works!");

    ConvexShape triangle;
    CircleShape point(10);
    triangle.setPointCount(3);
    triangle.setFillColor(Color::Green);

    bool click = false, checkPoint = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear();

        if(cntPoint < 3)
        {
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) click = true;
            if(click && event.type == Event::MouseButtonReleased )
            {
                cout << "Up ";
                click = false;
                Vector2f tmp(event.mouseButton.x, event.mouseButton.y);
                Coord[cntPoint] = tmp;
                triangle.setPoint(cntPoint, tmp);
                cout << cntPoint << " "<< Coord[cntPoint].x << " " << Coord[cntPoint].y << "\n";
                cntPoint++;
            }
        }
        else
        {
            window.clear();
            window.draw(triangle);
            if(!(ranPoint.x == 0 && ranPoint.y == 0)) window.draw(point);
            window.display();

            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) click = true;
            if(click && event.type == Event::MouseButtonReleased )
            {
                click = false;
                ranPoint.x = event.mouseButton.x;
                ranPoint.y = event.mouseButton.y;
                cntPoint++;
                point.setPosition(ranPoint);
                cout << "Curr: "<< ranPoint.x << " " << ranPoint.y << "\n";
                checkPoint = true;
            }

            if(checkPoint)
            {
                int minusCnt = 0, plusCnt = 0, tempMult;
                for(int i = 0; i < 3; i++)
                {
                    tempMult = vectMult(vectMinus(Coord[i], ranPoint), vectMinus(Coord[i], Coord[(i+1)%3]));
                    //cout << i << " " << (i+1)%3 << " = " << tempMult << "\n";
                    if(tempMult < 0) minusCnt++;
                    else plusCnt++;
                }
                //cout << minusCnt << " " << plusCnt << "\n";
                if(minusCnt == 3 || plusCnt == 3) cout << "Yes\n";
                else cout << "No\n";
                checkPoint = false;
            }
        }


    }





    return 0;
}
