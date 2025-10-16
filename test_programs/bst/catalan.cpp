#include <iostream>
#include <vector>

long long catalan(int n)
{
    std::vector<long long> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j < i; j++)
            dp[i] += dp[j] * dp[i - 1 - j];
    return dp[n];
}

int main()
{
    int n;
    std::cout << "Enter number of distinct keys: ";
    std::cin >> n;
    std::cout << "Number of distinct BSTs: " << catalan(n) << std::endl;
    return 0;
}