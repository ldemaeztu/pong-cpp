#include "balltracker.hpp"

#include <iostream>

BallTracker::BallTracker(ConfigLoader* config) : m_config(config) {
    // Define random generator with Gaussian distribution
    const double mean = m_config->get<float>("bT", "mean");
    const double stddev = m_config->get<float>("bT", "stddev");
    m_dist = std::normal_distribution<double>(mean, stddev);
}

/** Init ball tracker objects */
void BallTracker::init(){
    int n = 2; // Number of states
    int m = 1; // Number of measurements

    m_dt = m_config->get<float>("bT", "timestep"); // Time step

    Eigen::MatrixXd A(n, n); // System dynamics matrix
    Eigen::MatrixXd C(m, n); // Output matrix
    Eigen::MatrixXd Q(n, n); // Process noise covariance
    Eigen::MatrixXd R(m, m); // Measurement noise covariance
    Eigen::MatrixXd P(n, n); // Estimate error covariance

    // Discrete LTI projectile motion, measuring position only
    A << 1, m_dt, 0, 1;
    C << 1, 0;

    // Reasonable covariance matrices
    float q1 = m_config->get<float>("bT", "q1");
    float q2 = m_config->get<float>("bT", "q2");
    float r = m_config->get<float>("bT", "r");
    float p = m_config->get<float>("bT", "p");
    Q << q1, q2, q2, q1;
    R << r;
    P << p, p, p, p;

    // Construct the filter
    m_kf = KalmanFilter(m_dt, A, C, Q, R, P);

    // Best guess of initial states
    Eigen::VectorXd x0(n);
    m_t = 0;
    x0 << 0.0, 0.0;
    m_kf.init(m_t, x0);

    // Init to a stable position where paddle and ball are at the same position
    int steps = m_config->get<int>("bT", "stabilization_steps");
    for (int i = 0; i < steps; i++)
        update(0.0f, 0.0f);
}

/** Estimate paddle speed given the position of the ball and the position of the paddle */
float BallTracker::update(const float ballY, const float paddleY) {
    Eigen::VectorXd y(1);
    m_t += m_dt;

    y << ballY - paddleY + m_dist(m_generator);
    m_kf.update(y);    
    Eigen::VectorXd ballPosKalman = m_kf.state().transpose();

    return m_config->get<float>("bT", "speed_multiplier") * ballPosKalman(0);
}
