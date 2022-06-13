#include <random>

#include "kalman.hpp"

class BallTracker {
public:
    BallTracker();
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
};