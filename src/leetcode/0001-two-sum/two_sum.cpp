#include <iterator>
#include <unordered_map>
#include <vector>

class Solution final {
public:
    std::vector<int> twoSum(std::vector<int> const & nums, int target) {
        std::unordered_map<int, int> num_idx;

        auto it = nums.begin();
        auto const end = nums.end();
        for (; it != end; ++it) {
            int const idx = std::distance(nums.begin(), it);
            if (auto const val = num_idx.find(target - *it); val != num_idx.end()) {
                return {val->second, idx};
            } else {
                num_idx.emplace(*it, idx);
            }
        }

        return {-1, -1};
    }
};

////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

using T = std::tuple<std::vector<int>, int, std::vector<int>>;
using TestSuite = ::testing::TestWithParam<T>;

TEST_P(TestSuite, Example) {
    auto [nums, target, expect] = GetParam();
    auto const result = Solution().twoSum(nums, target);
    EXPECT_EQ(expect, result);
}

// clang-format off

INSTANTIATE_TEST_SUITE_P(TestValues, TestSuite, ::testing::ValuesIn({
    T{
        {2, 7, 11, 15},
        9,
        {0, 1},
    },
    T{
        {3, 2, 4},
        6,
        {1, 2}
    },
    T{
        {3, 3},
        6,
        {0, 1}
    },
}));

INSTANTIATE_TEST_SUITE_P(TestIncorrectValues, TestSuite, ::testing::ValuesIn({
    T{
        {-1, -1},
        0,
        {-1, -1},
    },
}));

// clang-format on

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
