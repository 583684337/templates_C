#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 1000000
//small->big
void mergesort(double d[], int len);
void mergesort_recursive(double d[], int left, int right);
void quicksort(double[], int left, int right);
void bubblesort(double[], int);
void insertionsort(double[], int);        //直接插入
void insertionsort_binary(double[], int); //折半插入排序
void selectionsort(double[], int);
void shellsort(double[], int);
void datagenerate(int);
void copy(const double rawdata[], double copy[], int);

int main(void)
{

    //double rawdata[LEN] = {7, 3, 1, 5, 10, 9, 8, 2, 6, 4, 14, 11, 12, 13};
    //double sorted[LEN];
    double *rawdata, *sorted;
    rawdata = (double *)malloc(sizeof(double) * LEN);
    sorted = (double *)malloc(sizeof(double) * LEN);
    if (rawdata == NULL || sorted == NULL)
        return 1;
    int start, end, i;
    /*for (i = 0; i < LEN; i++)
    {
        printf("please enter %d data:", i + 1);
        scanf("%lf", rawdata + i);
    }*/

    datagenerate(LEN);

    FILE *fp = fopen("1.txt", "r");
    if (fp == NULL)
        return 1;

    for (i = 0; i < LEN; i++)
    {
        fscanf(fp, "%lf", &rawdata[i]);
        printf("%d/%d\r", i + 1, LEN);
    }

    fclose(fp);
    printf("\n data input finished!\n");

    /*     copy(rawdata, sorted, LEN);
    start = clock();
    insertionsort(sorted, LEN);
    end = clock();
    printf("insertionsort time consumption: %d ms\n", end - start);
 */
    /*     copy(rawdata, sorted, LEN);
    start = clock();
    bubblesort(sorted, LEN);
    end = clock();
    printf("bubblesort time consumption: %d ms\n", end - start);
 */
    copy(rawdata, sorted, LEN);
    start = clock();
    quicksort(sorted, 0, LEN - 1);
    end = clock();
    printf("quicksort time consumption: %d ms\n", end - start);

    /*     copy(rawdata, sorted, LEN);
    start = clock();
    selectionsort(sorted, LEN);
    end = clock();
    printf("selectionsort time consumption: %d ms\n", end - start);
 */
    /*     copy(rawdata, sorted, LEN);
    start = clock();
    insertionsort_binary(sorted, LEN);
    end = clock();
    printf("insertionsort_binary time consumption: %d ms\n", end - start);
 */
    copy(rawdata, sorted, LEN);
    start = clock();
    shellsort(sorted, LEN);
    end = clock();
    printf("shellsort time consumption: %d ms\n", end - start);

    copy(rawdata, sorted, LEN);
    start = clock();
    mergesort_recursive(sorted, 0, LEN - 1);
    end = clock();
    printf("mergesort_recursive time consumption: %d ms\n", end - start);

    copy(rawdata, sorted, LEN);
    start = clock();
    mergesort(sorted, LEN);
    end = clock();
    printf("mergesort time consumption: %d ms\n", end - start);

    fp = fopen("out.txt", "w");
    if (fp == NULL)
        return -1;
    for (i = 0; i < LEN; i++)
    {
        fprintf(fp, "%-5.0lf\t", sorted[i]);
        printf("%d/%d\r", i + 1, LEN);
        if ((i + 1) % 10 == 0)
            fprintf(fp, "\n");
    }
    fclose(fp);
    printf("\nSort over\n");

    /*  
    for (i = 0; i < LEN; i++)
    {
        printf("%.0lf ", sorted[i]);
    }
*/
    system("pause");
    return 0;
}

void mergesort(double d[], int len)
{
    double *a, *b, *temp;
    int seg, start, end, mid;
    a = d;
    b = (double *)malloc(len * sizeof(double));
    if (b == NULL)
        return;
    for (seg = 1; seg < len; seg <<= 1)
    {
        int i, j, k = 0;
        for (start = 0; start < len; start = end)
        {
            mid = (start + seg) > len ? len : start + seg;
            end = (mid + seg) > len ? len : mid + seg;
            i = start, j = mid;
            while (i < mid && j < end)
                b[k++] = a[j] < a[i] ? a[j++] : a[i++];
            while (i < mid)
                b[k++] = a[i++];
            while (j < end)
                b[k++] = a[j++];
        }
        temp = a;
        a = b;
        b = temp;
    }
    if (b == d)
    {
        for (int i = 0; i < len; i++)
            d[i] = a[i];
        free(a);
    }
    else
        free(b);
    return;
}

