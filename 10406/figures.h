//===========================================================================================

Tensor pivot;

class Polygon
{
private:
    vector<Tensor> vertex;
    int num_vertex;
    double area;
    bool convex;
public:
    Polygon() : num_vertex(0), area(-1.0), convex(false) {};
    Polygon(vector<Tensor>&, bool);
    ~Polygon() {};

    void add(const Tensor&);
    double get_area();
    Tensor begin();

    static bool sort_angle(const Tensor&, const Tensor&);
    void print();
    void convex_hull();
    bool is_convex();
    vector<Tensor> get_hull();
};

Polygon::Polygon(vector<Tensor> &vertex_, bool convex_)
: vertex(vertex_), convex(convex_)
{
    num_vertex = vertex_.size();
    area = -1.0;
}

void Polygon::print(){
    cout << "x = [";
    for (int i=0; i < vertex.size(); i++){
        cout << vertex[i].x << ",";
    }

    cout << "]\ny = [";
    for (int i=0; i < vertex.size(); i++){
        cout << vertex[i].y << ",";
    }
    cout << "]\n";
}

void Polygon::add(const Tensor &tensor){
    vertex.push_back(tensor);
    convex = false;
    num_vertex++;
}

double Polygon::get_area(){
    if (area == -1.0){
        area = 0.0;
        if (num_vertex > 2)
            for (int i=0; i < num_vertex -1; i++)
                area += vertex[i] & vertex[i+1]; //producto cruz
            area += vertex[num_vertex-1] & vertex[0]; //el ultimo con el primero
            area = fabs(area) * 0.5;
    }
    return area;
}

Tensor Polygon::begin(){
    if (num_vertex) return pivot;
    return Tensor();
}

bool Polygon::sort_angle(const Tensor &t1, const Tensor &t2){
    Tensor l1 = (t1 - pivot);
    Tensor l2 = (t2 - pivot);

    if ( fabs( l1 & l2 ) < EPS ) //Son colineales? Regresa el mas cercano
        return l1.norma() < l2.norma();

    return (atan2(l1.y, l1.x) - atan2(l2.y, l2.x)) < 0;
}

void Polygon::convex_hull() {

    if (convex) return; //funcion convex_hull() ya fue llamada
    if (num_vertex <= 3) { //Los triangulos y rectas son convexos
        convex = true;
        return;  
    }

    // ALGORITMO DE GRAHAM
    // Encontramos el elemento mas abajo hacia la izquierda 'pivot'
    int p = 0;
    for (int i = 1; i < num_vertex; i++)
        if (vertex[i].y < vertex[p].y || (vertex[i].y == vertex[p].y && vertex[i].x < vertex[p].x))
            p = i;
    pivot = vertex[p];

    //Eliminamos 'pivot' y ordenamos de acuerdo al angulo entre los puntos
    vertex.erase(vertex.begin() + p);
    sort(vertex.begin(), vertex.end(), sort_angle);

    vector<Tensor> convex_vertex;
    convex_vertex.push_back(vertex[num_vertex-2]);
    convex_vertex.push_back(pivot);
    convex_vertex.push_back(vertex[0]);
    int id = 1, cid = 2;
    
    while(id < num_vertex - 2) {
        auto line1 = (convex_vertex[cid] - convex_vertex[cid-1]);
        auto line2 = (vertex[id] - convex_vertex[cid]);

        if( (line1 & line2) > 0 ){ //torca positiva
            convex_vertex.push_back(vertex[id]);
            id++; cid++;}
        else{
            convex_vertex.pop_back();
            cid--;}
    }
    
    vertex = convex_vertex;
    num_vertex = (int)vertex.size();
    convex = true; 
    area = -1.0; //reiniciamos el area
}

