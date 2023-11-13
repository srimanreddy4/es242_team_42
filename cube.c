#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>  

typedef int cube_t[8][3];
int vis = 0;
//no in clk 
//top clk,clk bottom

/*
white = 0
red = 1
blue = 2
green = 3
orange = 4
yellow = 5
*/
  
struct Node {  
    struct vertex* data;    
    struct Node* next;  
};  
  
struct Node* front = NULL;  
struct Node* rear = NULL;  
  
void enqueue(struct vertex* new_vertex) {  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    new_node->data = new_vertex;  
    new_node->next = NULL;  
    if (front == NULL && rear == NULL) {  
        front = rear = new_node;  
        return;  
    }  
    rear->next = new_node;  
    rear = new_node;  
};

struct Node1 {  
    cube_t data;    
    struct Node1* next;  
}; 

struct Node1* front1 = NULL;  
struct Node1* rear1 = NULL;  
void venqueue(cube_t cube ) { 
    vis++;
    struct Node1* new_node = (struct Node1*)malloc(sizeof(struct Node1));  
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
        new_node->data[i][j] = cube[i][j];              
        }
        
    }
    
    new_node->next = NULL;  
    if (front1 == NULL && rear1 == NULL) {  
        front1 = rear1 = new_node;  
        return;  
    }  
    rear1->next = new_node;  
    rear1 = new_node;  
;}

struct vertex* dequeue() {  
    if (front == NULL) {  
        printf("Queue is empty");  
        return NULL;  
    }  
    struct Node* temp = front;  
    struct vertex* element = temp->data;  
    if (front == rear) {  
        front = rear = NULL;  
    }  
    else {  
        front = front->next;  
    }  
    free(temp);  
    return element;  
}; 

void move_r(cube_t nxt_cube,cube_t cube){ 
    nxt_cube[1][0] = cube[2][2];
    nxt_cube[1][1] = cube[2][0];
    nxt_cube[1][2] = cube[2][1];

    nxt_cube[2][0] = cube[6][1];
    nxt_cube[2][1] = cube[6][0];
    nxt_cube[2][2] = cube[6][2];

    nxt_cube[5][0] = cube[1][0];
    nxt_cube[5][1] = cube[1][2];
    nxt_cube[5][2] = cube[1][1];

    nxt_cube[6][0] = cube[5][1];
    nxt_cube[6][1] = cube[5][2];
    nxt_cube[6][2] = cube[5][0];
}
void move_u(cube_t nxt_cube,cube_t cube){ 
    nxt_cube[0][0] = cube[3][0];
    nxt_cube[0][1] = cube[3][1];
    nxt_cube[0][2] = cube[3][2];

    nxt_cube[1][0] = cube[0][0];
    nxt_cube[1][1] = cube[0][1];
    nxt_cube[1][2] = cube[0][2];

    nxt_cube[2][0] = cube[1][0];
    nxt_cube[2][1] = cube[1][1];
    nxt_cube[2][2] = cube[1][2];

    nxt_cube[3][0] = cube[2][0];
    nxt_cube[3][1] = cube[2][1];
    nxt_cube[3][2] = cube[2][2];
}
void move_f(cube_t nxt_cube,cube_t cube){ 
    nxt_cube[0][0] = cube[1][2];
    nxt_cube[0][1] = cube[1][0];
    nxt_cube[0][2] = cube[1][1];

    nxt_cube[1][0] = cube[5][1];
    nxt_cube[1][1] = cube[5][0];
    nxt_cube[1][2] = cube[5][2];

    nxt_cube[5][0] = cube[4][1];
    nxt_cube[5][1] = cube[4][2];
    nxt_cube[5][2] = cube[4][0];

    nxt_cube[4][0] = cube[0][0];
    nxt_cube[4][1] = cube[0][2];
    nxt_cube[4][2] = cube[0][1];
}

