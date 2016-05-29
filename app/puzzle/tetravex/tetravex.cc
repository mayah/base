#include <iostream>
#include <sstream>
#include <vector>

// Caution:
// The order of input is north, west, east, south.
// However the output if north, east, south, west.

class Tetra {
public:
    Tetra() : Tetra(0, 0, 0, 0) {}
    Tetra(int north, int east, int south, int west) :
        north_(north),
        east_(east),
        south_(south),
        west_(west)
    {
    }

    int north() const { return north_; }
    int east() const { return east_; }
    int south() const { return south_; }
    int west() const { return west_; }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << '('
           << north() << ','
           << east() << ','
           << south() << ','
           << west() << ')';
        return ss.str();
    }

private:
    int north_;
    int east_;
    int south_;
    int west_;
};

bool iter(const std::vector<Tetra>& tetras, int N,
          int pos, std::vector<std::vector<Tetra>>* field, std::vector<int>* used)
{
    if (pos == N * N)
        return true;

    const int y = pos / N;
    const int x = pos % N;

    for (int i = 0; i < N * N; ++i) {
        if ((*used)[i])
            continue;
        if (x != 0 && tetras[i].west()  != (*field)[y][x - 1].east())
            continue;
        if (y != 0 && tetras[i].north() != (*field)[y - 1][x].south())
            continue;

        (*used)[i] = true;
        (*field)[y][x] = tetras[i];
        // cout << pos << " ";
        // tetras[i].print();
        if (iter(tetras, N, pos + 1, field, used)) { return true; }
        (*used)[i] = false;

    }

    return false;
}

void solve(const std::vector<Tetra>& tetras, int N)
{
    std::vector<std::vector<Tetra> > field(N, std::vector<Tetra>(N));
    std::vector<int> used(N * N);

    if (!iter(tetras, N, 0, &field, &used)) {
        std::cout << "Impossible" << std::endl;
        return;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << field[i][j].to_string() << std::endl;
        }
        std::cout << std::endl;
    }
}

int main(void)
{
    int N;
    while (std::cin >> N, N) {
        std::vector<Tetra> tetras(N * N);
        for (int i = 0; i < N * N; ++i) {
            int n, w, e, s;
            std::cin >> n >> w >> e >> s;
            tetras[i] = Tetra(n, e, s, w);
        }
        solve(tetras, N);
    }

    return 0;
}
