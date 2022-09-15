#include "pattern.hxx"
#include <iostream>

namespace wfc{


Pattern::Pattern(int size)
{
    size_ = size;
    pattern_ = std::vector<std::vector<int>>(size_, std::vector<int>(size_, 0));
}

Pattern::Pattern(std::vector<std::vector<int>> pattern)
{
    pattern_ = pattern;
    size_ = pattern_.size();
    // TODO Raise exception if not square
}

Pattern::~Pattern()
{

}

std::vector<Pattern> Pattern::GenerateRotations(){
    std::vector<Pattern> a = {*this};
    return a;
}

std::vector<Pattern> Pattern::GenerateReflections(){
    std::vector<Pattern> a = {*this};
    return a;
}

const bool Pattern::operator<(const Pattern& rhs) const{
    if (size_ != rhs.size_){
        // TODO raise exception
        return false;
    }
    return pattern_ < rhs.pattern_;
}

bool Pattern::CheckMatches(std::vector<std::vector<int>> to_compare_) const{
    // to_compare has -1 for tiles not to be compared,
    // otherwise >= 0 for collapsed neighbours
    // First check sizes match
    if (to_compare_.size() != size_ || to_compare_[0].size() != size_){
        return false;
    }
    std::cout << "within check match" << std::endl;

    // DEBUG PRINTING
    std::cout << "this pattern: " << size_ << std::endl;
    for (auto row : pattern_){
        for (auto val : row){
            std::cout << val;
        }
        std::cout << std::endl;
    }

    // DEBUG PRINTING
    std::cout << "to compare: " << size_ << std::endl;
    for (auto row : to_compare_){
        for (auto val : row){
            std::cout << val;
        }
        std::cout << std::endl;
    }

    // then loop through and compare
    // all non -1 elements should be equal
    for (int y=0; y < size_; ++y){
        for (int x=0; x<size_; ++x){
            int val = to_compare_[x][y];
            if (val >= 0 && val != pattern_[x][y]){
                std::cout << "Pattern mismatch" << x << " " << y << " " << to_compare_[x][y] << " " << pattern_[x][y] << std::endl;;
                return false;
            }
        }
    }
    return true;
}

int Pattern::GetCentre() const{
    int c = size_/2;
    return pattern_[c][c];
}

} // namespace wfc

