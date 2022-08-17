#include "gtest/gtest.h"

#include <math.h>

#include "../src/geometry.hpp"

TEST(TestGeometry, two_segments_intersection_correctly_computes_intersection_point)
{
    Vec2D p1(0.0f, 1.0f), p2(0.0f, -1.0f), p3(1.0f, 1.0f), p4(-1.0f, 1.0f);
    Segment s1(p1, p2);
    Segment s2(p3, p4);
    Vec2D pintersection = Geometry::computeSegmentsIntersection(s1, s2);
    EXPECT_FLOAT_EQ(pintersection.x, 0.0f);
    EXPECT_FLOAT_EQ(pintersection.y, 1.0f);
}

TEST(TestGeometry, two_parallel_segments_computes_no_intersection_point)
{
    Vec2D p1(0.0f, 0.0f), p2(1.0f, 0.0f), p3(0.0f, 1.0f), p4(1.0f, 1.0f);
    Segment s1(p1, p2);
    Segment s2(p3, p4);
    Vec2D pintersection = Geometry::computeSegmentsIntersection(s1, s2);
    EXPECT_TRUE(std::isnan(pintersection.x));
    EXPECT_TRUE(std::isnan(pintersection.y));
}

TEST(TestGeometry, two_parallel_segments_computes_no_intersection_point2)
{
    Vec2D p1(0.0f, 1.0f), p2(0.0f, -1.0f), p3(-1.0f, 0.0f), p4(-0.9f, 0.0f);
    Segment s1(p1, p2);
    Segment s2(p3, p4);
    Vec2D pintersection = Geometry::computeSegmentsIntersection(s1, s2);
    EXPECT_TRUE(std::isnan(pintersection.x));
    EXPECT_TRUE(std::isnan(pintersection.y));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}