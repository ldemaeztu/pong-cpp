#ifndef BALLTRACKER_H
#define BALLTRACKER_H 

#include <random>

#include "configloader.hpp"
#include "kalman.hpp"

class BallTracker {
public:
    BallTracker(ConfigLoader* config);
    void init();
    float update(const float ballY, const float paddleY);

private:
    // Kalman related variables
    KalmanFilter m_kf;
    double m_t;
    double m_dt;

    // Noise generation objects
    std::normal_distribution<double> m_dist;
    std::default_random_engine m_generator;

    // Config loader
    ConfigLoader* m_config;     
};

#endif