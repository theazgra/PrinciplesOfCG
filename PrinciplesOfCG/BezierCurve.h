#pragma once
//#include <pair>
#include <utility>
#include "Vertex.h"
#include "glm\glm.hpp"
#include "glm\gtx\spline.hpp"
#include "glm\gtx\integer.hpp"

class BezierCurve
{
private:
    float scaling = 1;
    float next_t = 0;

    glm::vec3 points[4];

    float bernstein(int i, int n, float t);
public:
    BezierCurve(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
    ~BezierCurve();

    glm::vec3 getPointOnCurve();
};

