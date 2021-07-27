#ifndef MAZE_H_
#define MAZE_H_
#include <string>

class Maze
{
private:
    int rowCount;
    int colCount;
    int layerCount;
    int ***maze;

public:
    Maze(int ***maze) {}
    ~Maze(void)
    {
        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t i = 0; i < colCount; i++)
            {
                for (size_t k = 0; k < layerCount; k++)
                {
                    delete maze[i][j][k];
                }
            }

            delete[] maze[i][j];
        }

        delete[] maze[i];
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
