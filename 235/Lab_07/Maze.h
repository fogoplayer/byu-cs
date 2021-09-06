#ifndef MAZE_H_
#define MAZE_H_
#include <string>
#include <limits>
#include <fstream>
#include <iostream>

#include "MazeInterface.h"

#define LEFT row, col - 1, layer
#define RIGHT row, col + 1, layer
#define UP row - 1, col, layer
#define DOWN row + 1, col, layer
#define OUT row, col, layer - 1
#define IN row, col, layer + 1

class Maze : public MazeInterface
{
private:
    int rowCount;
    int colCount;
    int layerCount;
    int ***maze;

    enum
    {
        OPEN,
        BLOCKED,
        VISITED,
        EXIT,
        L,
        R,
        U,
        D,
        O,
        I,
    };

public:
    Maze() : rowCount(0), colCount(0), layerCount(0){};
    Maze(int height, int width, int depth, std::ifstream &in) : rowCount(height), colCount(width), layerCount(depth), maze(nullptr)
    {
        std::cout << width << " " << height << " " << depth << " " << std::endl;

        //Layers
        maze = new int **[layerCount];
        for (int i = 0; i < layerCount; i++)
        {
            //Rows
            maze[i] = new int *[rowCount];
            for (int j = 0; j < rowCount; j++)
            {
                //Columns
                maze[i][j] = new int[colCount];
                for (int k = 0; k < colCount; k++)
                {
                    in >> maze[i][j][k];
                    int currChar = maze[i][j][k];
                    std::cout << currChar << " ";
                }

                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    ~Maze(void)
    {
        for (int i = 0; i < layerCount; i++)
        {
            for (int j = 0; j < rowCount; j++)
            {
                delete[] maze[i][j];
            }

            delete[] maze[i];
        }

        delete[] maze;
    }

    /** 
     * Set maze value
	 * @param height
	 * @param width
	 * @param layer
	 * @param value
	 */
    virtual void setValue(int height, int width, int layer, int value)
    {
        return;
    }

    /** 
     * Solve maze
	 * @return true if solveable, else false
	 */
    virtual bool find_maze_path()
    {
        return find_maze_path(0, 0, 0);
    }

    /** 
     * Recursively solve maze
	 * @return true if solveable, else false
	 */
    virtual bool find_maze_path(int row, int col, int layer);

    /**
     * Output maze (same order as input maze)
	 * @return string of 2D layers
	 */
    std::string toString() const;

    /**
     * Overload the insertion operator
     * @return an ostream with the maze
     */
    friend std::ostream &operator<<(std::ostream &os, Maze &maze)
    {
        os << maze.toString();
        return os;
    }
};
#endif

bool Maze::find_maze_path(int row, int col, int layer)
{
    // Outside of array bounds
    if (row < 0 || row >= rowCount || col < 0 || col >= colCount || layer < 0 || layer >= layerCount)
        return false;

    //Blocked and/or already visited
    if (maze[layer][row][col] != OPEN)
        return false;
    if ((row == rowCount - 1) && (col == colCount - 1) && (layer == layerCount - 1))
    {
        maze[layer][row][col] = EXIT;
        return true;
    }

    // Direction to the next done in the path
    maze[layer][row][col] = VISITED;
    if (find_maze_path(LEFT))
    {
        maze[layer][row][col] = L;
        return true;
    }
    if (find_maze_path(RIGHT))
    {
        maze[layer][row][col] = R;
        return true;
    }
    if (find_maze_path(UP))
    {
        maze[layer][row][col] = U;
        return true;
    }
    if (find_maze_path(DOWN))
    {
        maze[layer][row][col] = D;
        return true;
    }
    if (find_maze_path(OUT))
    {
        maze[layer][row][col] = O;
        return true;
    }
    if (find_maze_path(IN))
    {
        maze[layer][row][col] = I;
        return true;
    }

    return false;
}

std::string Maze::toString() const
{
    std::ostringstream os;
    //Layers
    for (int i = 0; i < layerCount; i++)
    {
        os << "Layer " << i + 1 << std::endl;
        //Rows
        for (int j = 0; j < rowCount; j++)
        {
            //Columns
            for (int k = 0; k < colCount; k++)
            {
                char output;
                switch (maze[i][j][k])
                {

                case OPEN:
                    output = '_';
                    break;
                case VISITED:
                    output = '*';
                    break;
                case BLOCKED:
                    output = 'X';
                    break;

                case EXIT:
                    output = 'E';
                    break;

                case L:
                    output = 'L';
                    break;

                case R:
                    output = 'R';
                    break;

                case U:
                    output = 'U';
                    break;

                case D:
                    output = 'D';
                    break;

                case O:
                    output = 'O';
                    break;

                case I:
                    output = 'I';
                    break;

                default:
                    output = maze[i][j][k];
                    break;
                }

                os << " " << output;
            }

            os << std::endl;
        }
    }

    return os.str();
}
