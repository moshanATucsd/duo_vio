//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Att_pred.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 04-Aug-2015 14:03:28
//

// Include Files
#include "rt_nonfinite.h"
#include "SLAM.h"
#include "Att_pred.h"
#include "quatPlusThetaJ.h"
#include <stdio.h>

// Function Definitions

//
// ATT_PRED Prediction step of the attitude estimator
//    INPUT ARGUMENTS:
//    - x:  The current estimated attitude (JPL quaternion)
//    - P:  The state covariance matrix (3 x 3)
//    - w:  The current Gyro measurement (3 x 1)
//    - q:  The proecss noise
//    - dt: The time step
// Arguments    : double x[4]
//                double b_P[9]
//                const double w[3]
//                double q
//                double dt
// Return Type  : void
//
void Att_pred(double x[4], double b_P[9], const double w[3], double q, double dt)
{
  signed char I[9];
  int i14;
  double Phi[9];
  double b_Phi[9];
  int k;
  double c;
  double a[9];
  double c_Phi[9];
  double b_a[9];
  int i15;
  static const signed char c_a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const signed char d_a[9] = { -1, 0, 0, 0, -1, 0, 0, 0, -1 };

  double b_w[3];
  double dq[4];
  double b_x[16];
  double b_dq[4];
  for (i14 = 0; i14 < 9; i14++) {
    I[i14] = 0;
  }

  Phi[0] = 0.0;
  Phi[3] = -w[2];
  Phi[6] = w[1];
  Phi[1] = w[2];
  Phi[4] = 0.0;
  Phi[7] = -w[0];
  Phi[2] = -w[1];
  Phi[5] = w[0];
  Phi[8] = 0.0;
  for (k = 0; k < 3; k++) {
    I[k + 3 * k] = 1;
    for (i14 = 0; i14 < 3; i14++) {
      b_Phi[i14 + 3 * k] = (double)I[i14 + 3 * k] + -Phi[i14 + 3 * k] * dt;
    }
  }

  c = dt * dt;
  for (i14 = 0; i14 < 3; i14++) {
    for (k = 0; k < 3; k++) {
      Phi[i14 + 3 * k] = 0.0;
      for (i15 = 0; i15 < 3; i15++) {
        Phi[i14 + 3 * k] += b_Phi[i14 + 3 * i15] * b_P[i15 + 3 * k];
      }

      a[i14 + 3 * k] = 0.0;
      for (i15 = 0; i15 < 3; i15++) {
        a[i14 + 3 * k] += (double)d_a[i14 + 3 * i15] * ((double)c_a[i15 + 3 * k]
          * q * c);
      }
    }

    for (k = 0; k < 3; k++) {
      c_Phi[i14 + 3 * k] = 0.0;
      for (i15 = 0; i15 < 3; i15++) {
        c_Phi[i14 + 3 * k] += Phi[i14 + 3 * i15] * b_Phi[k + 3 * i15];
      }

      b_a[i14 + 3 * k] = 0.0;
      for (i15 = 0; i15 < 3; i15++) {
        b_a[i14 + 3 * k] += a[i14 + 3 * i15] * (double)d_a[i15 + 3 * k];
      }
    }
  }

  for (i14 = 0; i14 < 3; i14++) {
    for (k = 0; k < 3; k++) {
      b_P[k + 3 * i14] = c_Phi[k + 3 * i14] + b_a[k + 3 * i14];
    }

    b_w[i14] = w[i14] * dt;
  }

  quatPlusThetaJ(b_w, dq);
  b_x[0] = x[3];
  b_x[4] = -x[2];
  b_x[8] = x[1];
  b_x[12] = x[0];
  b_x[1] = x[2];
  b_x[5] = x[3];
  b_x[9] = -x[0];
  b_x[13] = x[1];
  b_x[2] = -x[1];
  b_x[6] = x[0];
  b_x[10] = x[3];
  b_x[14] = x[2];
  b_x[3] = -x[0];
  b_x[7] = -x[1];
  b_x[11] = -x[2];
  b_x[15] = x[3];
  b_dq[0] = dq[0];
  b_dq[1] = dq[1];
  b_dq[2] = dq[2];
  b_dq[3] = dq[3];
  for (i14 = 0; i14 < 4; i14++) {
    x[i14] = 0.0;
    for (k = 0; k < 4; k++) {
      x[i14] += b_x[i14 + (k << 2)] * b_dq[k];
    }
  }
}

//
// File trailer for Att_pred.cpp
//
// [EOF]
//