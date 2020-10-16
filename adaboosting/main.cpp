#include <iostream>

#include "adaboosting.h"

using namespace std;

int main() {
    int x[] = {80, 93, 136, 147, 159, 214, 214, 257, 307, 307};
    int y[] = {144, 232, 275, 131, 69, 31, 152, 83, 62, 231};
    int label[] = {1, 1, -1, -1, 1, 1, -1, 1, -1, -1};
    int num = 10;
    Classification classifier = Classification(x, y, label, num, 350, 300);
    printf("%f", log(5.5));
    classifier.TrainStrong(3);

    printf("test: 80, 144 = %d\n", classifier.test(80, 144));
    printf("test: 93, 232 = %d\n", classifier.test(93, 232));
    printf("test: 136, 275 = %d\n", classifier.test(136, 275));
    printf("test: 147, 131 = %d\n", classifier.test(147, 131));
    printf("test: 159, 69 = %d\n", classifier.test(159, 69));
    printf("test: 214, 31 = %d\n", classifier.test(214, 31));
    printf("test: 214, 152 = %d\n", classifier.test(214, 152));
    printf("test: 257, 83 = %d\n", classifier.test(257, 83));
    printf("test: 307, 62 = %d\n", classifier.test(307, 62));
    printf("test: 307, 231 = %d\n", classifier.test(307, 231));

    system("pause");
    return 0;
}
