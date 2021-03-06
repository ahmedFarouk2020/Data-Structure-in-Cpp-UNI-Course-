#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>
#include <iostream>  // for std::cout
#include <fstream>   // for std::ifstream (loading files from disk)
#include <algorithm> // for std::atof
#include <cassert>
#include <utility>

namespace helpers
{

std::pair< char *, int > getFastaDNA(const char *filePath)
{
    std::ifstream input(filePath);
    std::string line, dna;

    if (input)
    {
        while (std::getline(input, line))
        {
            // line may be empty so you *must* ignore blank lines
            // or you have a crash waiting to happen with line[0]
            if (line.empty())
                continue;

            if (line.front() == '>')
            {
                continue;
            }
            else
            {
                dna += line;
            }
        }
    }
    else
    {
        std::cout << "Failed to open file:" << filePath << std::endl;
    }
    char *buffer = new char[dna.size() + 1];
    buffer[dna.size()] = '\0';
    std::copy(dna.begin(), dna.end(), &buffer[0]);
    return {buffer, dna.size()};
}

std::pair<double *, int> getECG(const char *filePath)
{
    std::ifstream f(filePath);
    std::vector<double> ecg;
    std::string line;
    if (f)
        while (std::getline(f, line))
            ecg.push_back(std::stof(line));
    else
        std::cout << "Failed to open file:" << filePath << std::endl;

    double *buffer = new double[ecg.size()];
    std::copy(ecg.begin(), ecg.end(), &buffer[0]);
    return {buffer,ecg.size()};
}

double *getECG(const char *filePath, int &size)
{
    auto [buffer,n] = getECG(filePath);
    size = n;
    return buffer;
}

} // namespace helpers

#endif // HELPERS_HPP
