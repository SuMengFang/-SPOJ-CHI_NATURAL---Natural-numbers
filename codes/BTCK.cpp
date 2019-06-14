#include <iostream>
#include <string.h>
using namespace std;

int findPermutation(int K, int index, int *num, int *result);

int main(void) {
	int n = 0;
    char str[100], *pch;
    
    memset(str, 0, sizeof(str));
    cin.getline(str, 1024);
    n = atoi (str);
    
    if (n < 0) return 0;
    
    for (unsigned int i = 0; i < n; i++)
    {
        int j = 0, K = 0, num[10], result[10];
        memset(str, 0, sizeof(str));
        memset(num, 0, sizeof(num));
        memset(result, 0, sizeof(result));
        
        cin.getline(str, 100);
        pch = strtok (str," ");
        while (pch != NULL)
        {
            num[j] = atoi (pch);
            result[j] = j;
            pch = strtok (NULL, " ");
            j++;
        }
        
        memset(str, 0, sizeof(str));
        cin.getline(str, 100);
        K = atoi (str);
        
        if (findPermutation(K, 0, num, result) == -1) cout << -1 << endl;//, &count, countArray
        else
        {
            for (j = 0; j < 10; j++)
            {
                if (j == 9) cout << result[j] << endl;
                else cout << result[j] << " ";
            }
        }
    }
 
	return 0;
}

int findPermutation(int K, int index, int *num, int *result)
{
	
    int tmp[10 - index], origin[10 - index], ptr, ret = -1, sum = 0, max, min, i, swap;
    
    // store enums by Insertion Sort
    for (i = index; i < 10; i++)
    {
        origin[i - index] = result[i];// store origin order
        ptr = i - index;
        while (ptr > 0 && result[i] < tmp[ptr - 1])
        {
            tmp[ptr] = tmp[ptr - 1];
            ptr--;
        }
        tmp[ptr] = result[i];
        if (i != index) sum += num[i];
    }
    
    // put into result array in order
    for (i = 0; i < 10 - index; i++) result[index + i] = tmp[i];
    
    // try each enum
    for (i = 0; i < 10 - index; i++)
    {
        swap = result[index];
        result[index] = result[index + i];
        result[index + i] = swap;
        
        max = K - (result[index] * num[index]);
        min = tmp[i == 0 ? 1 : 0];
        if (max < 0 || min * sum > max) ret = -1;
        else if (index >= 8)
        {
            if (index == 8) result[9] = tmp[1 - i];
            max -= result[9] * num[9];
            if (max >= 0) ret = 0;
            else ret = -1;
        }
        else ret = findPermutation(max, index + 1, num, result);//, count, countArray
        
        if (ret == 0) break;
        
        swap = result[index];
        result[index] = result[index + i];
        result[index + i] = swap;
    }
    
    if (ret == -1) for (i = 0; i < 10 - index; i++) result[index + i] = origin[i];
    
    return ret;
}
