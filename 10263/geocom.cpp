#include <cmath>
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

    bool operator==(const Tensor&);
    Tensor operator+(const Tensor&);
    Tensor operator-(const Tensor&);
    double operator&(const Tensor&);
    double operator*(const Tensor&);
    Tensor operator*(double);

    double distance(const Tensor&);
    double norma();
    void normalizar();
};


bool Tensor::operator== (const Tensor &other) {
    return (fabs(x - other.x ) < EPS && (fabs(y - other.y) < EPS ));
}

Tensor Tensor::operator+(const Tensor &other){
    Tensor tensor(x, y);
    tensor.x += other.x;
    tensor.y += other.y;
    return tensor;
}

Tensor Tensor::operator-(const Tensor &other){
    Tensor tensor(x, y);
    tensor.x -= other.x;
    tensor.y -= other.y;
    return tensor;
}

double Tensor::operator&(const Tensor &other){
    return fabs(x*other.y - y*other.x);
}

double Tensor::operator*(const Tensor &other){
    return x*other.x + y*other.y;
}

Tensor Tensor::operator*(double alpha){
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

//=====================================================================

class Segment
{
private:
    Tensor tensor1;
    Tensor tensor2;
    double lenght;
public:
    Segment() : tensor1(Tensor()), tensor2(Tensor()), lenght(-1.0) {size();}
    Segment(const Tensor &t1, const Tensor &t2) : tensor1(t1), tensor2(t2), lenght(-1.0) {size();}
    Segment(double a1, double a2, double b1, double b2) : tensor1(Tensor(a1, a2)), tensor2(Tensor(b1, b2)), lenght(-1.0) {size();}
    ~Segment() {};

    void set_tensor1(double, double);
    void set_tensor2(double, double);

    double size();
    double distance_to(Tensor&);
    double line_distance_to(Tensor&);
    Tensor closer_to(Tensor&);
};

void Segment::set_tensor1(double x, double y){
    tensor1.x = x;
    tensor1.y = y;
    lenght = -1.0;
}

void Segment::set_tensor2(double x, double y){
    tensor2.x = x;
    tensor2.y = y;
    lenght = -1.0;
}

double Segment::size(){
    if (lenght == -1.0)
        lenght = (tensor2 - tensor1).norma();
    
    return lenght;
}

double Segment::line_distance_to(Tensor &other){
    Tensor segment = tensor2 - tensor1;
    Tensor point = other - tensor1;
    return fabs((segment *  point)/lenght); //proyeccion a la linea
}

double Segment::distance_to(Tensor &other){
    Tensor segment = tensor2 - tensor1;
    Tensor point = other - tensor1;
    double dot = (segment *  point)/lenght; //proyeccion al segmento 
    
    if (dot < 0.0 ) return point.norma();
    if (dot > lenght ) return (other - tensor2).norma();
    else return (segment & point)/lenght; //proyeccion ortogonal
}

Tensor Segment::closer_to(Tensor &other){
    Tensor segment = tensor2 - tensor1;
    Tensor point = other - tensor1;
    double dot = (segment *  point)/lenght; //proyeccion al segmento 
    
    if (dot < 0.0 ) return tensor1;
    if (dot > lenght ) return tensor2;
    else return tensor1 + (segment)*(dot/lenght); //proyeccion ortogonal
}