#include "parser.hxx"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <set>

namespace wfc{

Parser::Parser(std::string input_file, int kernel_size)
{
    kernel_size_ = kernel_size;
    input_ = this->ReadInput(input_file);
    this->CheckKernelSize();
}

int Parser::InputCharToInt(char c){
    std::string s;
    s.push_back(c);
    // Parse string arg to int
    std::istringstream char_str(s);
    int val;
    if (char_str >> val)
    {
        return val;
    }
    return -1;
}

std::vector<std::vector<int>> Parser::ReadInput(std::string filename){

    std::string line;
    std::ifstream infile(filename);
    //std::vector<std::vector<char>> char_world;
    std::vector<std::vector<int>> int_world;
    int next_id = 0;
    std::map<char, int> char_map;

    // Read characters and make int mapping?

    while (std::getline(infile, line)) {
        std::vector<int> row;
        for (char& c: line) {
            row.push_back(this->InputCharToInt(c));
        }
        int_world.push_back(row);
    }

    return int_world;
}

void Parser::Parse(){
    std::pair<std::unordered_map<int,int>, std::map<wfc::Pattern, int>> parsed = this->ParseLoop();
    state_distribution_ = parsed.first;
    constraints_ =  wfc::Constraints(parsed.second);
}

std::pair<std::unordered_map<int,int>, std::map<wfc::Pattern, int>> Parser::ParseLoop(){
    // Find all kernels (for now ignoring symmetry and rotations)
    std::unordered_map<int, int> states_observed;
    std::map<wfc::Pattern, int> patterns;
    int in_height = input_.size();
    int in_width = input_[0].size();
    // TODO assuming looping boundaries
    // TODO faster loops?
    for (int y=0; y<in_height; ++y){
        for (int x=0; x<in_width; ++x){
            states_observed[input_[x][y]] += 1;
            std::vector<std::vector<int>> kernel(kernel_size_, std::vector<int>(kernel_size_));
            // kernel from current top left 
            for (int i=0; i<kernel_size_; ++i){
                for (int j=0; j<kernel_size_; ++j){
                    // Boundary looping logic
                    int xx = (x + i + in_width) % in_width;
                    int yy = (y + j + in_height) % in_height;
                    kernel[i][j] = input_[xx][yy];
                }
            }
            patterns[kernel]++;
        }
    }
    return std::pair<std::unordered_map<int,int>, std::map<wfc::Pattern, int>> (states_observed, patterns);
}

void Parser::CheckKernelSize(){
    // Kernel must be smaller or same size as input
    if (input_.size() < kernel_size_ || input_[0].size() < kernel_size_){
        throw std::invalid_argument("Input map smaller than kernel size");
    }
    // Input must be multiple of Kernel in all dimensions
    if (input_.size() % kernel_size_ || input_[0].size() % kernel_size_){
        throw std::invalid_argument("Input map not multiple of  kernel size in all dimensions");
    }
}

void Parser::SetKernelSize(int kernel_size){
    kernel_size_ = kernel_size;
    this->CheckKernelSize();
}

std::unordered_map<int,int> Parser::GetStateDistribution(){
    return state_distribution_;
}

wfc::Constraints Parser::GetConstraints(){
    return constraints_;
}

} // namespace wfc