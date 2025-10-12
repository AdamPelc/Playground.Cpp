#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> getAverages(std::vector<int>& nums, int k) {
        std::vector<int> result(nums.size(), -1);

        if(nums.size() < 2 * k + 1)
        {
            return result;
        }

        std::vector<int> runningTotal = [&nums]{
            std::vector<int> result;
            result.reserve(nums.size());
            auto currentValue = 0;
            for(const auto value : nums)
            {
                currentValue += value;
                result.push_back(currentValue);
            }

            return result;
        }();

        const auto rightLimit = nums.size() - k;
        for(auto idx = k; idx != rightLimit; ++idx)
        {
            auto sum = runningTotal.at(k + idx);
            if (idx != k) {
                sum -= runningTotal.at(idx - k - 1);
            }
            result[idx] = sum / (2 * k + 1);
        }

        return result;
    }
};

int main()
{
    std::cout << "LeetCode: 2090\n";

    auto solution = Solution();
    std::vector input = {8};
    auto result = solution.getAverages(input, 100000);
    std::cout << "{ ";
    for(const auto value : result) {
        std::cout << value << ", ";
    }
    std::cout << "}\n";
    return 0;
}
