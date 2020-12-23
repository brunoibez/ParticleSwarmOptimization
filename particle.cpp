#include "particle.h"
#include "constants.h"
#include <iostream>
#include <cmath>

std::string Particle::optimizationFunction = StringConstants::deJongFunction1;
QPoint Particle::bestGlobalPos = QPoint();
float Particle::bestGlobalRes = ModelDefaultConstants::defaultBestGlobalRes;
float Particle::inercia1 = ModelDefaultConstants::defaultInercia1;
float Particle::inercia2 = ModelDefaultConstants::defaultInercia2;


Particle::Particle(int x, int y, int vx, int vy)
{
    this->qpoint = QPoint((x % WindowConstants::WIDTH) - WindowConstants::WIDTH/2, (y % WindowConstants::HEIGHT) - WindowConstants::HEIGHT/2);
    this->qvelocity = QPoint(vx,vy);
    this->inerciaVelocity = 1;
    this->setOptimizationValue();

}


void Particle::updatePosition(){
    this->qpointnext = this->qpoint + this->qvelocity;

    if (this->qpointnext.x() > WindowConstants::WIDTH){
        this->qpointnext.setX(WindowConstants::WIDTH);
    }else if (this->qpointnext.x() < 0){
        this->qpointnext.setX(0);
    }

    if (this->qpointnext.y() > WindowConstants::WIDTH){
        this->qpointnext.setY(WindowConstants::WIDTH);
    }else if (this->qpointnext.y() < 0){
        this->qpointnext.setY(0);
    }

    this->recomputeVelocity();
    this->qpoint = this->qpointnext;
    this->qvelocity = this->qvelocitynext;
    this->setOptimizationValue();
}


void Particle::setOptimizationValue(){
    this->localRes = this->getOptimizationValue();
    this->checkIfBestLocalPos();
    this->checkIfBestGlobalPos();
}


float Particle::getOptimizationValue(){
    float res;
    if (Particle::optimizationFunction == StringConstants::deJongFunction1){
        res = this->optimizationFunctionDeJong1();
    }
    else{
        res = 10000;
    }

    return res;
}

float Particle::optimizationFunctionDeJong1(){
    float x = this->qpoint.x();
    float y = this->qpoint.y();

    float res = pow(x,2) + pow(y,2);

    return res;
}

void Particle::recomputeVelocity(){
   float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
   float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

   this->qvelocitynext = this->inerciaVelocity * this->qvelocity + Particle::inercia1 * r1 * (this->bestLocalPos - this->qpoint) + Particle::inercia2 * r2 * (this->bestGlobalPos - this->qpoint);
   this->inerciaVelocity = this->inerciaVelocity * 0.8;
}

void Particle::checkIfBestGlobalPos(){
    if (this->localRes < this->bestGlobalRes){
        Particle::bestGlobalRes = this->localRes;
        Particle::bestGlobalPos = this->qpoint;
    }
}

void Particle::checkIfBestLocalPos(){
    if (this->localRes < this->bestLocalRes){
        this->bestLocalRes = this->localRes;
        this->bestLocalPos = this->qpoint;
    }
}


QPoint Particle::getPrintPoint(){
    int x = this->qpoint.x() + WindowConstants::WIDTH/2;
    int y = this->qpoint.y() + WindowConstants::HEIGHT/2;
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;

    QPoint qprintpoint = QPoint(x,y);
    return qprintpoint;
}

void Particle::clearGlobalVariables(){
    Particle::bestGlobalPos = QPoint();
    Particle::bestGlobalRes = ModelDefaultConstants::defaultBestGlobalRes;
    Particle::inercia1 = ModelDefaultConstants::defaultInercia1;
    Particle::inercia2 = ModelDefaultConstants::defaultInercia2;
}



