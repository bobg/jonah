#include <stack>
#include <iostream>
#include<cassert>
using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    /*Push the starting coordinate(sr, sc) onto the coordinate stack and
        update maze[sr][sc] to indicate that the algorithm has encountered
        it(i.e., set maze[sr][sc] to have a value other than '.').
        While the stack is not empty,
    { Pop the top coordinate off the stack.This gives you the current
            (r,c) location that your algorithm is exploring.
        If the current(r,c) coordinate is equal to the ending coordinate,
            then we've solved the maze so return true!
        Check each place you can move from the current cell as follows :
            If you can move EAST and haven't encountered that cell yet,
                then push the coordinate(r,c + 1) onto the stack and update
                maze[r][c + 1] to indicate the algorithm has encountered it.
            If you can move NORTH and haven't encountered that cell yet,
                then push the coordinate(r - 1,c) onto the stack and update
                maze[r - 1][c] to indicate the algorithm has encountered it.
            If you can move WEST and haven't encountered that cell yet,
                then push the coordinate(r,c - 1) onto the stack and update
                maze[r][c - 1] to indicate the algorithm has encountered it.
            If you can move SOUTH and haven't encountered that cell yet,
                then push the coordinate(r + 1,c) onto the stack and update
                maze[r + 1][c] to indicate the algorithm has encountered it.
    }
        There was no solution, so return false*/
    for (int i = 0; i < nRows; i++) {
        if (maze[i].length() > nCols) {
            return false;
        }
    }

    if (sr < 0 || sr > nRows - 1 || sc < 0 || sc > nCols - 1) {
        return false;
    }

    if (er < 0 || er > nRows - 1 || ec < 0 || ec > nCols - 1) {
        return false;
    }

    stack<Coord> coordstack;

    Coord start(sr, sc);
    Coord end(er, ec);

    coordstack.push(start);

    char replacement_char = '*';
    maze[sr][sc] = replacement_char;

    while (!coordstack.empty()) {
        Coord current = coordstack.top();
        coordstack.pop();
        if (current.r() == er && current.c() == ec) {
            return true;
        }

        char north = maze[current.r() - 1][current.c()];
        char south = maze[current.r() + 1][current.c()];
        char east = maze[current.r()][current.c() + 1];
        char west = maze[current.r()][current.c() - 1];

        if (east != 'X' && east != '*') {
            Coord coordeast(current.r(), current.c() + 1);
            coordstack.push(coordeast);
           
            char replacement_char = '*';
            maze[current.r()][current.c() + 1] = replacement_char;
        }
       
        if (north != 'X' && north != '*') {
            Coord coordnorth(current.r() - 1, current.c());
            coordstack.push(coordnorth);

            char replacement_char = '*';
            maze[current.r() - 1][current.c()] = replacement_char;
        }

        if (west != 'X' && west != '*') {
            Coord coordwest(current.r(), current.c() - 1);
            coordstack.push(coordwest);

            char replacement_char = '*';
            maze[current.r()][current.c() - 1] = replacement_char;
        }

        if (south != 'X' && south != '*') {
            Coord coordsouth(current.r() + 1, current.c());
            coordstack.push(coordsouth);

            char replacement_char = '*';
            maze[current.r() + 1][current.c()] = replacement_char;
        }


    }

    return false;
}

//int main() {
//    Coord s(1, 1);
//    string maze[1] {"hello"};
//    assert(pathExists(maze, 1, 5, 0, 0, 0, 1));
//    cout << "Passed all tests!" << endl;
//}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X..X...X.X",
        "X.XXXX.X.X",
        "X.X.X..X.X",
        "X...X.XX.X",
        "XXX......X",
        "X.X.XXXX.X",
        "X.XXX....X",
        "X...X..X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 5, 3, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