vector<Tensor> Polygon::get_hull(){

    if (convex) return vertex; //funcion convex_hull() ya fue llamada
    if (num_vertex <= 3) { //Los triangulos y rectas son convexos
        convex = true;
        return vertex; 
    }

    // ALGORITMO DE GRAHAM
    vector<Tensor> temp_vertex = vertex;
    // Encontramos el elemento mas abajo hacia la izquierda 'pivot'
    int p = 0;
    for (int i = 1; i < num_vertex; i++)
        if (temp_vertex[i].y < temp_vertex[p].y || (temp_vertex[i].y == temp_vertex[p].y && temp_vertex[i].x < temp_vertex[p].x))
            p = i;
    pivot = temp_vertex[p];

    //Eliminamos 'pivot' y ordenamos deacuero al angulo entre los puntos
    temp_vertex.erase(temp_vertex.begin() + p);
    sort(temp_vertex.begin(), temp_vertex.end(), sort_angle);

    vector<Tensor> convex_vertex;
    convex_vertex.push_back(temp_vertex[num_vertex-2]);
    convex_vertex.push_back(pivot);
    convex_vertex.push_back(temp_vertex[0]);
    int id = 1, cid = 2;
    
    while(id < num_vertex - 2) {
        auto line1 = (convex_vertex[cid] - convex_vertex[cid-1]);
        auto line2 = (temp_vertex[id] - convex_vertex[cid]);

        if( (line1 & line2) > 0 ){ //torca positiva
            convex_vertex.push_back(temp_vertex[id]);
            id++; cid++;}
        else{
            convex_vertex.pop_back();
            cid--;}
    }
    
    return convex_vertex;
}

bool Polygon::is_convex(){
    return convex;
}

//===========================================================================================

class Circle
{
private:
    Tensor center;
    double radio;
public:                 
    Circle() : radio(-1.0), center(Tensor()) {};
    Circle(double radio_, const Tensor &center_) : radio(radio_), center(center_) {};
    Circle(Tensor&, Tensor&, Tensor&);
    ~Circle() {};

    bool is_inside(Tensor&);
};

Circle::Circle(Tensor& point1, Tensor &point2, Tensor &point3) {

    //Puntos medios de los puntos dados
    Tensor mid1 = point1 + (point2 - point1)*0.5;
    Tensor mid2 = point2 + (point3 - point2)*0.5;

    //Pendientes de cada segmento
    Slope slope1(point1, point2);
    Slope slope2(point2, point3);
    
    //Ecuacion de rectas perpendiculares a los segmentos
    Line line1(mid1, slope1.perpendicular());
    Line line2(mid2, slope2.perpendicular());

    //Calculamos la intercecion de las dos lineas
    center = line1 % line2;
    radio = (point1 - center).norma();
}

bool Circle::is_inside(Tensor &point){
    return (point - center).norma() < radio;
}

//===========================================================================================

class Rectangule
{
private:
    Tensor upper;
    Tensor lower;
public:
    Rectangule(const Tensor &upper_, const Tensor &lower_): upper(upper_), lower(lower_) {};
    ~Rectangule() {};

    bool is_inside(Tensor&);
};

bool Rectangule::is_inside(Tensor &point){
    return point.x > upper.x && point.x < lower.x && point.y < upper.y && point.y > lower.y;
}

//===========================================================================================

class Triangule
{
private:
    Tensor corner1;
    Tensor corner2;
    Tensor corner3;
    double area;
public:
    Triangule(const Tensor &t1, const Tensor &t2, const Tensor &t3): corner1(t1), corner2(t2), corner3(t3), area(-1.0) {};
    ~Triangule() {};

    double get_area();
    bool is_inside(Tensor&);
};

double Triangule::get_area(){
    if (area == -1.0){
        area = corner1 & corner2;
        area+= corner2 & corner3;
        area+= corner3 & corner1;
        area = fabs(area) * 0.5;
    }
    return area;
}
bool Triangule::is_inside(Tensor &point){
    get_area(); 
    double area_test = 0.0;

    area_test += 0.5*fabs((corner1 & corner2) + (corner2 & point) + (point & corner1));
    area_test += 0.5*fabs((corner2 & corner3) + (corner3 & point) + (point & corner2));
    area_test += 0.5*fabs((corner3 & corner1) + (corner1 & point) + (point & corner3));

    return fabs(area - area_test) < EPS;
}

//===========================================================================================