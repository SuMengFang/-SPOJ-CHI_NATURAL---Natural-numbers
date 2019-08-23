#include <stdio.h>
using namespace std;

#define MMAX 2000
#define NMAX 10000

int M = 0, N = 0;
int mat[MMAX][MMAX]; 
long aux[MMAX + 1][MMAX + 1]; 
long BIT[MMAX + 1][MMAX + 1];

int boundary(int min, int max, int val)
{
    return val < min ? min : (val > max ? max : val);
}

bool isValid(int min, int max, int val)
{
    return (val < min || val > max) ? false : true;
}

void updateBIT(int x, int y, long val) 
{
    int saved_y = y;

    for (; x > 0 && x <= N; x += (x & -x))
        for (y = saved_y; y > 0 && y <= M; y += (y & -y))
            BIT[x][y] += val;
} 
  
long getSum(int x, int y)
{ 
    long sum = 0;
    int saved_y = y;

    for (; x > 0; x -= x&-x)
        for (y = saved_y; y > 0; y -= y&-y)
            sum += BIT[x][y];

    return sum;
} 
  
void constructAux()
{
    for (int i=0; i<=N; i++)
        for (int j=0; j<=M; j++)
            BIT[i][j] = aux[i][j] = 0;

    for (int i=1; i<=N; i++)
        for (int j=1; j<=M; j++)
	    aux[i][j] = mat[i-1][j-1];
} 
  
void construct2DBIT()
{
    constructAux();
  
    for (int i=1; i<=N; i++)
    { 
        for (int j=1; j<=M; j++)
        { 
            long v1 = getSum(i, j);
            long v2 = getSum(i, j-1);
            long v3 = getSum(i-1, j-1);
            long v4 = getSum(i-1, j);

            updateBIT(i, j, aux[i][j]-(v1-v2-v4+v3));
        } 
    }
} 
  
void answerQueries(int X1, int Y1, int X2, int Y2)
{
    long ans = 0;

    if (!(X1 == X2 && !isValid(1, N, X1)) &&	// [X1, X2] & [1, N] overlapping
	!(Y1 == Y2 && !isValid(1, M, Y1)))	// [Y1, Y2] & [1, M] overlapping
    {
	int x1 = X1 < X2 ? X1 : X2;
	int x2 = X1 > X2 ? X1 : X2;
	int y1 = Y1 < Y2 ? Y1 : Y2;
	int y2 = Y1 > Y2 ? Y1 : Y2;

	x1 = boundary(1, N, x1);
	x2 = boundary(1, N, x2);
	y1 = boundary(1, M, y1);
	y2 = boundary(1, M, y2);
	
	ans = getSum(x2    , y2    )
	    - getSum(x2    , y1 - 1)
	    - getSum(x1 - 1, y2    )
	    + getSum(x1 - 1, y1 - 1);
    }
  
    printf("%ld\n", ans);
}

int main()
{
    int Q = 0, n = 0;
    
    scanf("%d %d %d", &N, &M, &Q);
    if (!isValid(1,      MMAX, N)) 	return 0;
    if (!isValid(1,      MMAX, M))	return 0;
    if (!isValid(1, 10 * NMAX, Q))	return 0;
    
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M; j++)
        {
            scanf("%d", &n);
            mat[i][j] = isValid(1, NMAX, n) ? n : 0;
        } 
    }

    construct2DBIT();
    
    // read and do queries
    int num[4], max, type;
    bool doContinue;
    for (int i=0; i<Q; i++)
    {
        // initial
	max = NMAX;
        type = 0;
        doContinue = false;
        
        scanf("%d", &type);
        for (int j = 0; j < (2 + type); j++)
        {
            scanf("%d", &n);
	    if (doContinue)
		continue;
            max = (j == 2 && type == 1) ? NMAX : ((j % 2 == 0) ? N : M);
            if (type == 1 && !isValid(1, max, n))
		doContinue = true;
            else
            	num[j] = boundary(0, max + 1, n);
        }
        if (doContinue)
	    continue;
        
        // do query
        if (type == 1)
            updateBIT(num[0], num[1], num[2]);
        else if (type == 2)
            answerQueries(num[0], num[1], num[2], num[3]);
    }

    return 0;
}
