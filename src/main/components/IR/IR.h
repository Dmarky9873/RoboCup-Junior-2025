#ifndef IR_H
#define IR_H

class IR {
  public:

    float* getReadingsArr();
    double* getPWsArr();
    void printReadingsArr();
    void printPWsArr();
    void initIR();

};

template <typename T, size_t N>
constexpr size_t arrayLength(const T (&)[N]) {
    return N;
}

#endif