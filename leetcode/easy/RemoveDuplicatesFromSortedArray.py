class Solution:
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        index = 0
        len_n = len(nums)
        if len_n ==0:
            return 0

        for i in range(len_n):
            if nums[index] != nums[i]:
                nums[index+1] = nums[i]
                index += 1
        return index+1
