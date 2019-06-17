#include <iostream>
#include <string.h>
using namespace std;
 
int main(void) {
	int n = 0;
    char str[100], *pch;
    
    memset(str, 0, sizeof(str));
    cin.getline(str, 100);
    n = atoi (str);
    
    if (n < 0) return 0;
    
    for (int i = 0; i < n; i++)
    {
        memset(str, 0, sizeof(str));
        cin.getline(str, 100);
        pch = strtok (str," ");
        for (int j = 1; pch != NULL; j++)
        {
            if (j == 7)
            {
                cout << pch << endl;
                break;
            }
            pch = strtok (NULL, " ");
        }
        
        cin.getline(str, 100);// read chosen cards
    }
 
	return 0;
}
