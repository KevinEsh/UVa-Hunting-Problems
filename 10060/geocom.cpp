#include <cmath>
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

    bool operator==(const Tensor&);
    bool operator!=(const Tensor&);
    bool operator<(const Tensor&);
    Tensor operator+(const Tensor&);
    Tensor operator-(const Tensor&);
    double operator&(const Tensor&);
    double operator*(const Tensor&);
    Tensor operator*(double);

    double distance(const Tensor&);
    double norma();
    void normalizar();
};


bool Tensor::operator==(const Tensor &other) {
    return (fabs(x - other.x ) < EPS && (fabs(y - other.y) < EPS ));
}

bool Tensor::operator!=(const Tensor &other) {
    return (fabs(x - other.x ) > EPS || (fabs(y - other.y) > EPS ));
}

bool Tensor::operator<(const Tensor &other) {
    return fabs(x - other.x) > EPS ? (x > other.x) : (y > other.y);
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
    return x*other.y - y*other.x;
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
    else return fabs(segment & point)/lenght; //proyeccion ortogonal
}

Tensor Segment::closer_to(Tensor &other){
    Tensor segment = tensor2 - tensor1;
    Tensor point = other - tensor1;
    double dot = (segment *  point)/lenght; //proyeccion al segmento 
    
    if (dot < 0.0 ) return tensor1;
    if (dot > lenght ) return tensor2;
    else return tensor1 + (segment)*(dot/lenght); //proyeccion ortogonal
}

//==========================================================

class Slope
{
public:
    bool inf;
    double slope;

    Slope() : slope(0.0), inf(false) {};
    Slope(double slope_, bool inf_) : slope(slope_), inf(inf_) {}; 
    Slope(const Tensor&, const Tensor&);
    ~Slope() {};

    Slope perpendicular();
};

Slope::Slope(const Tensor &t1, const Tensor &t2) 
{
    double deno = t2.x - t1.x;
    double nume = t2.y - t1.y;

    if (fabs(deno) < EPS) {
        inf = true;
        slope = 0.0;
    }
    else {
        inf = false;
        slope = nume/deno;
    }
}

Slope Slope::perpendicular(){
    if (inf) return Slope(0.0, false); //pendiente cero
    if (fabs(slope) < EPS) return Slope(0.0, true); //pendiente infinita
    else return Slope(-1.0/slope, false); //pendiente perpendicular
}

//====================================================================

class Line
{
private:
    Slope M;
    double B;
public:
    Line(const Tensor&, const Tensor&);
    Line(const Tensor&, const Slope&);
    ~Line() {};

    double get_slope();
    double get_abscice();

    Tensor operator%(const Line&);
};

Line::Line(const Tensor &tensor1, const Tensor &tensor2){
    M = Slope(tensor1, tensor2);
    if (M.inf) B = tensor1.x; //pendiente infinita
    else B = tensor1.y - M.slope * tensor1.x;
}

Line::Line(const Tensor &tensor, const Slope &slope_){
    M = slope_;
    if (M.inf) B = tensor.x; //pendiente infinita
    else B = tensor.y - M.slope * tensor.x;
}

Tensor Line::operator%(const Line &other){
    double x_intersec, y_intersec;
    
    if (M.inf) x_intersec = B;
    if (other.M.inf) x_intersec = other.B;
    else x_intersec = (other.B - B)/ (M.slope - other.M.slope);
    y_intersec = M.slope * x_intersec + B;

    return Tensor(x_intersec, y_intersec); 
}

double Line::get_slope(){
    return M.slope;
}

double Line::get_abscice(){
    return B;
}

//======================================================================

class Polygon
{
private:
    vector<Tensor> vertex;
    int num_vertex;
    double area;
    bool closed;
public:
    Polygon() : num_vertex(0), area(-1.0), closed(false) {};
    ~Polygon() {};

    void add(const Tensor&);
    void close();
    double get_area();
    Tensor begin();
};

void Polygon::add(const Tensor &tensor){
    vertex.push_back(tensor);
    num_vertex++;
}

void Polygon::close(){
    vertex.push_back(vertex[0]);
    closed = true;
}

double Polygon::get_area(){
    if (area == -1.0 || closed){
        area = 0.0;
        if (num_vertex > 2)
            for (int i=0; i < num_vertex; i++)
                area += vertex[i] & vertex[i+1]; //producto cruz
            area = fabs(area) * 0.5;
    }
    return area;
}

Tensor Polygon::begin(){
    if (num_vertex) return vertex[0];
    return Tensor();
}