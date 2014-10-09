// $Id: kalman_mobile.cpp 5925 2006-03-14 21:23:49Z tdelaet $
// Copyright (C) 2006 Tinne De Laet <first dot last at mech dot kuleuven dot be>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "DroneKalman.h"

#include <filter/extendedkalmanfilter.h>

#include <model/linearanalyticsystemmodel_gaussianuncertainty.h>
#include <model/linearanalyticmeasurementmodel_gaussianuncertainty.h>

#include <pdf/analyticconditionalgaussian.h>
#include <pdf/linearanalyticconditionalgaussian.h>

#include <iostream>
#include <fstream>

using namespace MatrixWrapper;
using namespace BFL;
using namespace std;


DroneKalman::DroneKalman(float qAngle, float qAngleVel, float qDrift, float rAccelero, float rGyro)
{
  /****************************
   * Linear system model      *
   ***************************/

  double dt=0.005;
  // Create the matrices A and B for the linear system model
  Matrix A(3,3);
  A(1,1) = 1.0;
  A(1,2) = dt;
  A(1,3) = 0.0;
  
  A(2,1) = 0.0;
  A(2,2) = 1.0;
  A(2,3) = 0.0;
  
  A(3,1) = 0.0;
  A(3,2) = 0.0;
  A(3,3) = 1.0;
  
  vector<Matrix> AB(1);
  AB[0] = A;

  // create gaussian
  ColumnVector sysNoise_Mu(3);
  sysNoise_Mu(1) = 0;
  sysNoise_Mu(2) = 0;

  SymmetricMatrix sysNoise_Cov(3);
  sysNoise_Cov = 0.0;
  sysNoise_Cov(1,1) = qAngle;
  sysNoise_Cov(1,2) = 0.0;
  sysNoise_Cov(1,3) = 0.0;
  
  sysNoise_Cov(2,1) = 0.0;
  sysNoise_Cov(2,2) = qAngleVel;
  sysNoise_Cov(2,3) = 0.0;
  
  sysNoise_Cov(3,1) = 0.0;
  sysNoise_Cov(3,2) = 0.0;
  sysNoise_Cov(3,3) = qDrift;


  BFL::Gaussian system_Uncertainty(sysNoise_Mu, sysNoise_Cov);

  // create the model
  m_sys_pdf=new LinearAnalyticConditionalGaussian(AB, system_Uncertainty);
  m_sys_model=new LinearAnalyticSystemModelGaussianUncertainty(m_sys_pdf);


  /*********************************
   * Initialise measurement model *
   ********************************/

  // create matrix H for linear measurement model
  Matrix H(2,3);
  H = 0.0;
  H(1,1) = 1;
  H(1,2) = 0;
  H(1,3) = 0;
  H(2,1) = 0;
  H(2,2) = 1;
  H(2,3) = 1;

  // Construct the measurement noise
  ColumnVector measNoise_Mu(2);
  measNoise_Mu(1) = 0;
  measNoise_Mu(2) = 0;

  SymmetricMatrix measNoise_Cov(2);
  measNoise_Cov=0.0;
  measNoise_Cov(1,1) = rAccelero;
  measNoise_Cov(2,2) = rGyro;
  Gaussian measurement_Uncertainty(measNoise_Mu, measNoise_Cov);

  // create the model
  m_meas_pdf=new LinearAnalyticConditionalGaussian(H, measurement_Uncertainty);
  m_meas_model=new LinearAnalyticMeasurementModelGaussianUncertainty(m_meas_pdf);


  /****************************
   * Linear prior DENSITY     *
   ***************************/
   // Continuous Gaussian prior (for Kalman filters)
  ColumnVector prior_Mu(3);
  prior_Mu(1) = 0;
  prior_Mu(2) = 0;
  prior_Mu(3) = 0;
  
  SymmetricMatrix prior_Cov(3);
  prior_Cov(1,1) = 100.0;
  prior_Cov(1,2) = 0.0;
  prior_Cov(1,3) = 0.0;
  prior_Cov(2,1) = 0.0;
  prior_Cov(2,2) = 10.0;
  prior_Cov(2,3) = 0.0;
  prior_Cov(3,1) = 0.0;
  prior_Cov(3,2) = 5.0;
  prior_Cov(3,3) = 0.0;


  m_prior=new Gaussian(prior_Mu,prior_Cov);


  /******************************
   * Construction of the Filter *
   ******************************/
  m_filter=new ExtendedKalmanFilter(m_prior);
}

DroneKalman::~DroneKalman()
{
  delete m_filter;
  delete m_prior;
  delete m_meas_pdf;
  delete m_meas_model;
  delete m_sys_pdf;
  delete m_sys_model;
}


void DroneKalman::update(float acceleroAngle, float gyroVal)
{

      ColumnVector measurement(2);
      measurement(1)=acceleroAngle;
      measurement(2)=gyroVal;
      ColumnVector input(0);
      
      m_filter->Update(m_sys_model,input, m_meas_model, measurement);
      Pdf<ColumnVector> * posterior = m_filter->PostGet();
      //cout << " Posterior Mean = " << endl << posterior->ExpectedValueGet() << endl;
} 

float DroneKalman::angle()
{
      Pdf<ColumnVector> * posterior = m_filter->PostGet();
      return posterior->ExpectedValueGet()(1);
}

float DroneKalman::angleVel()
{
      Pdf<ColumnVector> * posterior = m_filter->PostGet();
      return posterior->ExpectedValueGet()(2);
}

float DroneKalman::drift()
{
      Pdf<ColumnVector> * posterior = m_filter->PostGet();
      return posterior->ExpectedValueGet()(3);
}
