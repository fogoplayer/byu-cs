#ifndef CAR_H_
#define CAR_H_

struct Car
{
    /**
     * Create a car
     * @param data an unsigned int to store in the car
     * @return a new Car
     */
    Car(unsigned int data = 0) : carData(data) {}
    unsigned int carData;
};

#endif