#include "pattern.hxx"

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
    for (int i=0; i<size_; ++i){
        for (int j=0; j<size_; ++j){
            if (pattern_[i][j] < rhs.pattern_[i][j]){
                return true;
            }
        }
    }
    return false;
}

bool Pattern::CheckMatches(std::vector<std::vector<int>> to_compare_){
    // TODO not implemented
    return false;
}

} // namespace wfc

