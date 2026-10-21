#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <vector>

void plotSignal(const std::vector<int>& levels, int samplesPerBit);
void plotSignal(const std::vector<double>& samples, int samplesPerBit);
#endif