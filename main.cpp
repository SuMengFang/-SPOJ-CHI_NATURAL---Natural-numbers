#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define BASE 100

int read2base(char *string, unsigned int *num_array);
void intArray2string(int msb, unsigned int *num_array, char *output);
int compare(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B);
int fullAdder(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, bool sub);
int multiplier(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, 
    unsigned int *output, unsigned int m);
int divider(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, 
    unsigned int *output);

int main(void) {
    unsigned int n, M, msb_A, msb_B, msb, num_A[1024], num_B[1024], num_C[1024];
    char op[10], str[65536], output[65536], *pch;
    
    memset(str, 0, sizeof(str));
    cin.getline(str, 65536);
    n = atoi (str);
    
    if (n < 0) return 0;
    
    for (unsigned int i = 0; i < n; i++)
    {
        memset(op, 0, sizeof(op));
        memset(str, 0, sizeof(str));
        memset(num_A, 0, sizeof(num_A));
        memset(num_B, 0, sizeof(num_B));
        memset(num_C, 0, sizeof(num_C));
        M = 0;
        cin.getline(str, 65536);
        
        pch = strtok (str," ");
        int j = 0;
        while (pch != NULL)
        {
            if (j == 0) sprintf(op, "%s", pch);
            else if (j == 1) msb_A = read2base(pch, num_A);
            else if (j == 2) msb_B = read2base(pch, num_B);
            else if (j == 3) M = atoi (pch);
            
            pch = strtok (NULL, " ");
            j++;
        }
        
        if (strcmp (op, "<") == 0) cout << compare(msb_A, msb_B, num_A, num_B) << endl;
        else if (strcmp (op, "+") == 0 || strcmp (op, "-") == 0)
        {
            msb = fullAdder(msb_A, msb_B, num_A, num_B, strcmp (op, "-") == 0);
            intArray2string(msb, num_A, output);
            cout << output << endl;
        }
        else if (strcmp (op, "*") == 0 || strcmp (op, "#") == 0)
        {
            msb = multiplier(msb_A, msb_B, num_A, num_B, num_C, M);
            intArray2string(msb, num_C, output);
            cout << output << endl;
        }
        else if (strcmp (op, "/") == 0)
        {
            msb = divider(msb_A, msb_B, num_A, num_B, num_C);
            intArray2string(msb, num_C, output);
            cout << output << " ";
            intArray2string(msb_B, num_A, output);
            cout << output << endl;
        }
    }
    
	return 0;
}

int read2base(char *string, unsigned int *num_array)
{
	char tmp[65536];
	int str_index, num_index = 0;
	str_index = strlen(string) - 2;
	if (str_index < 0) str_index = 0;
	
	sprintf(tmp, "%s", string);
	while (str_index >= 0)
	{
	    num_array[num_index] = atoi (tmp + str_index);
	    num_index++;
	    if (str_index == 0) break;
	  
	    tmp[str_index] = '\0';
	    str_index -= 2;
	    if (str_index < 0) str_index = 0;
	}
	
	while (num_index > 1 && num_array[num_index - 1] == 0)
	    num_index--;
	if (num_index < 0) num_index = 0;
	
	return num_index;
}

void intArray2string(int msb, unsigned int *num_array, char *output)
{
	char tmp[65536];
	int i = msb - 1;
	sprintf(output, "%d", 0);
	
	while (i >= 0)
	{
	    if (num_array[i] != 0) break;
	    i--;
	}
	if (i < 0) return;
	
	memset(output, 0, sizeof(output));
	while (i >= 0)
	{
	    sprintf(tmp, "%s", output);
	    if (strlen(tmp) == 0) sprintf(output, "%d", num_array[i]);
	    else sprintf(output, "%s%02d", tmp, num_array[i]);
	    i--;
	}
}

int compare(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B)
{
    for (int i = msb_A - 1; i >= 0; i--)
	{
	    if (num_A[i] != 0) break;
	    msb_A--;
	}
	for (int i = msb_B - 1; i >= 0; i--)
	{
	    if (num_B[i] != 0) break;
	    msb_B--;
	}
    
    if (msb_A == 0 && msb_B == 0) return 0;
    else if (msb_A == 0) return 1;
    else if (msb_B == 0) return -1;
    
    int output = 0;
    
    if (msb_A > msb_B) output = -1;
    else if (msb_A < msb_B) output = 1;
    else
    {
        unsigned int msb = msb_A;// msb_A == msb_B
        while (msb > 0 && output == 0)
        {
            if (num_A[msb - 1] > num_B[msb - 1]) output = -1;
            else if (num_A[msb - 1] < num_B[msb - 1]) output = 1;
            else msb--;
        }
    }
    
    return output;
}

