#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define EPS 10e-9

class Tensor
{

public:
    double x, y;
    Tensor(): x(0.0), y(0.0) {}
    Tensor(double x_, double y_) : x(x_), y(y_) {}
    Tensor(const Tensor &p) : x(p.x), y(p.y) {}
    ~Tensor() {};

    bool operator==(const Tensor&) const;
    bool operator!=(const Tensor&) const;
    bool operator< (const Tensor&) const;
    Tensor operator+(const Tensor&) const;
    Tensor operator-(const Tensor&) const;
    double operator&(const Tensor&) const;
    double operator*(const Tensor&) const;
    Tensor operator*(double) const;

    double distance(const Tensor&);
    double norma();
    void normalizar();
};


bool Tensor::operator==(const Tensor &other) const{
    return (fabs(x - other.x ) < EPS && (fabs(y - other.y) < EPS ));
}

bool Tensor::operator!=(const Tensor &other) const{
    return (fabs(x - other.x ) > EPS || (fabs(y - other.y) > EPS ));
}

bool Tensor::operator<(const Tensor &other) const{
    if (fabs(x - other.x) < EPS )
        return y < other.y;
    else
        return x < other.x;
}

Tensor Tensor::operator+(const Tensor &other) const{
    Tensor tensor(x, y);
    tensor.x += other.x;
    tensor.y += other.y;
    return tensor;
}

Tensor Tensor::operator-(const Tensor &other) const{
    Tensor tensor(x, y);
    tensor.x -= other.x;
    tensor.y -= other.y;
    return tensor;
}

double Tensor::operator&(const Tensor &other) const{
    return x*other.y - y*other.x;
}

double Tensor::operator*(const Tensor &other) const{
    return x*other.x + y*other.y;
}

Tensor Tensor::operator*(double alpha) const{
    return Tensor(x*alpha, y*alpha);
}

double Tensor::distance(const Tensor &other){
    return sqrt( pow(x-other.x,2) + pow(y-other.y,2) );
}

double Tensor::norma(){
    return sqrt(x*x + y*y);
}

void Tensor::normalizar(){
    double norm = norma();
    x /= norm;
    y /= norm; 
    return;
}

//===================================================================

#include "lines.h"
#include "figures.h"