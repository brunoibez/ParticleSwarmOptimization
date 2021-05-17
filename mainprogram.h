#ifndef MAINPROGRAM_H
#define MAINPROGRAM_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <vector>
#include "particle.h"

class MainProgram
{
public:
    MainProgram();
    QPixmap refreshWindow();
    void paintPoint(QPixmap * q, Particle * particle);
    void restartPoints();
    void setNumberOfParticles(int numberOfParticles);
    void updatePointsPositions();
    void setPixmap();
    void setOptimizationFunction(std::string function);
    void setInercia1(float value);
    void setInercia2(float value);
    void setInercialWeight(float value);
    void evaluateVelocity();
    void evaluateDistanceToOptimum();
    void checkIfOptimumSeen(int iteration);
    void clearAnalysisVectors();
    void analysisAlgorithm(int iteration);
    std::vector <Particle *> particles;
    std::vector <Particle *> particlesFirstIteration;
    std::vector <float> distances_to_minimum;
    std::vector <float> norms_of_velocity;
    QPixmap * qpixMap;
    float minValue;
    QPoint minValuePosition;
    int iterationMinimumSeen;
   static int numberMaxOfIterations;

};

#endif // MAINPROGRAM_H
