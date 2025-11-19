#include <stdio.h>

#define SIZE 100000

typedef enum {
    PRINT,
    SORT,
    SEARCH,
} commands;

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
commands choose_command(const char* str) {
    return str[0] == 'p' ? PRINT :
        (str[0] == 'x' ? XOR : 
            (str[1] == 'o' ? SORT : SEARCH));
}

void sort(int *arr, int len){
    for (int i=1;i<len;i++){
        for (int j=i; j>0 && arr[j]<arr[j-1];j--) {
            int temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
        }
    }
}

int binarySearch(int *arr, int len, int target) {
    int left = 0;
    int right = len - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

void print(int *arr, int len){
    for (int i=0;i<len;i++){
        if (i==len-1) {printf("%d",arr[i]); break;}
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int nums1[SIZE];
    int nums2[SIZE];

    int n;

    while (scanf("%d") !=)
    {
        /* code */
    }
    

    char command[20];
    while (scanf("%s",command)!=EOF){

        switch (choose_command(command))
        {
        case PRINT:
            print(nums1, n);
            print(nums2, n);
            break;
        
        case SORT:
            sort(nums1, n);
            sort(nums2, n);
            break;
        case SEARCH:
            int target;
            scanf("%d",&target);
            if (binarySearch(nums1,n,target)!=-1){
                printf("%d %d\n",1,binarySearch(nums1,len,num)+1);
            } else if (binarySearch(nums2,len,num)!=-1){
                printf("%d %d\n",2,binarySearch(nums2,len,num)+1);
            } else printf("-1\n");
            break;
        }

    }



    return 0;
}
