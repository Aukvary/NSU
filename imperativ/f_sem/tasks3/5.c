// #include <stdio.h>

// char is_func(int nums[][2], int m) {
//     for (int i = 0; i < m; i++) 
//         for (int j = i + 1; j < m; j++) 
//             if (nums[i][0] == nums[j][0] && nums[i][1] != nums[j][1]) 
//                 return 0;  

//     return 1;
// }

// char always_exists(int nums[][2], int n, int m) {
//     int existing[100000];

//     for (int i = 0; i < n; i++) 
//         existing[i] = 0;

//     for (int i = 0; i < m; i++)
//         existing[nums[i][0] - 1] = 1;

//     for (int i = 0; i < n; i++)
//         if (!existing[i])
//             return 0;

//     return 1;
// }

// char is_injective(int nums[][2], int m) {
//     for (int i = 0; i < m; i++) 
//         for (int j = i + 1; j < m; j++) 
//             if (nums[i][1] == nums[j][1] && nums[i][0] != nums[j][0]) 
//                 return 0;
            
        
    
//     return 1;
// }

// char is_surjective(int nums[][2], int n, int m) {
//     int existing[n];

//     for (int i = 0; i < n; i++) 
//         existing[i] = 0;

//     for (int i = 0; i < m; i++) 
//         existing[nums[i][1] - 1] = 1;
    

//     for (int i = 0; i < n; i++) 
//         if (!existing[i])
//             return 0;


//     return 1;
// }

// int main() {
//     int n;
//     int m;

//     scanf("%d %d", &n, &m);

//     int pairs[m][2];

//     for (int i = 0; i < m; i++)
//         scanf("%d %d", &pairs[i][0], &pairs[i][1]);

//     if (!is_func(pairs, m)) {
//         printf("0");
//         return 0;
//     }
    
//     printf("1");
//     char inj = is_injective(pairs, m);
//     char sur = is_surjective(pairs, n, m);

//     if (always_exists(pairs, n, m))
//         printf(" 2");
//     if (inj)
//         printf(" 3");
//     if (sur)
//         printf(" 4");
//     if (inj && sur)
//         printf(" 5");

//     return 0;
// }