/*
You are given an array arr[] where no two adjacent elements are same, 
find the index of a peak element. An element is considered to be a peak if it is greater than its adjacent elements 
(if they exist).

If there are multiple peak elements, Return index of any one of them. The output will be "true" 
if the index returned by your function is correct; otherwise, it will be "false".

Note: Consider the element before the first element and the element after the last element to be negative infinity.

Examples :

Input: arr = [1, 2, 4, 5, 7, 8, 3]
Output: true
Explanation: arr[5] = 8 is a peak element because arr[4] < arr[5] > arr[6].
Input: arr = [10, 20, 15, 2, 23, 90, 80]
Output: true
Explanation: Element 20 at index 1 is a peak since 10 < 20 > 15. Index 5 (value 90) is also a peak,
 but returning any one peak index is valid.
Constraints:
1 ≤ arr.size() ≤ 106
-231 ≤ arr[i] ≤ 231 - 1



If an element is smaller than it's next element then it is guaranteed that at least one peak element will exist on the right side of this element.

Conversely if an element is smaller than it's previous element then it is guaranteed that at least one peak element will exist on the left side of this element.
*/



class Solution {
  public:
    int peakElement(vector<int> &arr) {
        // code here
        int n= arr.size();
         if(n==1) return 0;
        int low= 0, high= n-1;
        while(low<=high){
            int mid= (low+high)/2;
            
            if(mid==0) return (arr[0]>arr[1])?0:1;
            if(mid==n-1) return (arr[n-1]>arr[n-2])?n-1:n-2;
            if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1]) return mid;
            
            
            if(arr[mid]>arr[mid-1]) low=mid+1;
            else high= mid-1;
        }
        return low;
    }
};