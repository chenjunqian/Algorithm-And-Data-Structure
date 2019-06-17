#Given nums = [0,0,1,1,1,2,2,3,3,4],
#Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.
#It doesn't matter what values are set beyond the returned length.
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
