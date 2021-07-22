#ifndef DEQUE_H_
#define DEQUE_H_

template <typename T>
class Deque
{
public:
    /**
     * Create a deque
     * @param seedData an array of the data to prime the array with (defaults to empty)
     * @param seedDataSize the size of the seed data (defaults to 0)
     */
    Deque(T seedData[] = {}, size_t seedDataSize = 0) : container(new T[4]),
                                                        size(4),
                                                        head(0),
                                                        tail(0)
    {
        //First element
        container[0] = seedData[0];

        //Other elements;
        for (size_t i = 1; i < seedDataSize; ++i)
        {
            push_back(seedData[i]);
        }
    }
    ~Deque() {}

    /**
     * Push an element to the back of the deque
     * @param node the node being sent to the back of the deque
     */
    void push_back(T node)
    {
        if (tail == head - 1 ||            // array has wrapped around and is now full
            head == 0 && tail == size - 1) // array is full from beginning to end
        {
            reallocContainer();
        }
        container[tail + 1] = node;
        ++tail;
    }

private:
    void reallocContainer(int offset = 0)
    {
        T *newContainer = new T[size * 2];
        for (size_t i = 0; i < size; i++)
        {
            newContainer[i + offset] = container[i];
        }
        delete container;
        container = newContainer;
        size *= 2;
    }

    size_t size;
    size_t head;
    size_t tail;
    T *container;
};

#endif
