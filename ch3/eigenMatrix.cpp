#include <iostream>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char const *argv[])
{
	Eigen::Matrix<float, 2, 3> matrix_23;
	matrix_23 << 1,2,3,4,5,6;
	cout << matrix_23 << endl;

	for (int i = 0; i < 1; i++)
		for(int j = 0; j < 2; j++)
			cout << matrix_23(i,j) << endl;


	//Matrix<double,3,1>
	Eigen::Vector3d v_3d;
	v_3d << 3,2,1;
	Eigen::Matrix<double,2,1> result = matrix_23.cast<double>() * v_3d;
	cout << result << endl;
	//wrong eg
	// Eigen::Matrix<double,2,1> result_wrong_type = matrix_23 * v_3d;
	// Eigen::Matrix<double,2,3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;


    //Matrix<double,3,3>
	Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
	matrix_33 = Eigen::Matrix3d::Random();
	cout << matrix_33 << endl << endl;

    cout << matrix_33.sum() << endl;
    cout << matrix_33.trace() << endl;
    cout << 10 * matrix_33 << endl;
    cout << matrix_33.inverse() << endl;
    cout << matrix_33.determinant() << endl;
    cout << matrix_33.transpose() << endl;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);	
    cout << "Eigen values = " << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = " << eigen_solver.eigenvectors() << endl;


    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock();
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time use in normal inverse is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;

    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time use in Qr composition is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
    
    return 0;
}