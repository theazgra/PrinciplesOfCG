#include "stdafx.h"
#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
    this->t = -1;
}

BezierCurve::BezierCurve(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
{
    this->t = 0;
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->points[3] = p4;
}

BezierCurve::~BezierCurve()
{

}

glm::vec3 BezierCurve::getPointOnCurve()
{
    if (this->t < 0)
        throw new std::exception("Bezier curve was not initiliazed with points!");

    glm::vec3 result = glm::vec3(0);

    for (unsigned int i = 0; i < POINT_COUNT; i++)
    {
        result.x += points[i].x * bernstein(i, (POINT_COUNT - 1), t);
        result.y += points[i].y * bernstein(i, (POINT_COUNT - 1), t);
        result.z += points[i].z * bernstein(i, (POINT_COUNT - 1), t);
    }            
    this->t += t_increment;

    return result;
}

void BezierCurve::initialize(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float t_increment)
{
    this->t_increment = t_increment;
    this->t = 0;
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->points[3] = p4;
}

void BezierCurve::reverse()
{
    if (t < 0)
        t = 0;
    else if (t > 1)
        t = 1;

    t_increment *= -1;
}

BezierCurve::operator bool() const
{
    return (t >= 0 && t <= 1);
}

float BezierCurve::bernstein(int i, int n, float t)
{
    float a = glm::factorial(n) / (glm::factorial(n - i) * glm::factorial(i));
    float b = glm::pow(t, i);
    float c = glm::pow((1 - t), (n - i));
    return (a * b * c);
}
