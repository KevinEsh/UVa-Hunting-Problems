class UFDSet {

  public:

    UFDSet(int size);
    ~UFDSet() {};
    int find(int a);
    bool is_same_parent(int a, int b);
    void union_sets(int a, int b);
    int get_disjoint_sets();
    int get_size(int a);

  private:
  
    int size;
    vector<int> pset;
    vector<int> set_size;
};

UFDSet::UFDSet(int size) {
  this->size = size;

  set_size.assign(size, 1);
  pset.assign(size, 0);

  for (int i = 0; i < size; i++)
    pset[i] = i;
}

int UFDSet::find(int a) {
  return pset[a] == a ? a : (pset[a] = find(pset[a]));
}

bool UFDSet::is_same_parent(int a, int b) {
  return find(a) == find(b);
}

void UFDSet::union_sets(int a, int b) {
  if (is_same_parent(a, b)) return;

  size--;
  set_size[find(b)] += set_size[find(a)];
  pset[find(a)] = find(b);
}

int UFDSet::get_disjoint_sets() {
  return size;
}

int UFDSet::get_size(int a) {
  return set_size[find(a)];
}