int fullAdder(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, bool sub)
{
    int cmp = 0;
    if (sub && (cmp = compare(msb_A, msb_B, num_A, num_B)) >= 0)
    {
        memset(num_A, 0, sizeof(num_A));
        return 1;
    }
    
    int borrow = 0, ptr = 0;
    unsigned int msb = msb_A >= msb_B ? msb_A : msb_B;
    for (ptr = 0; ptr < msb; ptr++)
    {
        if (!sub)
        {
            num_A[ptr] += num_B[ptr];
            num_A[ptr + 1] += num_A[ptr] / BASE;
            num_A[ptr] %= BASE;
        }
        else
        {
            bool need2borrow = num_A[ptr] < (num_B[ptr] + borrow);
            if (need2borrow) num_A[ptr] += BASE;
            num_A[ptr] -= (num_B[ptr] + borrow);
            borrow = need2borrow ? 1 : 0;
        }
    }
    
    if (!sub && num_A[ptr] > 0) msb++;
    
    return msb;
}

int multiplier(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, 
    unsigned int *output, unsigned int m)
{
    // skip x * 0
    memset(output, 0, sizeof(output));
    if ((msb_A <= 1 && num_A[0] == 0) || (msb_B <= 1 && num_B[0] == 0)) return 1;
    
    int carry = 0, ptr = 0;
    unsigned int msb = msb_A + msb_B - 1;
    while (ptr < msb)
    {
        if (ptr < m)
        {
            ptr++;
            continue;
        }
        int sum = 0;
        for (int ptr_A = 0; ptr_A <= ptr; ptr_A++)
        {
            int ptr_B = ptr - ptr_A;
            if (ptr_A < msb_A && ptr_B < msb_B) sum += num_A[ptr_A] * num_B[ptr_B];
        }
        sum += carry;
        carry = sum / BASE;
        output[ptr - m] = sum % BASE;
        ptr++;
    }
    
    if (carry > 0)
    {
        output[ptr - m] = carry;
        msb++;
    }
    
    return msb;
}

int divider(unsigned int msb_A, unsigned int msb_B, unsigned int *num_A, unsigned int *num_B, 
    unsigned int *output)
{
    unsigned int msb = msb_A - msb_B + 1;
    int cmp = 0, ptr;
    memset(output, 0, sizeof(output));
    // check number correct
    if ((msb_B <= 1 && num_B[0] == 0) || msb_A <= 1 && num_A[0] == 0)
    {
        memset(num_A, 0, sizeof(num_A));
        return 1;
    }
    else if ((cmp = compare(msb_A, msb_B, num_A, num_B)) >= 0)
    {
        if (cmp == 0)
        {
            memset(num_A, 0, sizeof(num_A));
            output[0] = 1;
            msb_A = 1;
        }
        
        return msb_A;
    }
    else if (msb_B == 1)
    {
        for (ptr = msb - 1; ptr >= 0; ptr--)
        {
            output[ptr] = (num_A[ptr] + num_A[ptr + 1] * BASE) / num_B[0];
            num_A[ptr] = (num_A[ptr] + num_A[ptr + 1] * BASE) % num_B[0];
            num_A[ptr + 1] = 0;
        }
        
        return msb;
    }
    
    for (ptr = msb - 1; ptr >= 0; ptr--)
    {
        //output[ptr] = 0;
        if ((cmp = compare(msb_A - ptr, msb_B, num_A + ptr, num_B)) <= 0)
        {
            int upper = cmp == 0 ? 1 : 100, lower = cmp == 0 ? 1 : 0;
            while (upper - lower > 1)
            {
            	// multiply
            	unsigned int msb_C, num_C[1024], msb_D, num_D[1024];
                memset(num_D, 0, sizeof(num_D));
                num_C[0] = (upper + lower) / 2;
                msb_D = multiplier(msb_B, 1, num_B, num_C, num_D, 0);
                
                // compare
                cmp = compare(msb_A - ptr, msb_D, num_A + ptr, num_D);
                if (cmp <= 0) lower = num_C[0];
                if (cmp >= 0) upper = num_C[0];
            }
            
            // do result
            output[ptr] = lower;
            if (output[ptr] != 0)
            {
                unsigned int msb_C, num_C[1024], msb_D, num_D[1024];
                memset(num_D, 0, sizeof(num_D));
                num_C[0] = lower;
                msb_D = multiplier(msb_B, 1, num_B, num_C, num_D, 0);
                msb_A = fullAdder(msb_A - ptr, msb_D, num_A + ptr, num_D, true);
                msb_A += ptr;
            }
        }
    }
    
    return msb;
}