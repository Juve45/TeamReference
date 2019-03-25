/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 *
 * $dp[i] = min j<i {dp[j] + b[j] * a[i]} when b[j] >= b[j+1], a[i] <= a[i+1]: O(n^2) -> O(n)$ \\
 * $dp[i][j] = min k<j {dp[i-1][k] + b[k] * a[j]} when b[k] >= b[k+1], a[j] <= a[j+1]: O(kn^2) -> O(kn)$ \\
 * $dp[i][j] = min k<j {dp[i-1][k] + C[k][j]}, optim[i][j] <= optim[i][j+1]: O(kn^2) -> O(kn logn)$ \\
 * Time: O(N^2)
 */