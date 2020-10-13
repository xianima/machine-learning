#include <iostream>

#include "adaboosting.h"

using namespace std;

int main() {
    int x[] = {80, 93, 136, 147, 159, 214, 214, 257, 307, 307};
    int y[] = {144, 232, 275, 131, 69, 31, 152, 83, 62, 231};
    int label[] = {1, 1, -1, -1, 1, 1, -1, 1, -1, -1};
    int num = 10;
    Classification classifier = Classification(x, y, label, num);
    classifier.TrainStrong(3);

}
