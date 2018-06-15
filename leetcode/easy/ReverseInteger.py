class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        index = 1 if x >= 0 else -1
        result = 0
        x = abs(x)
        while x:
            result = 10 * result + x % 10
            x =x//10
        result = index * result
        return result if result < pow(2,31)-1 and result >= pow(2,-31)*-1 else 0

