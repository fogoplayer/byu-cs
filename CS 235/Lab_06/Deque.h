#ifndef DEQUE_H_
#define DEQUE_H_

template <typename T>
class Deque
{
private:
    T *[] container;

public:
    /**
     * Create a deque
     * @param seedData an array of the data to prime the array with (defaults to empty)
     * @param seedDataSize the size of the seed data (defaults to 0)
     */
    Deque(T[] seedData = {}, size_t seedDataSize = 0)
    {
        container = new T[seedDataSize == 0 ? 4 : seedDataSize];
        for (size_t i = 0; i < seedDataSize; ++i)
        {
            // container.push_back(seedData[i]);
        }
    }
    ~Deque();
};

#endif