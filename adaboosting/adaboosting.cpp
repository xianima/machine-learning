#include "adaboosting.h"

Classification::Classification(int x[], int y[], int label[], int num, int x_plant, int y_plant) {
    // setup the training set 
    x_plant_ = x_plant;
    y_plant_ = y_plant;
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
            label=-1;
    }
    else
    {
        if(data.y<weak.value)
            label=1;
        else
            label=-1;
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
    WeakClassifier weak_classifier = {.error = 1};
    WeakClassifier weak_classifier_test = {.vertical=1, .value=0};

    while(weak_classifier_test.value<x_plant_) {
        //weak_classifier_test.value++;
        UpdateError(weak_classifier_test);
        if(weak_classifier_test.error<weak_classifier.error)
            weak_classifier = weak_classifier_test;
        
        weak_classifier_test.value++;
    }
    // change the weak_classifier_test to horizon
    weak_classifier_test.vertical = 0;
    weak_classifier_test.value = 0;

    while(weak_classifier_test.value<y_plant_) {
        //weak_classifier_test.value++;
        UpdateError(weak_classifier_test);
        if(weak_classifier_test.error<weak_classifier.error)
            weak_classifier = weak_classifier_test;
        
        weak_classifier_test.value++;
    }

    weak_classifier.weight = (double)1/2*log((1-weak_classifier.error)/weak_classifier.error);

    weak_.push_back(weak_classifier);

    if(weak_classifier.error>0.5) {
        exit(1);
    }
}

void Classification::UpdateWeight() {
    int n_data = training_data_.size();
    WeakClassifier weak = weak_.back();
    double denom=0;

    for(int i=0; i<n_data; i++) {
        training_data_[i].weight = training_data_[i].weight*exp(-1*weak.weight*training_data_[i].label*WeakJudge(training_data_[i], weak));
        denom+=training_data_[i].weight;
    }
    for(int i=0; i<n_data; i++) {
        training_data_[i].weight = training_data_[i].weight/denom;
    }

}

void Classification::TrainStrong(int n_weak) {
    for(int i=0; i<n_weak; i++) {
        TrainWeak();
        UpdateWeight();
    }
}

int Classification::test(int x, int y) {
    int n_weak = weak_.size();
    double result = 0;
    for(int i=0; i<n_weak; i++) {
        if((weak_[i].vertical==1 && x<weak_[i].value) || (weak_[i].vertical==0 && y<weak_[i].value)) {
            result += weak_[i].weight;
        }
        else
        {
            result -= weak_[i].weight;
        }    
    }
    if(result>=0) {
        return 1;
    }
    else
    {
        return -1;
    }
    
}