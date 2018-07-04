class Solution:
    def removeElement(self, nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """
        i = 0
        j = 0
        while j < len(nums):
            if nums[j] == val:
                j+=1
            else:
                nums[i] = nums[j]
                i+=1
                j+=1
        return i
