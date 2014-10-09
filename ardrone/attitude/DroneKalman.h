#ifndef _DRONEKALMAN_H
#define _DRONEKALMAN_H

namespace BFL {
  class ExtendedKalmanFilter;
  class Gaussian;
  class LinearAnalyticConditionalGaussian;
  class LinearAnalyticMeasurementModelGaussianUncertainty;
  class LinearAnalyticSystemModelGaussianUncertainty;
}


class DroneKalman
{
  public:
  DroneKalman(float qAngle, float qAngleVel, float qDrift, float rAccelero, float rGyro);
  ~DroneKalman();
  
  void update(float acceleroAngle, float gyroVal);
  
  float angle();
  float angleVel();
  float drift();

 
  private:
  
  BFL::ExtendedKalmanFilter * m_filter;
  BFL::Gaussian *m_prior;
  
  BFL::LinearAnalyticConditionalGaussian *m_meas_pdf;
  BFL::LinearAnalyticMeasurementModelGaussianUncertainty *m_meas_model;
  BFL::LinearAnalyticConditionalGaussian *m_sys_pdf;
  BFL::LinearAnalyticSystemModelGaussianUncertainty *m_sys_model;
};


#endif 