#include <iostream>
#include <memory>

#include <eigen3/Eigen/Core>
#include <cblas.h>

#include "base/time/current_time.h"

using namespace std;
using namespace Eigen;

const int N = 1024;

void run_eigen()
{
    double t1 = base::current_time();

    MatrixXf m1(N, N), m2(N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            m1(i, j) = i + j;
            m2(i, j) = i + j;
        }
    }

    double t2 = base::current_time();

    MatrixXf m3 = m1 * m2;

    double t3 = base::current_time();

    cout << m3(0, 0) << ' ' << m3(128, 64) << endl;

    double t4 = base::current_time();

    cout << "prepare: " << (t2 - t1) << endl;
    cout << "multi  : " << (t3 - t2) << endl;
    cout << "print  : " << (t4 - t3) << endl;
}

void run_blas()
{
    double t1 = base::current_time();

    unique_ptr<float[]> m1(new float[N * N]);
    unique_ptr<float[]> m2(new float[N * N]);
    unique_ptr<float[]> m3(new float[N * N]);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            m1[i * N + j] = i + j;
            m2[i * N + j] = i + j;
        }
    }

    double t2 = base::current_time();

    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                N, N, N,
                1.0, m1.get(), N, m2.get(), N,
                0.0, m3.get(), N);

    double t3 = base::current_time();

    cout << m3[0] << ' ' << m3[128 * N + 64] << endl;

    double t4 = base::current_time();

    cout << "prepare: " << (t2 - t1) << endl;
    cout << "multi  : " << (t3 - t2) << endl;
    cout << "print  : " << (t4 - t3) << endl;
}

int main()
{
    cout << "Run Eigen:" << endl;
    run_eigen();

    cout << "Run BLAS:" << endl;
    run_blas();

    return 0;
}
