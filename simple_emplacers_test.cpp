#include <iostream>  // std::cout
#include <algorithm> // std::transform
#include <vector>    // std::vector
#include <set>       // std::set
#include <list>      // std::list

#include "emplacers.hpp" // back_emplacer, front_emplacer, emplacer

class Integer
{
public:
    explicit Integer(const int& num);
    ~Integer() = default;

    Integer(const Integer&) = default;  
    Integer(Integer&&) noexcept = default; 
    Integer& operator=(const Integer&) = default;
    Integer& operator=(Integer&&) noexcept = default;

    bool operator<(const Integer& integer) const;
    friend std::ostream& operator<<(std::ostream& os, const Integer& integer);

private:
    int m_num;
};

Integer::Integer(const int& num)
: m_num(num)
{}

bool Integer::operator<(const Integer& other) const
{
    return m_num < other.m_num;
}

std::ostream& operator<<(std::ostream& os, const Integer& integer)
{
    os << integer.m_num;

    return os;
}

int main()
{
    std::set<int> set{0, 1, 2, 3, 4, 5};

    std::vector<Integer> vec;
    std::transform(set.begin(), set.end(),
                   ilrd::back_emplacer(vec),
                   [](const auto& integer){ return integer; });
    for (const auto& integer : vec)
    {
        std::cout << integer << ' ';
    }
    std::cout << std::endl;

    std::list<Integer> list;
    std::transform(set.begin(), set.end(),
                   ilrd::front_emplacer(list),
                   [](const auto& integer){ return integer; });
    for (const auto& integer : list)
    {
        std::cout << integer << ' ';
    }
    std::cout << std::endl;

    std::set<int> shuffleSet{2, 5, 1, 0, 3, 4};

    std::set<Integer> otherSet;
    std::transform(shuffleSet.begin(), shuffleSet.end(),
                   ilrd::emplacer(otherSet, otherSet.begin()),
                   [](const auto& interger){ return interger; });
    for (const auto& integer : otherSet)
    {
        std::cout << integer << ' ';
    }
    std::cout << std::endl;

    return 0;
}