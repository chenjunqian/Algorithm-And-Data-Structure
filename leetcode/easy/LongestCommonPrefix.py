# Write a function to find the longest common prefix string amongst an array of strings.
# If there is no common prefix, return an empty string "".
# Example 1:
# Input: ["flower","flow","flight"]
# Output: "fl"
class Solution:
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        result = ''
        if len(strs) <= 0:
            return result
        for i in range(len(strs[0])):
            for j in range(len(strs)):
                if i > len(strs[j])-1 or strs[j][i] != strs[0][i]:
                    return result
            result = result + strs[0][i]
        return result
