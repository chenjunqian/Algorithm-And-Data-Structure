# Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
# Note: For the purpose of this problem, we define empty string as valid palindrome.
# Example 
# Input: "A man, a plan, a canal: Panama"
# Output: true
class Solution:
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if x < 0:
            return False
        
        temp = x
        result = 0
        while temp:
            result = result*10 + temp%10
            temp = temp//10
            print('result : '+str(result))
            print('temp : '+str(temp))
        return x == result