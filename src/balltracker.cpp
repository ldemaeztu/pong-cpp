#include "balltracker.hpp"

#include <iostream>

BallTracker::BallTracker() {
    // Define random generator with Gaussian distribution
    const double mean = 0.0;
    const double stddev = 0.8;
    m_dist = std::normal_distribution<double>(mean, stddev);
}

/** Init ball tracker objects */
void BallTracker::init(){
    int n = 2; // Number of states
    int m = 1; // Number of measurements

    m_dt = 1.0/300; // Time step

    Eigen::MatrixXd A(n, n); // System dynamics matrix
    Eigen::MatrixXd C(m, n); // Output matrix
    Eigen::MatrixXd Q(n, n); // Process noise covariance
    Eigen::MatrixXd R(m, m); // Measurement noise covariance
    Eigen::MatrixXd P(n, n); // Estimate error covariance

    // Discrete LTI projectile motion, measuring position only
    A << 1, m_dt, 0, 1;
    C << 1, 0;

    // Reasonable covariance matrices
    Q << .05, 10.0, 10.0, .05;
    R << 5.0;
    P << .1, .1, .1, .1;

    // Construct the filter
    m_kf = KalmanFilter(m_dt, A, C, Q, R, P);

    // Best guess of initial states
    Eigen::VectorXd x0(n);
    m_t = 0;
    x0 << 0.0, 0.0;
    m_kf.init(m_t, x0);
}

/** Estimate paddle speed given the position of the ball and the position of the paddle */
float BallTracker::update(const float ballY, const float paddleY) {
    Eigen::VectorXd y(1);
    m_t += m_dt;

    //y << ballY + m_dist(m_generator);
    y << ballY - paddleY + m_dist(m_generator);
    m_kf.update(y);    
    Eigen::VectorXd ballPosKalman = m_kf.state().transpose();

    return ballPosKalman(0);
}
