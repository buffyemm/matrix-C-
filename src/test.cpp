#include <iostream>

class Car {
    public:
        int door;
        int wheels;
        std::string model;
    
    void print(){

        std::cout << model << "\t" << door << "\t" << wheels << std::endl;
    }
    Car(std::string model, int door, int wheels){

        this->door = door;
        this->wheels = wheels;
        this->model = model;
        std::cout << "Car has been created" << std::endl;
    }

    Car(std::string model) : door(1), wheels(1)
    {
        std:: cout << "PISOS" << std::endl;
        this->model = model;
    } 

};

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

    public:
        S21Matrix(int rows, int cols) : rows_(rows), cols_(cols), matrix_(nullptr){}
        S21Matrix() : rows_(3), cols_(3), matrix_(nullptr){}
       ~S21Matrix(){
         for (unsigned i{}; i < rows_; i++)
        {
            delete[] matrix_[i];
        }
            delete[] matrix_;
            }

        void create_matrix(){
            matrix_ = new double*[rows_];
            for (int i = 0; i < rows_; i++) {
                matrix_[i] = new double[cols_];
            }

            for(int i = 0; i < rows_; i++) {
                for (int j = 0; j < cols_; j++) {
                    matrix_[i][j] = 1;
                }
            }
        }

        bool EqMatrix(const S21Matrix& other){
            if ( rows_ != other.rows_ || cols_ != other.cols_){
                return false;
            } 
                else{
                    for(int i = 0; i < rows_; i++){
                        for (int j = 0; j < cols_; j++){
                            if(matrix_[i][j] != other.matrix_[i][j]){
                                return false;
                            }
                        }
                    }
                }
        return true;
        }

        void SumMatrix(const S21Matrix& other) {
             if (matrix_ == nullptr || other.matrix_ == nullptr) {
            std::cerr << "Matrix not initialized!" << std::endl;
            return;
        }

            for (int i = 0; i < rows_; i++) {
                for (int j = 0; j < cols_; j++) {
                    matrix_[i][j] += other.matrix_[i][j];
                }
             }
        }
    
        void SubMatrix(const S21Matrix& other) {
            for (int i = 0; i < rows_; i++) {
                for (int j = 0; j < cols_; j++) {
                    matrix_[i][j] -= other.matrix_[i][j];
                }
            }
        }

        void printfMatrix() {
            for(int i = 0; i < rows_; i++) {
                for (int j = 0; j < cols_; j++) {
                    std::cout<<matrix_[i][j]<<" ";
                }
            std::cout << std::endl;
            }
        }

};




int main () {
S21Matrix arr;
S21Matrix bar;
arr.create_matrix();
bar.create_matrix();
//arr.SubMatrix(bar);
int kan = arr.EqMatrix(bar);
std:: cout << kan << std::endl;
arr.printfMatrix();
    return 0;
}




