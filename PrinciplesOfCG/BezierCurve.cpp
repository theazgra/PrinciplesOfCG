#include "stdafx.h"
#include "BezierCurve.h"

BezierCurve::BezierCurve(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
{
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
    glm::vec3 result = glm::vec3(0);


    for (unsigned int i = 0; i < 4; i++)
    {
        result.x = points[i].x * bernstein(i, 3, next_t);
        result.y = points[i].y * bernstein(i, 3, next_t);
        result.z = points[i].z * bernstein(i, 3, next_t);
    }
    this->next_t += 0.1;

    return result;
}

float BezierCurve::bernstein(int i, int n, float t)
{
    float a = glm::factorial(i) / (glm::factorial(i - n) * glm::factorial(n));
    float b = glm::pow(i, t);
    float c = glm::pow((1 - t), (n - i));
    return (a * b * c);
}
