#ifndef MAZE_H_
#define MAZE_H_
#include <string>
#include <limits>
#include <fstream>
#include <iostream>

class Maze
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
        VISTED,
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
        for (size_t i = 0; i < layerCount; i++)
        {
            //Rows
            maze[i] = new int *[rowCount];
            for (size_t j = 0; j < rowCount; j++)
            {
                //Columns
                maze[i][j] = new int[colCount];
                for (size_t k = 0; k < colCount; k++)
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
        for (size_t i = 0; i < layerCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                delete[] maze[i][j];
            }

            delete[] maze[i];
        }
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
        return true;
    }

    /**
     * Output maze (same order as input maze)
	 * @return string of 2D layers
	 */
    virtual std::string toString() const
    {
        std::ostringstream os;
        //Layers
        for (size_t i = 0; i < layerCount; i++)
        {
            //Rows
            for (size_t j = 0; j < rowCount; j++)
            {
                //Columns
                for (size_t k = 0; k < colCount; k++)
                {
                    char output;
                    switch (maze[i][j][k])
                    {
                    case OPEN:
                        output = '_';
                        break;

                    case BLOCKED:
                        output = 'X';
                        break;

                    default:
                        break;
                    }

                    os << output << " ";
                }

                os << std::endl;
            }

            os << std::endl;
        }

        return os.str();
    }

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
