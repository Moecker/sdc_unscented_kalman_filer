#pragma once

#include <vector>

#include "Eigen/Dense"

#include "measurement_package.h"

#include "laser_manager.h"
#include "radar_manager.h"
#include "sigmapoint_manager.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class UnscentedKalmanFilter
{
  public:
    UnscentedKalmanFilter();

    /// @brief Processes a measurement package
    /// @param meas_package The latest measurement data of either radar or laser
    void ProcessMeasurement(MeasurementPackage meas_package);

    /// @brief PredictionStep Predicts sigma points, the state, and the state covariance matrix
    /// @param delta_t Time between k and k+1 in s
    void PredictionStep(double delta_t);

    /// @brief Initializes the Kalman filter with a first given measurement
    void InitializeWithFirstMasurement(const MeasurementPackage& meas_package);

    /// @brief Based on the predicted sigma points the mean and covariance is predicted.
    void PredictMeanAndCovariance();

    /// @brief The state is updated using the predicted measurements
    void UpdateState(const int n_z, const VectorXd& z_pred, const MatrixXd& S, const MatrixXd& Zsig, const VectorXd& z);

    // Getter for internal states
    VectorXd& GetState() { return x_; }
    MatrixXd& GetCovariance() { return P_; }

    double GetStdDevAcceleration() { return std_a_; }
    double GetStdDevYawAcceleration() { return std_yawdd_; }

    double GetLambda() { return lambda_; }

    int GetStateSize() { return n_x_; }
    int GetAugmentedStateSize() { return n_aug_; }
    VectorXd GetWeights() { return weights_; }

    MatrixXd& GetPredictedSigmaPoints() { return Xsig_pred_; }

  private:
    /// Shall make debug outputs
    bool use_debug_outputs_;
    /// if this is false, laser measurements will be ignored (except for init)
    bool use_laser_;
    /// if this is false, radar measurements will be ignored (except for init)
    bool use_radar_;

    // Helper classes for sigma points and measurements
    SigmapointManager sigma_manager_;
    LaserManager laser_manager_;
    RadarManager radar_manager_;
    /// State dimension
    int n_x_;
    /// Augmented state dimension
    int n_aug_;
    /// Sigma point spreading parameter
    double lambda_;

    /// State vector: [pos1 pos2 vel_abs yaw_angle yaw_rate] in SI units and rad
    VectorXd x_;
    /// State covariance matrix
    MatrixXd P_;
    /// Predicted sigma points matrix
    MatrixXd Xsig_pred_;
    ///  Weights of sigma points
    VectorXd weights_;

    /// time when the state is true, in us
    long long time_us_;
    /// initially set to false, set to true in first call of ProcessMeasurement
    bool is_initialized_;

    /// Process noise standard deviation longitudinal acceleration in m/s^2
    double std_a_;
    /// Process noise standard deviation yaw acceleration in rad/s^2
    double std_yawdd_;

    // Helper for initialization
    void InitializeProcessNoise();
    void InitializeCovariance();
    void SetupWeights();
};
