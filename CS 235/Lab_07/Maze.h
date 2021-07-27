#ifndef MAZE_H_
#define MAZE_H_
#include <string>
#include <fstream>
#include <iostream>

class Maze
{
private:
    int rowCount;
    int colCount;
    int layerCount;
    int ***maze;

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
            in.ignore(); // handle the blank line at the top of each layer
            maze[i] = new int *[rowCount];
            for (size_t j = 0; j < rowCount; j++)
            {
                //Columns
                maze[i][j] = new int[colCount];

                std::string currLine;
                getline(in, currLine);
                std::istringstream is(currLine);
                for (size_t k = 0; k < colCount; k++)
                {
                    is >> maze[i][j][k];
                }
                is.ignore();
            }
        }
    }

    ~Maze(void)
    {
        for (size_t i = 0; i < layerCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                for (size_t k = 0; k < rowCount; k++)
                {
                    // delete[] maze[i][j][k];
                }

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
        return "string";
    }
};
#endif
