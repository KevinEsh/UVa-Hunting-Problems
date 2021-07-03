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
    //if (fabs(slope) < EPS) return Slope(0.0, true); //pendiente infinita
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
    void shift_to(Tensor&, double);

    Tensor operator%(const Line&);
    bool operator<(const Tensor&);
};

Line::Line(const Tensor &tensor1, const Tensor &tensor2){
    M = Slope(tensor1, tensor2);
    if (M.inf) B = tensor1.x; //pendiente infinita (B = t1.x = t2.x)
    else B = tensor1.y - M.slope * tensor1.x;
}

Line::Line(const Tensor &tensor, const Slope &slope_){
    M = slope_;
    if (M.inf) B = tensor.x; //pendiente infinita
    else B = tensor.y - M.slope * tensor.x;
}

Tensor Line::operator%(const Line &other){
    double x_intersec, y_intersec;
    
    if (M.inf) {
        x_intersec = B;
        y_intersec = other.M.slope * x_intersec + other.B;
    }
    else if (other.M.inf) {
        x_intersec = other.B;
        y_intersec = M.slope * x_intersec + B;
    }
    else {
        x_intersec = (other.B - B)/(M.slope - other.M.slope);
        y_intersec = M.slope * x_intersec + B;
    }

    return Tensor(x_intersec, y_intersec); 
}

double Line::get_slope(){
    return M.slope;
}

double Line::get_abscice(){
    return B;
}

void Line::shift_to(Tensor& point, double distance){
    Tensor unitary;
    if (M.inf){
        if (point.x < B) B -= distance;
        else B += distance;
        return;
    }
    else if (M.slope * point.x - point.y + B < 0)
        {unitary.x = -M.slope; unitary.y = 1.0;}
    else
        {unitary.x = M.slope; unitary.y = -1.0;}    

    unitary.normalizar();
    unitary = unitary*distance;
    B += unitary.y - M.slope * unitary.x;
}

bool Line::operator<(const Tensor& point){ //Esta a la izquierda?
    if (M.inf) return point.x < B; //pendiente infinita
    return M.slope * point.x - point.y + B < 0;
}
//======================================================================