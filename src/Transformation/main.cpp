#include <Eigen/Eigen>
#include <iostream>

template<typename M, typename V>
M translate(const M &a, const V b){
    int k = a.rows();
    assert(k == a.cols());
    assert(k - 1 == b.rows());
    
    M c = a;
    for(int i = 0; i < k - 1; i++)
        c(i, k - 1) += b(i);
        
    return c;
}

int main(){
    Eigen::Matrix4f trans = Eigen::Matrix4f::Identity();
    Eigen::Vector4f vec(1.0f, 0.0f, 0.0f, 1.0f);
    trans = translate(trans, Eigen::Vector3f(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec << std::endl;
}