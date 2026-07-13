/*
Given a string s consisting only of digits, return all possible valid IP address combinations that can be formed from it. 
A valid IP address consists of four numbers (0–255) separated by dots.
Note: A segment cannot contain leading zeros unless the number itself is 0.
For example, 1.1.2.11 and 0.11.21.1 are valid IP addresses, while 01.1.2.11 and 00.11.21.1 are not valid because they contain leading zeros.

Examples:
Input: s = "255678166"
Output: [“25.56.78.166”, “255.6.78.166”, "255.67.8.166", "255.67.81.66"]
Explanation: These are the only valid possible IP addresses.

Input: s = "25505011535"
Output: []
Explanation: We cannot generate a valid IP address with this string.

Using Backtracking with Pruning
We generate all possible ways to place 3 dots in the string to form 4 segments.
During the process, we only continue if the current segment is valid (0–255 and no leading zeros). 
If a segment becomes invalid, we prune that branch to avoid unnecessary exploration.

Step by Step implementation

Start backtracking from the beginning of the string and try forming segments.
Choose segment lengths of 1, 2, or 3 digits, since a valid IP part cannot exceed 3 digits.
Validate the segment: it must be between 0 and 255 and must not contain leading zeros.
If the segment is valid, place a dot and recursively process the remaining string.
Prune the recursion if a segment becomes invalid.
Stop when 3 dots are placed and check whether the final segment is valid.
If all 4 segments are valid, store the formed IP address.
*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Check if a segment is a valid IP part
bool isValid(const string &s)
{
    if (s.size() > 1 && s[0] == '0')
    {

        // leading zero not allowed
        return false;
    }

    int val = stoi(s);
    return val <= 255;
}

// Recursive function to generate IP addresses
void generateIpRec(const string &s, int index, string curr, int cnt, vector<string> &res)
{

    if (index >= s.size())
        return;

    // If 3 dots are placed, validate the last segment
    if (cnt == 3)
    {
        string last = s.substr(index);
        if (last.size() <= 3 && isValid(last))
            res.push_back(curr + last);
        return;
    }

    string segment = "";

    // Try segment lengths 1 to 3
    for (int i = index; i < min(index + 3, (int)s.size()); i++)
    {
        segment += s[i];

        if (isValid(segment))
        {
            generateIpRec(s, i + 1, curr + segment + ".", cnt + 1, res);
        }
    }
}

// Generate all valid IP addresses
vector<string> generateIp(string s)
{
    vector<string> res;
    generateIpRec(s, 0, "", 0, res);
    return res;
}

int main()
{
    string s = "255678166";
    vector<string> res = generateIp(s);

    for (string ip : res)
        cout << ip << endl;
}