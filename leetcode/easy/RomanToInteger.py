
class Solution:
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        numerals = { "M": 1000, "D": 500, "C": 100, "L": 50, "X": 10, "V": 5, "I": 1 }
        sum = 0
        for i in range(len(s)-1):
            if numerals[s[i]] < numerals[s[i+1]]:
                sum = sum - numerals[s[i]]
            else:
                sum = sum + numerals[s[i]]
        return sum + numerals[s[-1]]
            
                

if __name__ == '__main__':
    s = Solution()
    print(s.romanToInt('MCMXCIV'))
