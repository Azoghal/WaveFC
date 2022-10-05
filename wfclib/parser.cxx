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
    next_pattern_id_ = 1;
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

    std::cout << "finished reading world" << std::endl;
    return int_world;
}

int Parser::GeneratePatternID(std::vector<std::vector<int>> pattern){
    std::map<std::vector<std::vector<int>>, int>::iterator it = pattern_ids_.find(pattern);
    if(it != pattern_ids_.end())
    {
        //element found;
        return it->second;
    }
    else{
        pattern_ids_[pattern] = next_pattern_id_;
        return next_pattern_id_++;
    }
}

void Parser::Parse(){
    this->ParseLoop();
}

void Parser::ParseLoop(){
    // Find all kernels (for now ignoring symmetry and rotations)
    //std::unordered_map<int, int> states_observed;
    std::map<int,std::vector<std::map<int,int>>> constraints;
    std::vector<std::vector<int>> pattern_id_world;
    int in_height = input_.size();
    int in_width = input_[0].size();
    // TODO assuming looping boundaries
    // TODO faster loops?
    for (int y=0; y<in_height; y += kernel_size_){
        std::vector<int> pattern_id_row;
        for (int x=0; x<in_width; x += kernel_size_){
            std::vector<std::vector<int>> kernel(kernel_size_, std::vector<int>(kernel_size_));
            // kernel from current top left 
            for (int j=0; j<kernel_size_; ++j){
                for (int i=0; i<kernel_size_; ++i){
                    // Boundary looping
                    int xx = (x + i + in_width) % in_width;
                    int yy = (y + j + in_height) % in_height;
                    kernel[j][i] = input_[yy][xx];
                }
            }
            std::cout << "finisehd with xx yy usage" << std::endl;
            // Increase count of pattern appearence, find its unique id, add to pattern world
            int pattern_id = this->GeneratePatternID(kernel);
            patterns_[pattern_id] = wfc::Pattern(pattern_id,kernel);
            pattern_id_row.push_back(pattern_id);
        }
        pattern_id_world.push_back(pattern_id_row);
    }

    int pattern_world_height = pattern_id_world.size();
    int pattern_world_width = pattern_id_world[0].size();

    for (int p_id=1; p_id < next_pattern_id_; ++p_id){
        constraints[p_id] = std::vector<std::map<int,int>> (4,std::map<int,int>());
    }


    for (int y=0; y<pattern_world_height; ++y){
         for (int x=0; x<pattern_world_width; ++x){
            int centre_id = pattern_id_world[y][x];
            int left = (x - 1 + pattern_world_width) % pattern_world_width;
            int right = (x + 1 + pattern_world_width) % pattern_world_width;
            int top = (y - 1 + pattern_world_height) % pattern_world_height;
            int bottom = (y + 1 + pattern_world_height) % pattern_world_height;
            constraints[centre_id][0][pattern_id_world[y][right]] += 1;
            constraints[centre_id][1][pattern_id_world[top][x]] += 1;
            constraints[centre_id][2][pattern_id_world[y][left]] += 1;
            constraints[centre_id][3][pattern_id_world[bottom][x]] += 1;
        }
    }

    // DIAGONAL NEIGHBOURS.
    // for (int y=0; y<pattern_world_height; ++y){
    //     for (int x=0; x<pattern_world_width; ++x){
    //         for (int i=-1; i<2; ++i){
    //             for (int j=-1; j<2; ++j){
    //                 if (i || j){
    //                 // Boundary looping
    //                     int xx = (x + i + pattern_world_width) % pattern_world_width;
    //                     int yy = (y + j + pattern_world_height) % pattern_world_height;
    //                     if (! (y || x)){
    //                         std::cout << xx << "," << yy << std::endl;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // check map
    // std::vector<std::string> directions = {"Right", "Top", "Left", "Bottom"};
    // for (auto& [p_id, vec] : constraints){
    //     int direction = 0;
    //     for (auto& m : vec){
    //         for (auto& [n_id, n_count] : m){
    //             std::cout << p_id << " has " << n_count << "x" << n_id << "to the " << directions[direction] << std::endl;
    //         }
    //         direction++;
    //     }
    // }

    constraints_ = constraints;
}

void Parser::CheckKernelSize(){
    // Kernel must be smaller or same size as input
    if (input_.size() < kernel_size_ || input_[0].size() < kernel_size_){
        std::cout << input_.size() << "x" <<input_[0].size() << std::endl;
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

wfc::Constraints Parser::GetConstraints(){
    return constraints_;
}

std::map<int, wfc::Pattern> Parser::GetPatterns(){
    return patterns_;
}


} // namespace wfc