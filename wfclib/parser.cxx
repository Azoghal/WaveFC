#include "parser.hxx"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <set>

namespace wfc{

Parser::Parser()
{
    next_pattern_id_ = 1;
}

int Parser::InputCharToInt(std::string s){
    // Parse string arg to int
    std::istringstream char_str(s);
    int val;
    if (char_str >> val)
    {
        return val;
    }
    return -1;
}

int Parser::InputCharToInt(char c){
    std::string s;
    s.push_back(c);
    // Parse string arg to int
    return this->InputCharToInt(s);
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

void Parser::Parse(std::string input_file, int kernel_size){
    kernel_size_ = kernel_size;
    input_ = this->ReadInput(input_file);
    this->ParseLoop();
}

void Parser::ParseLoop(){
    // Find all kernels (for now ignoring symmetry and rotations)
    //std::unordered_map<int, int> states_observed;
    std::map<int,std::vector<std::map<int,int>>> constraints;
    std::map<int,wfc::Pattern> patterns;
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
            // Increase count of pattern appearence, find its unique id, add to pattern world
            int pattern_id = this->GeneratePatternID(kernel);
            patterns[pattern_id] = wfc::Pattern(pattern_id,kernel);
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
    patterns_ = patterns;
    constraints_ = wfc::Constraints(constraints);
}

std::pair<int,std::string> Parser::ReadToken(std::string s){
    std::string output;
    bool started = false;
    int consumed = 0;
    for (char c : s){
        if (c != ' '){
            output += c;
            started = true;
        }
        else if (started){
            break;
        }
        consumed++;
    }
    return std::pair<int,std::string>(consumed,output);
}

std::vector<std::string> Parser::TokeniseLine(std::string l){
    std::string line = l;
    std::vector<std::string> tokens;
    std::pair<int,std::string> token = this->ReadToken(line);
    while (token.first > 0){
        tokens.push_back(token.second);
        line = line.substr(token.first);
        token = this->ReadToken(line);
        
    } 
    return tokens;
}


void Parser::LoadParse(std::string input_file){
    input_ = std::vector<std::vector<int>>();
    //Temp
    // kernel [kernel size]
    // patterns [n number of patterns]
    // 
    // [pattern id]
    // [kernel size x colour id]
    // [... kernel size]
    // repeated n times
    //std::pair<int,std::string> token;
    std::map<int, std::vector<std::map<int,int>>> constraints;
    std::map<int, wfc::Pattern> patterns;

    std::vector<std::string> tokens;
    std::string line;
    std::ifstream infile(input_file);
    std::runtime_error format_error("Incorrectly formatted constraints file");

    int num_patterns;
    int num_constraints;

    //Todo allow constraints file to have different order as each part has titles
    std::getline(infile, line);
    tokens = this->TokeniseLine(line);
    if (tokens.size() != 2) throw format_error;
    if (tokens[0] != "kernel") throw format_error;
    int k = this->InputCharToInt(tokens[1]);
    if (k < 1) throw format_error;
    kernel_size_ = k;
    std::cout << "parsed kernel size " << kernel_size_ << std::endl;

    std::getline(infile, line);
    tokens = this->TokeniseLine(line);
    if (tokens.size() != 2 || tokens[0] != "patterns") throw format_error;
    num_patterns = this->InputCharToInt(tokens[1]);
    if (num_patterns < 1) throw format_error;
    std::cout << "parsed num patterns " << kernel_size_ << std::endl;

    for (int i = 0; i<num_patterns; ++i){
        // Find a pattern id and its relevant pixel values
        std::getline(infile, line);
        tokens = this->TokeniseLine(line);
        if (tokens.size() != 1) throw format_error;
        int pattern_id = this->InputCharToInt(tokens[0]);
        // TODO check that pattern id is not already  present.
        std::vector<std::vector<int>> int_pattern;
    
        for (int p_line=0; p_line < kernel_size_; ++p_line){
            std::vector<int> int_row;
            std::getline(infile,line);
            tokens = this->TokeniseLine(line);
            if (tokens.size() != kernel_size_) throw format_error;
            for (std::string token : tokens){
                int pixel_id = this->InputCharToInt(token);
                if (pixel_id < 0) throw format_error;
                int_row.push_back(pixel_id);
            }
            int_pattern.push_back(int_row);
        }
        patterns[pattern_id] = wfc::Pattern(pattern_id, int_pattern);
        // make vector of empty maps for constraints to be written to.
        constraints[pattern_id] = std::vector<std::map<int,int>>(4,std::map<int,int>());
    }

    for (auto& [id, pattern] : patterns){
        std::cout << "Pattern " << id << std::endl;
        std::vector<std::vector<int>> ints = pattern.GetPattern();
        for (auto& row: ints){
            for (auto& val: row){
                std::cout << val;
            }
            std::cout << std::endl;
        }
    }

    int left, right, top, bottom, count;

    std::getline(infile, line);
    tokens = this->TokeniseLine(line);
    if (tokens.size() != 2) throw format_error;
    if (tokens[0] != "horizontal") throw format_error;
    num_constraints = this->InputCharToInt(tokens[1]);
    if (k < 1) throw format_error;
    kernel_size_ = k;
    std::cout << "parsing " << num_constraints << " horizontal constraints" << std::endl;
    
    for (int i=0; i< num_constraints; ++i){
        std::getline(infile, line);
        tokens = this->TokeniseLine(line);
        if (tokens.size() != 3) throw format_error;
        left = this->InputCharToInt(tokens[0]);
        right = this->InputCharToInt(tokens[1]);
        count = this->InputCharToInt(tokens[2]);
        if (left < 0 || right < 0 || count < 0) throw format_error;
        // constraint indexing
        // pattern id, direction index, neighbour id -> count
        constraints[left][0][right] = count;
        constraints[right][2][left] = count;
        std::cout << left << " " << right << " x" << count << std::endl;
    }

    std::getline(infile, line);
    tokens = this->TokeniseLine(line);
    if (tokens.size() != 2) throw format_error;
    if (tokens[0] != "vertical") throw format_error;
    num_constraints = this->InputCharToInt(tokens[1]);
    if (k < 1) throw format_error;
    kernel_size_ = k;
    std::cout << "parsing " << num_constraints << " vertical constraints" << std::endl;
    
    for (int i=0; i< num_constraints; ++i){
        std::getline(infile, line);
        tokens = this->TokeniseLine(line);
        if (tokens.size() != 3) throw format_error;
        top = this->InputCharToInt(tokens[0]);
        bottom = this->InputCharToInt(tokens[1]);
        count = this->InputCharToInt(tokens[2]);
        if (top < 0 || bottom < 0 || count < 0) throw format_error;
        // constraint indexing
        // pattern id, direction index, neighbour id -> count
        constraints[top][1][bottom] = count;
        constraints[bottom][3][top] = count;
        std::cout << top << " " << bottom << " x" << count << std::endl;
        std::cout << bottom << " " << top << std::endl;

    }

    patterns_ = patterns;
    constraints_ = wfc::Constraints(constraints);
}

void Parser::SaveParse(std::string output_file){
    // Convert constraints to text and write them
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