void nxt_confg(cube_t nxt_conf[9],cube_t cube){
    move_r(nxt_conf[0],cube);
    move_u(nxt_conf[1],cube);
    move_f(nxt_conf[2],cube);
    move_r(nxt_conf[3],nxt_conf[0]);
    move_u(nxt_conf[4],nxt_conf[1]);
    move_f(nxt_conf[5],nxt_conf[2]);
    move_r(nxt_conf[6],nxt_conf[3]);
    move_u(nxt_conf[7],nxt_conf[4]);
    move_f(nxt_conf[8],nxt_conf[5]);
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j==0 || j==3 || j==4 || j==7){
                for (int k = 0; k < 3; k++)
                {
                    nxt_conf[i*3][j][k] = cube[j][k];
                }
                
            }
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j==4 || j==5 || j==6 || j==7){
                for (int k = 0; k < 3; k++)
                {
                    nxt_conf[(i*3)+1][j][k] = cube[j][k];
                }
                
            }
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j==2 || j==3 || j==6 || j==7){
                for (int k = 0; k < 3; k++)
                {
                    nxt_conf[(i*3)+2][j][k] = cube[j][k];
                }
                
            }
        }
        
    }
    
};

struct vertex {  
    int path[12];
    cube_t cube;  
};

int is_equal(cube_t cube1,cube_t cube2){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cube1[i][j] != cube2[i][j]){
                return 0;
            }
        }
        
    }
    return 1;
    
}


int main() {  
    int input_cube[8][3];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &input_cube[i][j]);             
        }
    }
    int solid_cube[8][3] = {{0,3,4},
                            {0,4,2},
                            {0,2,1},
                            {0,1,3},
                            {3,4,5},
                            {4,2,5},
                            {2,1,5},
                            {1,3,5}};
    venqueue(solid_cube);
    struct vertex* new_vertex = (struct vertex*)malloc(sizeof(struct vertex));  
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
        new_vertex->cube[i][j] = solid_cube[i][j];              
        }
    }
    for (int i = 0; i < 12; i++)
    {
        new_vertex->path[i] =0;
    }  
    enqueue(new_vertex);

    int ls = 1;
    while ((front != NULL) && ls)
    {
        struct vertex* head = dequeue();
        cube_t nxt_confgs[9];
        nxt_confg(nxt_confgs,head->cube);
        for (int i = 0; i < 9; i++)
        {
            struct Node1* ptr = front1;
            for (int j = 0; j < vis; j++)
            {
                if (is_equal(nxt_confgs[i],ptr->data))
                {
                    break;
                }
                venqueue(nxt_confgs[i]);
                struct vertex* new_vertex = (struct vertex*)malloc(sizeof(struct vertex));  
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                    new_vertex->cube[k][l] = nxt_confgs[i][k][l];              
                    }
                }
                for (int k = 0; k < 12; k++)
                {
                    if (head->path[k] == 0){
                        new_vertex->path[k] = i+1;
                        if (k == 11){
                            ls = 0; 
                        }
                        break;
                    }else{
                        new_vertex->path[k] = head->path[k];
                    }
                }
                if (is_equal(input_cube,new_vertex->cube)){
                    for (int k = 0; k < 12; k++)
                    {
                        printf("%d", new_vertex->path[k]);
                    }
                    return 0;
                    
                }
                enqueue(new_vertex);

                ptr = ptr->next;
            }   
        }
        free(head);
    }

    
    return 0;  
}  
// int is_valid(cube_t cube) 
// {
//     int count[6];
//     for (int i = 0;i < 8;i++){
//         for (int j = 0; j < 3; j++)
//         {
//            count[cube[i][j]]++;
//         }
//     }
//     for (int i = 0; i < 6; i++)
//     {
//         if (count[i]!=4){return 0;}
        
//     }
//     for (int i = 0; i < 8; i++)
//     {
//         int col[6] = {0,0,0,0,0,0};
//         for (int j = 0; j < 3; j++)
//         {
//             col[cube[i][j]]++;
//         }
//         if ((col[0]==1 && col[5]==1) || (col[1]==1 && col[4]==1) || (col[2]==1 && col[3]==1))
//         {
//             return 0;
//         }
         

//     }
    
//     return 1;
// }

