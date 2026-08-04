/*
973. K Closest Points to Origin

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

Example 1:
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].


Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 

Constraints:
1 <= k <= points.length <= 10^4
-10^4 <= xi, yi <= 10^4


Time complexity: 0(nlogk)
Space : O(k);
*/


    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, vector<int>>> pq;

        for(auto point: points){
            int dist = point[0] * point[0] + point[1] * point[1];
            pq.push({dist, point});

            if(pq.size()>k)
                pq.pop();
        }

        vector<vector<int>> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }


/*
    using quick sort
Time Complexity:

Average: O(n)
Worst: O(n²)
Space Complexity: O(1) (ignoring recursion stack)

*/

    class Solution {
public:
    int dist(vector<int>& p) {
        return p[0] * p[0] + p[1] * p[1];
    }

    int partition(vector<vector<int>>& points, int l, int r) {
        int pivot = dist(points[r]);
        int i = l;

        for (int j = l; j < r; j++) {
            if (dist(points[j]) <= pivot) {
                swap(points[i], points[j]);
                i++;
            }
        }

        swap(points[i], points[r]);
        return i;
    }

    void quickSelect(vector<vector<int>>& points, int l, int r, int k) {
        if (l >= r) return;

        int p = partition(points, l, r);

        if (p == k)
            return;
        else if (p < k)
            quickSelect(points, p + 1, r, k);
        else
            quickSelect(points, l, p - 1, k);
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        quickSelect(points, 0, points.size() - 1, k);
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};
