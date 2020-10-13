#include "adaboosting.h"

Classification::Classification(int x[], int y[], int label[], int num) {
    // setup the training set 
    for(int i=0; i<num; i++) {
        Data data;
        data.x = x[i];
        data.y = y[i];
        data.label = label[i];
        data.weight = (double)1/num;
        training_data_.push_back(data);
    }
}

int Classification::WeakJudge(Data &data, WeakClassifier &weak) {
    int label;
    if(weak.vertical==1) {
        if(data.x<weak.value)
            label=1;
        else
            label=0;
    }
    else
    {
        if(data.y>weak.value)
            label=1;
        else
            label=0;
    }
    return label;
}

void Classification::UpdateError(WeakClassifier &weak) {
    int n_data = training_data_.size();
    double error=0;
    for(int i=0; i<n_data; i++) {
        if(training_data_[i].label!=WeakJudge(training_data_[i], weak)) {
            error+=training_data_[i].weight;
        }
    }
    weak.error=error;
}

void Classification::TrainWeak() {
    
}

void Classification::UpdateWeight() {
    int n_data = training_data_.size();
    WeakClassifier weak = weak_.back();

}