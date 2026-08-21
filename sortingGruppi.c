/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "sortingGruppi.h"

void QuickSortRG(gruppo* A, int l, int r);
int partitionG(gruppo* A, int l, int r);
void SwapG(gruppo *v, int n1, int n2);

void SortGruppi(gruppo* A, int N)
{
    int l=0, r=N-1;
    QuickSortRG(A, l, r);
}

void QuickSortRG(gruppo* A, int l, int r)
{
    int q;
    if (r <= l)		return;
    q = partitionG(A, l, r);
    QuickSortRG(A, l, q - 1);
    QuickSortRG(A, q + 1, r);

    return;
}

int partitionG(gruppo* A, int l, int r)
{
    int i, j;
    gruppo x = A[r];
    i = l-1;
    for (j=l; j<=r-1; j++)
    {
        if(GRUPPOleq(A[j], x))
        {
            i++;
            SwapG(A, i, j);
        }
    }
    SwapG(A, i+1, r);

    return i+1;
}

void SwapG(gruppo *v, int n1, int n2)
{
    gruppo tmp;

    tmp  = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;

    return;
}