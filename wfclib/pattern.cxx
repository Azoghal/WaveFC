#include "pattern.hxx"
#include <iostream>

namespace wfc{

Pattern::Pattern(){
    // Non collapsed pattern
    size_ = -1;
    pattern_ = std::vector<std::vector<int>>();
}

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

std::vector<Pattern> Pattern::GenerateRotations(){
    std::vector<Pattern> a = {*this};
    return a;
    // TODO
}

std::vector<Pattern> Pattern::GenerateReflections(){
    std::vector<Pattern> a = {*this};
    return a;
    // TODO
}

std::vector<std::vector<int>> Pattern::GetPattern(){
    return pattern_;
}

const bool Pattern::operator<(const Pattern& rhs) const{
    // Comparison allows for this to be used as a std::map key
    if (size_ != rhs.size_){
        // TODO raise exception
        return false;
    }
    return pattern_ < rhs.pattern_;

    // return id_ < rhs.id_;
}

} // namespace wfc

