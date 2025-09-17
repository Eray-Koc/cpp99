
#pragma once
#include <vector>
#include <deque>
#include <iostream>

class PMergeME
{
    public:
        template <typename T>
        static void printContainer(const T& container)
        {
            typename T::const_iterator it = container.begin();
            while (it != container.end())
            {
                std::cout << *it;
                if (++it != container.end())
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }

    template<typename T>
    static void merge(T& con, int left, int mid, int right)
    {
        T leftCon, rightCon;
        for (int i = left; i <= mid; ++i)
            leftCon.push_back(con[i]);
        for (int i = mid + 1; i <= right; ++i)
            rightCon.push_back(con[i]);
        int i = 0, j = 0, k = left;
        while (i < (int)leftCon.size() && j < (int)rightCon.size())
        {
            if (leftCon[i] < rightCon[j])
                con[k++] = leftCon[i++];
            else
                con[k++] = rightCon[j++];
        }
        while (i < (int)leftCon.size())
            con[k++] = leftCon[i++];
        while (j < (int)rightCon.size())
            con[k++] = rightCon[j++];
    }

    template<typename T>
    static void splitContainer(T& con, int left, int right)
    {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        splitContainer(con, left, mid);
        splitContainer(con, mid + 1, right);
        merge(con, left, mid, right);
    }
};