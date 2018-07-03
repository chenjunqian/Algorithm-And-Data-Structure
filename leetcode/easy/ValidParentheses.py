class Solution:
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        result = [None]
        parantDict = {")":"(","]":"[","}":"{"}
        for item in s:
            if item in parantDict:
                if parantDict[item] != result.pop():
                    return False
            else:
                result.append(item)
        return len(result) == 1
                
