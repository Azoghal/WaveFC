#include "parser.hxx"

#include <iostream>
#include <cmath>


namespace wfc{

Parser::Parser(std::vector<std::vector<int>> input, int kernel_size){
    input_ = input;
    kernel_size_ = kernel_size;
    this->CheckKernelSize();
}

Parser::~Parser(){

}

wfc::Constraints Parser::Parse(){
    std::map<wfc::Pattern, int> patterns = this->GetKernelPatterns();
    return wfc::Constraints();
}

std::map<wfc::Pattern, int> Parser::GetKernelPatterns(){
    // Find all kernels (for now ignoring symmetry and rotations)
    std::map<wfc::Pattern, int> patterns;
    int in_height = input_.size();
    int in_width = input_[0].size();
    // TODO assuming looping boundaries
    for (int y=0; y<in_height; ++y){
        for (int x=0; x<in_width; ++x){
            std::vector<std::vector<int>> kernel(kernel_size_, std::vector<int>(kernel_size_));
            for (int i=0; i<kernel_size_; ++i){
                for (int j=0; j<kernel_size_; ++j){
                    int xx = (x + i + in_width) % in_width;
                    int yy = (y + j + in_height) % in_height;
                    kernel[i][j] = input_[xx][yy];
                }
            }
            patterns[kernel]++;
        }
    }
    return patterns;
}

void Parser::CheckKernelSize(){
    if (input_.size() < kernel_size_ || input_[0].size() < kernel_size_){
        std::cout << "Input map smaller than kernel size" << std::endl;
        // TODO Refactor with exceptions
    }
}

void Parser::SetKernelSize(int kernel_size){
    kernel_size_ = kernel_size;
    this->CheckKernelSize();
}

} // namespace wfc