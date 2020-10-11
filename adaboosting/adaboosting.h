#ifndef ADABOOSTING_H
#define ADABOOSTING_H

#include <iostream>
#include <vector>

using namespace std;

struct Data {
    int x;
    int y;
    int label;
    double weight;
};

struct WeakClassifier {
    int vertical; // 1: vertical classifier; 0: horizontal classifier
    int value;
    double error;
    double weight;
};

class Classification
{
private:
    vector<Data> training_data_;
    vector<WeakClassifier> weak_;
public:
    Classification(int x[], int y[], int label[]);
    void UpdateWeight();
    void TrainWeak();
    void TrainStrong();
    int test(int x, int y);
};

#endif
