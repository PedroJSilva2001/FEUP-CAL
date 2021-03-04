// By: Gonçalo Leão

#ifndef CAL_TP3_CLASSES_EXERCISES_H
#define CAL_TP3_CLASSES_EXERCISES_H

#include <vector>
#include <ostream>

// Ex 1
struct Point {
    double x;
    double y;

    Point(double x, double y);
    Point(int x, int y);
    double distance(Point &p) const;
    double distSquare(Point &p) const; // distance squared
    bool operator==(const Point &p) const;
};
std::ostream& operator<<(std::ostream& os, Point &p);

// Auxiliary class to store a solution.
struct Result {
    double dmin; // distance between selected points
    Point p1, p2; // selected points
    Result(double dmin2, Point p1, Point p2);
    Result();
};

void setNumThreads(int num);

// Nearest-points using different algorithms
// Brute-force
Result nearestPoints_BF(std::vector<Point> &vp);
// Brute-force that begins by sorting the points by the X coordinate
Result nearestPoints_BF_SortByX(std::vector<Point> &vp);
// Divide-and-conquer with a single thread
Result nearestPoints_DC(std::vector<Point> &vp);
// Divide-and-conquer with multiple threads (number of threads is set using setNumThreads).
Result nearestPoints_DC_MT(std::vector<Point> &vp);

// Pointer to function that computes nearest points
typedef Result (*NP_FUNC)(std::vector<Point> &vp);

// Ex 2
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j);

#endif //CAL_TP3_CLASSES_EXERCISES_H
