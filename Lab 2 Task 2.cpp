/* За допомогю SFML змоделювати рух точки на колі (трохоїда)*/
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;
const int radius = 50;
const Color standartColor(51, 255, 153);

float pow (float a)
{
    return a*a;
}

int main()
{
    bool click = false;
    float angle = 0, tempAngle = 0, radiusTrajekt = 0, cntClick = 0;
    int speed, time = M_PI/2, cnt = 0;

    cout << "Input speed:";
    cin >> speed;

    speed *= 180;

    RenderWindow window(VideoMode(1920, 1080), "SFML works!");

    Color ColorTemp(0,0,0);


    Vector2f inputCenter, inputPoint, tempPoint, TempRadius, TempCenter;
    CircleShape circle, point;

    VertexArray trochoid(LineStrip, 360);
    VertexArray earth(Lines, 2);
    VertexArray lineRadius(Lines, 2);

    circle.setRadius(0);
    point.setRadius(0);
    circle.setOutlineColor(Color(105, 105, 105  ));
    circle.setFillColor(Color(0,0,0,0));
    point.setFillColor(standartColor);
    circle.setOutlineThickness(10);





    bool flag = true;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(radiusTrajekt != 0)
        {
            tempPoint.x =  inputCenter.x + radius * (tempAngle - angle)  - radiusTrajekt*sin(tempAngle);
            tempPoint.y =  inputCenter.y + radiusTrajekt*cos(tempAngle);

            trochoid.append(tempPoint);
            tempAngle += M_PI/speed;

            TempCenter.x = inputCenter.x + radius * (tempAngle - angle);
            TempRadius.x = inputCenter.x + radius * (tempAngle - angle)  - radius*sin(tempAngle);
            TempRadius.y = inputCenter.y + radius*cos(tempAngle);
            lineRadius[1] = TempRadius;
            lineRadius[0] = TempCenter;
            point.setPosition(tempPoint.x - 10, tempPoint.y - 10);
            circle.setPosition(TempCenter.x - radius, TempCenter.y - radius);
            lineRadius[1].color = Color::Green;
            lineRadius[0].color = Color::Green;
        }
        else trochoid.clear();


        if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) click = true;
        if(click && event.type == Event::MouseButtonReleased )
        {
            click = false;
            if(cntClick == 0)
            {
                circle.setPosition(event.mouseButton.x - radius, event.mouseButton.y - radius);
                inputCenter.x = event.mouseButton.x;
                inputCenter.y = event.mouseButton.y;
                TempCenter = inputCenter;
                circle.setRadius(radius);
                TempCenter = inputCenter;
                lineRadius[0] = inputCenter;
                earth.append(Vector2f(0, inputCenter.y + radius+10));
                earth.append(Vector2f(1920, inputCenter.y + radius+10));
            }
            else if(cntClick == 1)
            {
                if( pow(event.mouseButton.y  - inputCenter.y) + pow(event.mouseButton.x  - inputCenter.x) > pow(radius))
                {
                    /*cout << "\nERROR\nPoint isn't in circle\n";
                    window.close();*/
                    ColorTemp = Color(0, 51, 102);
                }
                else
                {
                    ColorTemp = Color(255, 153, 51);
                }
                    inputPoint.x = event.mouseButton.x;
                    inputPoint.y = event.mouseButton.y;
                    float deltaX = abs(inputCenter.x - inputPoint.x);
                    float deltaY = abs(inputCenter.y - inputPoint.y);

                    radiusTrajekt = sqrt(pow(deltaX) + pow(deltaY));
                    angle = acos(deltaY/radiusTrajekt);

                    if(inputPoint.x >= inputCenter.x && inputPoint.y <= inputCenter.y) angle = M_PI  + angle, cout << "Rule 1\n";
                    else if(inputPoint.x <= inputCenter.x && inputPoint.y <= inputCenter.y) angle = M_PI - angle, cout << "Rule 2\n";
                    else if(inputPoint.x <= inputCenter.x && inputPoint.y >= inputCenter.y) angle = angle, cout << "Rule 3\n";
                    else if(inputPoint.x >= inputCenter.x && inputPoint.y >= inputCenter.y) angle = 2 * M_PI - angle, cout << "Rule 4\n";

                    tempAngle = angle;

                    point.setRadius(10);
                    point.setPosition(Vector2f(inputPoint.x - 10, inputPoint.y - 10));
                    lineRadius[1] = (inputPoint);

            }

            cntClick++;
        }


            window.clear(ColorTemp);
            window.draw(earth);
            if(cntClick > 1) window.draw(lineRadius);
            window.draw(circle);
            window.draw(trochoid);
            window.draw(point);
            window.display();

    }



    return 0;
}
