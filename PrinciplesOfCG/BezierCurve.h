#pragma once

#include <utility>
#include <exception>
#include "glm\glm.hpp"
#include "glm\gtx\spline.hpp"
#include "glm\gtx\integer.hpp"

class BezierCurve
{
private:
    const unsigned int POINT_COUNT = 4;
    float t_increment = 0.1;
    float t = 0;

    glm::vec3 points[4];

    float bernstein(int i, int n, float t);
public:
    BezierCurve();
    BezierCurve(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
    ~BezierCurve();

    glm::vec3 getPointOnCurve();
    void initialize(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float t_increment = 0.1);
    void reverse();

    operator bool() const;

};