void mergesort_recursive(double d[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergesort_recursive(d, left, mid);
        mergesort_recursive(d, mid + 1, right);
        double *temp = NULL;
        temp = (double *)malloc(sizeof(double) * (right - left + 1));
        if (temp == NULL)
            return;
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right)
            if (d[i] > d[j])
                temp[k++] = d[j++];
            else
                temp[k++] = d[i++];
        while (i <= mid)
            temp[k++] = d[i++];
        while (j <= right)
            temp[k++] = d[j++];
        for (i = 0; i < k; i++)
            d[left + i] = temp[i];
        free(temp);
    }
    return;
}

void quicksort(double rawdata[], int left, int right)
{
    int i = left, j = right;
    double pivot;
    double temp;
    pivot = rawdata[(left + right) / 2];
    while (i <= j)
    {
        while (rawdata[j] > pivot)
            j--;
        while (rawdata[i] < pivot)
            i++;
        if (i <= j)
        {
            temp = rawdata[i];
            rawdata[i] = rawdata[j];
            rawdata[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j)
        quicksort(rawdata, left, j);
    if (right > i)
        quicksort(rawdata, i, right);
    return;
}

void shellsort(double rawdata[], int r)
{
    int gap, i, j;
    double temp;
    for (gap = r / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < r; i++)
        {
            for (j = i - gap; j >= 0 && rawdata[j] > rawdata[j + gap]; j -= gap)
            {
                temp = rawdata[j];
                rawdata[j] = rawdata[j + gap];
                rawdata[j + gap] = temp;
            }
        }
    }
    return;
}

void insertionsort_binary(double rawdata[], int r)
{
    int i, j;
    int high, low, mid;
    double temp;
    for (i = 1; i < r; i++)
    {
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (rawdata[i] < rawdata[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i; j > low; j--) //为什么是j>low呢???
        {
            temp = rawdata[j];
            rawdata[j] = rawdata[j - 1];
            rawdata[j - 1] = temp;
        }
    }
    return;
}

void bubblesort(double rawdata[], int r)
{
    int i, j;
    double temp;
    for (j = 1; j < r; j++)
    {
        for (i = 0; i < r - j; i++)
        {
            if (rawdata[i] > rawdata[i + 1])
            {
                temp = rawdata[i];
                rawdata[i] = rawdata[i + 1];
                rawdata[i + 1] = temp;
            }
        }
    }
    return;
}

void insertionsort(double rawdata[], int r)
{
    int i, j;
    double temp;
    for (i = 1; i < r; i++)
    {
        for (j = i; j > 0; j--)
        {
            if (rawdata[j] < rawdata[j - 1])
            {
                temp = rawdata[j];
                rawdata[j] = rawdata[j - 1];
                rawdata[j - 1] = temp;
            }
            else
                break;
        }
    }
    return;
}

void selectionsort(double rawdata[], int r)
{
    int i, j;
    double temp;
    for (i = 0; i < r; i++)
    {
        for (j = i + 1; j < r; j++)
        {
            if (rawdata[j] < rawdata[i])
            {
                temp = rawdata[j];
                rawdata[j] = rawdata[i];
                rawdata[i] = temp;
            }
        }
    }

    return;
}
void copy(const double rawdata[], double copy[], int r)
{
    int i;
    for (i = 0; i < r; i++)
        copy[i] = rawdata[i];
    return;
}

void datagenerate(int r)
{
    FILE *fp = fopen("1.txt", "w");
    if (fp == NULL)
    {
        printf("Error!\n");
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < r; i++)
        fprintf(fp, "%-7d%c", 11 * (rand() % 19979) - rand() % 17171, ((i + 1) % 10 == 0) ? '\n' : '\t');
    fclose(fp);
    return;
}