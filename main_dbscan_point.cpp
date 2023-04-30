#include <iostream>
#include <vector>
#include <cmath>
#include "dbscan.hpp"

using namespace std;

struct Point
{  
    double x; // first coordinate
    double y; // second coordinate 
    
    Point(double n_x = 0.0, double n_y = 0.0): x(n_x), y(n_y){}
    double calculateDistance(const Point& pointTarget)
    {
        return sqrt(pow(this->x - pointTarget.x, 2) + pow(this->y - pointTarget.y, 2));
    }
};

int main(){
    int n; 
    cin >> n;
    vector<Point> points(n);
    for(auto &p : points)
    {
        cin >> p.x >> p.y;
    }
    
    int total_pts = points.size();
    double** distance_matrix = new double*[total_pts];
    for(int i = 0; i < total_pts; ++i)
    {
        distance_matrix[i] = new double[total_pts];
        for(int j = 0; j < total_pts; ++j){
            distance_matrix[i][j] = points[i].calculateDistance(points[j]);
        }
    }

    double eps = 3;
    int m_minPts = 2;
    DBSCAN clustering(eps, m_minPts);
    clustering.fit(distance_matrix, total_pts, "BFS");
    
    for(auto id : clustering.labels) cout << id << " ";
    cout << endl;
}