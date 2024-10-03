#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// glibc-2.31
// gcc slime_machine.c -o chal -fno-stack-protector  -no-pie 

char *slime_ptrs[0x20];
int slime_size[0x20];
int slime_status[0x20];
int idx = 0;


int shell(){
    system("/bin/sh");
}

void init()
{
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
}

int read_num()
{
    int num;
    
    scanf("%d", &num);

    return num;
}

void menu()
{
    puts("=== NAUP'S SLIME MACHINE ===");
    puts("1) Create BLUE SLIME");
    puts("2) Create GREEN SLIME");
    puts("3) Get SLIME information");
    puts("4) Set SLIME information");
    puts("5) KILL SLIME");
    puts("6) End");
    printf("# ");
}

void create()
{
    int size;

    if (idx >= 0x20) {
        return;
    }

    printf("size:\n");
    scanf("%d", &size);
    if (size <= 0x20 || size >=0x70){
        printf('size err!');
        return;
    } 

    slime_ptrs[idx] = malloc(size);
    slime_size[idx] = size;
    slime_status[idx] = 1;
    
    printf("Create: SLIME[%d]\n", idx);

    idx++;
}

void create2()
{
    int size;

    if (idx >= 0x20) {
        return;
    }

    printf("size:\n");
    scanf("%d", &size);

    slime_ptrs[idx] = calloc(1, size);
    slime_size[idx] = size;
    slime_status[idx] = 1;
    
    printf("Create: SLIME[%d]\n", idx);

    idx++;
}

void get()
{
    int idx;

    printf("idx:\n");
    scanf("%d", &idx);

    if (slime_status[idx]) {
        printf("SLIME[%d]: %s\n", idx, slime_ptrs[idx]);
    }
}

void set()
{
    int idx;

    printf("idx:\n");
    scanf("%d", &idx);

    printf("str:\n");
    read(0, slime_ptrs[idx], slime_size[idx]);
    
}

void delete()
{
    int idx;

    printf("idx:\n");
    scanf("%d", &idx);
    
    if (slime_ptrs[idx] && slime_status[idx]) {
        free(slime_ptrs[idx]);
        slime_status[idx] = 0;
    }
}

int a=1;

int main(void)
{
    init();
    size_t stack_var;
    printf("gift: %p \n", (char *)&stack_var);
    while(a) {
        menu();
        switch(read_num()) {
        case 1:
            create();
            break;
        case 2:
            create2();
            break;
        case 3:
            get();
            break;
        case 4:
            set();
            break;
        case 5:
            delete();
            break;
        case 6:
            a=0;
            break;
        }
    }

    return 0;
}
