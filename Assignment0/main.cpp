#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<iostream>

int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;
    // matrix add i + j
    std::cout << "Matrix add: "<<std::endl<<i+j<<std::endl;
    // matrix scalar multiply i * 2.0
    std::cout << "Matrix scalar multiply: "<<std::endl<<i*2.0f<<std::endl;
    // matrix multiply i * j
    std::cout << "Matrix multiplication: "<<std::endl<<i*j<<std::endl;
    // matrix multiply vector i * v
    std::cout << "Matrix multiply vector: "<<std::endl<<i*v<<std::endl;

    //define a family of vectors
    Eigen::Vector3f vertices[3];
    vertices[0] << 1,2,3;
    vertices[1] << 4,5,6;
    vertices[2] << 7,8,9;
    std::cout<<"the 1th vertex is: \n"<<vertices[1]<<std::endl;

    //index of Vectors
    std::cout<<"testing index of the vectors\n";
    Eigen::Matrix<float, 10, 1> array;
    array<<0,1,2,3,4,5,6,7,8,9;
    std::cout<<array(8,0)<<std::endl;
    std::cout<<array[8]<<std::endl;
    std::cout<<array(8)<<std::endl;
    //Eigen supports some short cuts for vector with length within [2,4]
    Eigen::Vector4f vec4d(0,1,2,3);  //supports initialization with constructor!
    //position 0,1,2,3 has short cuts: x(), y(), z(), w()
    std::cout<<vec4d.w()<<std::endl;
    std::cout<<"modify vector\n";
    vec4d.x() = 777;
    std::cout<<vec4d<<std::endl;

    //test using vectors to initialize matrix
    Eigen::Vector3f vt(1,2,3);
    Eigen::Vector3f vb(4,5,6);
    Eigen::Vector3f vn(7,8,9);
    Eigen::Matrix<float, 3,3> tbn;
    tbn<<vt,vb,vn;
    std::cout<<tbn<<std::endl;

    return 0;
}