#include <stdio.h>
#include <stdlib.h>

// LL_Bi_Error_Look_Up_Table will also have POINTER_NOT_FOUND_ERROR = 2

// Unidirectional Linked Lists

typedef struct 
{
    int value;
    struct LL_Uni* nxtelm;

} LL_Uni;

// Defining Working Functions

LL_Uni* LL_Uni_Initialize_Elm(int Initializer,  LL_Uni* restrict Empty_Pre_Made)
{
    /*
    Even Though we will always use "(LL_Uni*) malloc(sizeof(LL_Uni))"
    for 2nd argument, we purposefully add the 2nd argument
    so that we can tell the compiler that we are restricting it-
    for this function and thus no duplication will occur locally,
    thus increasing performance
    */

    if(Empty_Pre_Made != NULL)
    {
    Empty_Pre_Made->value = Initializer;
    Empty_Pre_Made->nxtelm = NULL;
    return Empty_Pre_Made;
    }
    return NULL;
}

LL_Uni* LL_Uni_Maker()
{
    /*
    Later add (int To_Take_From_Array) i.e. the input array.
    And thus instead of printf() and scanf()
    it will take input from an array and thus run the loop
    sizeof(To_Take_From_Array)/sizeof(To_Take_From_Array[0]) times
    */

    int initial_size, iternum = 1;
    printf("Enter Total Number Of Elements: "); scanf("%i",&initial_size); 

    LL_Uni* First_elm = (LL_Uni*) malloc(sizeof(LL_Uni));

    if (First_elm == NULL)
    {
        perror("Memory allocation failed for first element");
        exit(139);
    }

    
    int elm; printf("Enter Element %d: ",iternum); scanf("%i",&elm);

    LL_Uni_Initialize_Elm(elm, First_elm); iternum++;

    LL_Uni* temp_bfr = NULL;

    while(!(iternum>initial_size))
    {
        printf("Enter Element %d: ",iternum); scanf("%i",&elm);

        temp_bfr = (LL_Uni*) malloc(sizeof(LL_Uni));

        if (temp_bfr == NULL)
        {
            perror("Memory allocation failed for temporary element");
            exit(139);
        }

        LL_Uni_Initialize_Elm(elm,temp_bfr);
        LL_Uni_Linker(First_elm, temp_bfr);
        iternum++;
    }
    
    return First_elm;
}

void LL_Uni_Printer(LL_Uni* restrict To_Print)
{
    // make this long int if it is to be used in large systems
    int single_time_free_pass = 1; // So as if only single element, it still will get printed
    printf("\n The Following Link List Exists->\n");
    while((To_Print->nxtelm != NULL) || (single_time_free_pass == 1));
    {
        printf("\nElement Number %d:",single_time_free_pass);
        printf("\nValue = %d", To_Print->value);
        printf("\nAddress Of Next Element = %d", (To_Print->nxtelm));
        single_time_free_pass++;
    }
}

void LL_Uni_Linker(LL_Uni* restrict First_Item, LL_Uni* restrict Elem_To_Add) // Adds an Element to the end
{
    if(First_Item != NULL && Elem_To_Add != NULL)
    {
    LL_Uni* Last_Item = First_Item;
    
    while(Last_Item->nxtelm != NULL)
    {
        Last_Item = Last_Item->nxtelm;
    }

    Last_Item->nxtelm = Elem_To_Add;
    }
}

// These functions below will always return the pointers to the Things to add/look for
// so as that wrappers can check if the task is done succesfully by comparing

LL_Uni* LL_Uni_List_Free(LL_Uni* restrict First_Item) // Frees the full memmory allocated to the list except the first, as the first is done by the wrapper
{
    LL_Uni* current = First_Item->nxtelm;
    LL_Uni* next;

    while (current != NULL)
    {
        next = current->nxtelm;
        free(current);
        current = next;
    }

    return First_Item;
}

// Definig Wrapper Functions to check data validity

typedef LL_Uni* (*func_1_LL_Uni_Args)(LL_Uni*);

void LL_Uni_Fully_Free_Wrap(func_1_LL_Uni_Args func, LL_Uni* restrict first_arg)
{
    first_arg = func(first_arg);
    if(first_arg->nxtelm != NULL)
    {
        perror("Memory deallocation failed");
        exit(139);
    }

    free(first_arg);
}
