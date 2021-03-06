#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Eigen/Dense"

#include "main_utils.h"
#include "tools.h"

#include "ground_truth_package.h"
#include "measurement_package.h"
#include "udacity.h"
#include "unscented_kalman_filter.h"

using namespace std;
using std::vector;

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main(int argc, char* argv[])
{
    CheckArguments(argc, argv);

    string in_file_name_ = argv[1];
    ifstream in_file_(in_file_name_.c_str(), ifstream::in);

    string out_file_name_ = argv[2];
    ofstream out_file_(out_file_name_.c_str(), ofstream::out);

    CheckFiles(in_file_, in_file_name_, out_file_, out_file_name_);

    vector<MeasurementPackage> measurement_pack_list;
    vector<GroundTruthPackage> gt_pack_list;

    string line;

    // prep the measurement packages (each line represents a measurement at a
    // timestamp)
    int kMax = std::numeric_limits<int>::max();
    auto counter = 0;

    while (getline(in_file_, line))
    {
        counter++;
        if (counter >= kMax)
            break;

        string sensor_type;
        MeasurementPackage meas_package;
        GroundTruthPackage gt_package;
        istringstream iss(line);

        // reads first element from the current line
        iss >> sensor_type;
        if (sensor_type.compare("L") == 0)
        {
            ReadLaserMeasurement(meas_package, iss, measurement_pack_list);
        }
        else if (sensor_type.compare("R") == 0)
        {
            ReadRadarMeasurement(meas_package, iss, measurement_pack_list);
        }

        ReadGroundTruth(iss, gt_package, gt_pack_list);
    }

    // Create a UnscentedKalmanFilter instance
    UnscentedKalmanFilter ukf;

    // Used to compute the RMSE later
    vector<VectorXd> estimations;
    vector<VectorXd> ground_truth;

    // Call the UnscentedKalmanFilter-based fusion
    size_t N = measurement_pack_list.size();
    for (size_t k = 0; k < N; ++k)
    {
        std::cout << "Cycle: " << k + 1 << std::endl;
        // Start filtering from the second frame (the speed is unknown in the first frame)
        ukf.ProcessMeasurement(measurement_pack_list[k]);

        // Write estimations to output file
        OutputEstimations(out_file_, ukf, measurement_pack_list, k, gt_pack_list);

        // Store ground truth and current Kalman state
        estimations.push_back(ukf.GetState());
        ground_truth.push_back(gt_pack_list[k].gt_values_);
    }

    // Compute the accuracy (RMSE)
    auto rmse = Tools::CalculateRMSE(estimations, ground_truth);
    std::cout << "Accuracy - RMSE: \n" << rmse << std::endl;

    // Close files
    if (out_file_.is_open())
    {
        out_file_.close();
    }

    if (in_file_.is_open())
    {
        in_file_.close();
    }

    return 0;
}

/// @brief FOr testing the udacity provided quizzes
void CallQuizMethods()
{
    MatrixXd Xsig = MatrixXd(11, 5);
    MatrixXd Xsig_aug = MatrixXd(15, 7);
    MatrixXd Xsig_pred = MatrixXd(15, 5);
    VectorXd x_pred = VectorXd(5);
    MatrixXd P_pred = MatrixXd(5, 5);
    VectorXd z_out = VectorXd(3);
    MatrixXd S_out = MatrixXd(3, 3);
    VectorXd x_out = VectorXd(5);
    MatrixXd P_out = MatrixXd(5, 5);

    udacity::GenerateSigmaPoints(&Xsig);
    udacity::AugmentedSigmaPoints(&Xsig_aug);
    udacity::SigmaPointPrediction(&Xsig_pred);
    udacity::PredictMeanAndCovariance(&x_pred, &P_pred);
    udacity::PredictRadarMeasurement(&z_out, &S_out);
    udacity::UpdateState(&x_out, &P_out);
}
