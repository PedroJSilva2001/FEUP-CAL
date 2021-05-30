#include "exercises.h"

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

double Point::distance(Point &p) const {
    return sqrt((x-p.x) * (x-p.x)  + (y-p.y) * (y-p.y));
}

double Point::distSquare(Point &p) const {
    return (x-p.x) * (x-p.x)  + (y-p.y) * (y-p.y);
}

bool Point::operator==(const Point &p) const {
    return (x == p.x && y == p.y);
}

std::ostream& operator<<(std::ostream& os, Point &p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

Result::Result(double dmin, Point p1, Point p2): dmin(dmin), p1(p1), p2(p2) {
}

Result::Result(): Result(MAX_DOUBLE, Point(0,0), Point(0,0)) {
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num) {
    numThreads = num;
}

// Auxiliary functions to sort vector of points by X or Y axis.
static void sortByX(std::vector<Point> &v, int left, int right) {
    std::sort(v.begin( ) + left, v.begin() + right + 1,
              [](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(std::vector<Point> &v, int left, int right) {
    std::sort(v.begin( ) + left, v.begin() + right + 1,
              [](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

Result nearestPoints_BF(std::vector<Point> &vp) {
    Result res;
    double minDistance = MAX_DOUBLE;

    for(int i = 0; i < vp.size(); i++){
        for(int j = i+1; j < vp.size(); j++){
            if(vp[i].distance(vp[j]) < minDistance){
                minDistance = vp[i].distance(vp[j]);
                res = Result(minDistance, vp[i], vp[j]);
            }
        }
    }

    return res;
}

Result nearestPoints_BF_SortByX(std::vector<Point> &vp) {
    Result res;
    sortByX(vp, 0, vp.size()-1);
    double minDistance = MAX_DOUBLE;

    for(int i = 0; i < vp.size(); i++){
        for(int j = i+1; j < vp.size(); j++){
            if(vp[i].distance(vp[j]) < minDistance){
                minDistance = vp[i].distance(vp[j]);
                res = Result(minDistance, vp[i], vp[j]);
            }
            if(vp[j].x - vp[i].x > minDistance) break;
        }
    }

    return res;
}

Result nearestPoints_DC(std::vector<Point> &vp, int l, int r) {
    if(r-l == 1) return {vp[l].distance(vp[r]), vp[l], vp[r]};
    if(r-l < 1) return {};
    int m = (l+r)/2;
    Result left = nearestPoints_DC(vp,l,m), right = nearestPoints_DC(vp,m,r);
    Result d = left.dmin < right.dmin ? left : right;
    auto leftIt = lower_bound(vp.begin() + l,vp.begin() + r + 1,Point(vp[m].x-d.dmin,-MAX_DOUBLE),[](Point a, Point b){
        if(a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    auto rightIt = lower_bound(vp.begin() + l,vp.begin() + r + 1,Point(vp[m].x+d.dmin,MAX_DOUBLE),[](Point a, Point b){
        if(a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    std::vector<Point> vy(leftIt, rightIt);
    sortByY(vy, 0, vy.size()-1);
    for(unsigned i = 0; i < vy.size(); i++){
        for(unsigned j = i+1; j < std::min((unsigned long long )i+8, vy.size()); j++){
            if(vy[i].distance(vy[j]) < d.dmin){
                d = Result(vy[i].distance(vy[j]), vy[i], vy[j]);
            }
            if(vy[j].y - vy[i].y > d.dmin) break;
        }
    }
    return d;
}

Result nearestPoints_DC(std::vector<Point> &vp) {
    sortByX(vp, 0, vp.size()-1);
    Result res = nearestPoints_DC(vp,0,vp.size()-1);
    return res;
}

Result nearestPoints_DC_MT(std::vector<Point> &vp, int l, int r, int threads){
    if(r-l == 1) return {vp[l].distance(vp[r]), vp[l], vp[r]};
    if(r-l < 1) return {};
    int m = (l+r)/2;
    Result left, right;
    if(threads > 1) {
        std::thread t([&]() {left = nearestPoints_DC_MT(vp, l, m,threads/2);});
        right = nearestPoints_DC_MT(vp, m, r,threads/2);
        t.join();
    } else {
        left = nearestPoints_DC_MT(vp, l, m,threads), right = nearestPoints_DC_MT(vp, m, r,threads);
    }
    Result d = left.dmin < right.dmin ? left : right;
    auto leftIt = lower_bound(vp.begin() + l,vp.begin() + r + 1,Point(vp[m].x-d.dmin,-MAX_DOUBLE),[](Point a, Point b){
        if(a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    auto rightIt = lower_bound(vp.begin() + l,vp.begin() + r + 1,Point(vp[m].x+d.dmin,MAX_DOUBLE),[](Point a, Point b){
        if(a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    std::vector<Point> vy(leftIt, rightIt);
    sortByY(vy, 0, vy.size()-1);
    for(unsigned i = 0; i < vy.size(); i++){
        for(unsigned j = i+1; j < std::min((unsigned long long)i+8, vy.size()); j++){
            if(vy[i].distance(vy[j]) < d.dmin){
                d = Result(vy[i].distance(vy[j]), vy[i], vy[j]);
            }
            if(vy[j].y - vy[i].y > d.dmin) break;
        }
    }
    return d;
}

Result nearestPoints_DC_MT(std::vector<Point> &vp) {
    sortByX(vp, 0, vp.size()-1);
    Result res = nearestPoints_DC_MT(vp, 0, vp.size()-1,numThreads);
    return res;
}
/*d)
 * Variante de ciclo : expressão inteira, não negativa e decrescente
 *                    vp.size - i é o variante de ciclo porque:
 *                       - i e vp.size são ambos inteiros logo vp.size - i, também será inteira;
 *                       - como i \in [0, vp.size-1], 0 <= vp.size - i <= vp.size ou seja é não negativa
 *                       - como i é incrementado (i++), é decrescente
 * Invariante de ciclo : propriedade que é verdadeira antes e após de cada iteração no ciclo
 *                    - res (invariante) -> distância entre os 2 pontos mais próximos um estando em vp
 *                    e o outro em c1 = {vp[0], ..., vp[i-1]}
 *                    - em i = 0, c1 = {}, min não existe e o resultado é max_double
 *                    - nas sucessivas iterações res continua a ter a distância mínima pois procurámos
 *                    um novo mínimo entre vp[i] e todos os seguintes (vp[i+1], ..., vp[vp.size-1]),
 *                    incrementando-se i e acrescentando-se vp[i] em c1. Assim, o invariante continua
 *                    verdadeiro para a nova iteração
 *                    - No final, a pós-condição de res ser a distância mínima é garantida porque no final
 *                    c1 tem todos os pontos de vp.
 *
 */
/// TESTS ///
#include <gtest/gtest.h>
#include <fstream>
#include <time.h>
#include <sys/timeb.h>
#include <random>
#include <stdlib.h>

#define REL_PATH "../TP3/" // relative path to the tests

/**
 * Auxiliary function to read points from file to vector.
 */
void readPoints(std::string in, std::vector<Point> &vp) {
    std::ifstream is(REL_PATH + in);
    vp.clear();
    if (!is) {
        std::cerr << "Failed to read file " << in << "." << std::endl;
        return;
    }
    while (!is.eof()) {
        double x, y;
        is >> x >> y;
        Point p(x,y);
        vp.push_back(p);
    }
}

/**
 * Auxiliary functions to generate random sets of points.
 */
void shuffle(std::vector<Point> &vp, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, right - left +1);
    for (int i = left; i < right; i++){
        int k = i + dis(gen) % (right - i + 1);
        Point tmp = vp[i];
        vp[i] = vp[k];
        vp[k] = tmp;
    }
}

void shuffleY(std::vector<Point> &vp, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, right - left +1);
    for (int i = left; i < right; i++){
        int k = i + dis(gen) % (right - i + 1);
        double tmp = vp[i].y;
        vp[i].y = vp[k].y;
        vp[k].y = tmp;
    }
}

// Generates a vector of n distinct points with minimum distance 1.
void generateRandom(int n, std::vector<Point> &vp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n-1);

    vp.clear();
    // reference value for reference points (r, r), (r, r+1)
    int r = dis(gen);
    vp.push_back(Point(r,r));
    vp.push_back(Point(r,r+1));
    for (int i = 2; i < n; i++)
        if (i < r)
            vp.push_back(Point(i, i));
        else
            vp.push_back(Point(i+1, i+2));
    shuffleY(vp, 2, n-1);
    shuffle(vp, 0, n-1);
}

// Similar, but with constant X.
void generateRandomConstX(int n, std::vector<Point> &vp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n-1);

    vp.clear();
    // reference value for min dist
    int r = dis(gen);
    int y = 0;
    for (int i = 0; i < n; i++) {
        vp.push_back(Point(0, y));
        if (i == r)
            y++;
        else
            y += 1 + dis(gen) % 100;
    }
    shuffleY(vp, 0, n-1);
}

/**
 * Auxiliary functions to obtain current time and time elapsed
 * in milliseconds.
 * Something like GetTickCount but portable.
 * It rolls over every ~ 12.1 days (0x100000/24/60/60)
 * Use GetMilliSpan to correct for rollover
 */
int GetMilliCount() {
    timeb tb;
    ftime( &tb );
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int GetMilliSpan(int nTimeStart) {
    int nSpan = GetMilliCount() - nTimeStart;
    if (nSpan < 0)
        nSpan += 0x100000 * 1000;
    return nSpan;
}

int testNP(std::string name, std::vector<Point> &points, double dmin, NP_FUNC func, std::string alg) {
    int nTimeStart = GetMilliCount();
    Result res = (func)(points);
    int nTimeElapsed = GetMilliSpan(nTimeStart);
    std::cout << alg << "; " << name << "; " << nTimeElapsed << "; ";
    std::cout.precision(17);
    std::cout << res.dmin << "; " << res.p1 << "; " << res.p2 << std::endl;
    EXPECT_NEAR(dmin, res.dmin, 0.01);
    return nTimeElapsed;
}

/**
 * Runs the given algorithm (func) for an input file (in)
 * and checks the expected result (res).
 * Prints result and performance information.
 */
int testNPFile(std::string in, double dmin, NP_FUNC func, std::string alg) {
    std::vector<Point> pontos;
    readPoints(in, pontos);
    return testNP(in, pontos, dmin, func, alg);
}

int testNPRand(int size, std::string name, double dmin, NP_FUNC func, std::string alg) {
    std::vector<Point> pontos;
    generateRandom(size, pontos);
    return testNP(name, pontos, dmin, func, alg);
}

int testNPRandConstX(int size, std::string name, double dmin, NP_FUNC func, std::string alg) {
    std::vector<Point> pontos;
    generateRandomConstX(size, pontos);
    return testNP(name, pontos, dmin, func, alg);
}

/**
 * Runs the given algorithm for the existent data files.
 */

void testNearestPoints(NP_FUNC func, std::string alg) {
    std::cout << "algorithm; data set; time elapsed (ms); distance; point1; point2" << std::endl;
    int maxTime = 10000;
    if ( testNPFile("Pontos8", 11841.3, func, alg) > maxTime)
        return;
    if ( testNPFile("Pontos64", 556.066, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos1k", 100.603, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos16k", 13.0384, func, alg) > maxTime)
        return;
    /*
    // Uncomment to use more tests
    if (testNPFile("Pontos32k", 1.0, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos64k", 1.0, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos128k", 0.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x40000, "Pontos256k", 1.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x80000, "Pontos512k",  1.0, func, alg) > maxTime)
        return;
    if ( testNPRand(0x100000, "Pontos1M",  1.0, func, alg) > maxTime)
        return;
    if ( testNPRand(0x200000, "Pontos2M",  1.0, func, alg) > maxTime)
        return;
    */
}

TEST(TP3_Ex1, testNP_BF) {
    testNearestPoints(nearestPoints_BF, "Brute force");
}

TEST(TP3_Ex1, testNP_BF_SortedX) {
    testNearestPoints(nearestPoints_BF_SortByX, "Brute force, sorted by x");
}

TEST(TP3_Ex1, testNP_DC) {
    testNearestPoints(nearestPoints_DC, "Divide and conquer");
}

TEST(TP3_Ex1, testNP_DC_2Threads) {
    setNumThreads(2);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 2 threads");
}

TEST(TP3_Ex1, testNP_DC_4Threads) {
    setNumThreads(4);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 4 threads");
}

TEST(TP3_Ex1, testNP_DC_8Threads) {
    setNumThreads(8);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 8 threads");
}