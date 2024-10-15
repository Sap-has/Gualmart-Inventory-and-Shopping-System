// libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// delcaring methods so no error happens if I call a method before its declaration
double randRange(double min, double max);
void inventoryMaker(char *items[] , int *quantity , int *code , int size);
void printInventory(double *price , int *quantity , int *codes , char *items[] , int size);

void shopping(char *items[] , int size , int *quantity , int * code, double *price);
void checkStock(int item, int bought, int *itemsBought, int *quantity, char *items[], int size);

double calcTotal(double total);
double discount(double total);
bool isMilitary();
bool isStudent();

void printReceipt(char *items[], int *itemsBought  , double *price, int size);

int main() {
    /*

        - Inventory
            - calculates # of items available
            - returns 0 if they don't exist, or we ran out
                - order more if we run out
            - user random function for inventory, to start differently and adding more items

        - Receipt
            - Calculates total plus tax
            - Asks for promo codes, gift cards, military
            - Rate your experience
                - ask for comments
                - how many stars out of 5
    */




    int size = 11;
    // Making an array of strings for all items we sell
    char *items[] = { "Apples" , "Oranges" , "TV" , "Phone" , "Tablet" , "Chair" , "Table" , "Sofa" , "Milk" , "Spices" , "Spoons" };

    // Making an array that stores quantity of items, using inventory() method
    // each index corresponds to same index in items[] array
    // also for code and price
    int inventoryQuantity[ size ];
    int inventoryCode[ size ];
    double itemsprice[]={3.25,3.50, 599.99,699.99,200.00,59.99,150.00,1050.99,1.29,2.19,14.15};

    inventoryMaker( items , inventoryQuantity , inventoryCode , size );

    // calls shopping where user buys
    shopping( items , size , inventoryQuantity , inventoryCode, itemsprice );

    return 0;
}

// Makes the inventory, gives quantity, codes and price
void inventoryMaker( char *items[] , int *quantity , int *code , int size ){
    srand( ( int )time(0)); // Unique seed, rand() is unique now
    for( int i = 0; i < size; i++ ) {
        *( quantity + i ) = rand() % 50; // each item is given a random number, number represents number items present
        *( code + i ) = ( rand() % 1000 ) + 1000; // gives each item a unique item code
    }
}

// prints out the invetory
void printInventory( double *price , int *quantity , int *codes , char *items[] , int size ) {
    printf( "\t\t\t\t***** INVENTORY ***** \n" );
    printf( "-------------------------------------------------------------------------------------------------\n" );
    printf( "S.N.|\tNAME\t\t|\tCODE\t\t|\tQUANTITY\t|\tPRICE\t\t|\n" );

    for(int i = 0; i < size; i++) {
        printf( "S.N.|\t%s\t\t|\t%d\t\t|\t%d\t\t|\t$%.2lf\t\t|\n", *( items + i ) , *( codes + i ) , *( quantity + i ) , *( price + i ));
    }

    printf( "-------------------------------------------------------------------------------------------------\n" );
}


// User telss us what they want to buy and how many
void shopping( char *items[] , int size , int *quantity , int * code, double *price ) {
    char printInv = 'N';
    char buying = 'N';

    int itemIndex = -1;
    int itemsBought[ size ]; // what items they buy


    printf( "\t\t\tHello! Welcome to GualMart! \n\nWe are pleased to be your choice to buy from today! Please let us know what you want to buy.\n" );
    printf( "We will show you our list of what you can buy,  we will provide your their name, number, price and our inventory\n" );
    printf( "You can select by using the number they are associated with\n\n" );

    printf("Do you want to print our inventory? (Y/N): "); //getting input from user 
    scanf( "%c", &printInv);
    fflush(stdin);

    if(printInv == 'Y' || printInv == 'y') { 
        printInventory( price, quantity, code, items, size ); // print the inventory of the user wanna see it 
        printf( "Do you want to buy?(Y/N) ");
        scanf( "%c", &buying );
        fflush(stdin);
    } else {
        printf("Come on! See the inventory my friend :) - (Y/N) " ); //ask the user to see the inventory 
        scanf( "%c", &printInv);
        fflush(stdin);
        if(printInv == 'Y' || printInv == 'y') printInventory( price, quantity, code, items, size );
        printf( "Do you want to buy?(Y/N) ");
        scanf( "%c", &buying );
        fflush(stdin);
    }

    for(int i = 0; i < size; i++) {
            *(itemsBought+i) = 0; // making array values to 0 because I kept getting a weired values
        }
    printf("\n");
    while(buying == 'Y' || buying == 'y') { //printing the items of the inventory
        for(int i = 0; i < size; i++) {
            printf("For '%s' select - %d\n", *(items + i), i);
        }

        printf("\nPlease select item: ");//asking an input from the user to select their item
        scanf("%d", &itemIndex);
        fflush(stdin);

        int num = 0;
        printf("How many do you want to buy of %s: ", *(items + itemIndex));//asking the quantity of the items that the user wants to buy
        scanf("%d", &num);
        fflush(stdin);
        checkStock(itemIndex, num, itemsBought, quantity, items, size);

        printf("\nDo you wish to continue? (Y/N): "); 
        scanf("%c", &buying);
        fflush(stdin);
        printf("\n");

        if (buying == 'n' || buying == 'N') { //if the user doesnt want to continue we ask the users if they want to see the inventory ans buy an item again
            printf("Do you want to print our inventory? (Y/N): ");
            scanf( "%c", &printInv);
            fflush(stdin);

            if (printInv == 'y' || printInv == 'Y') { // if yes, the programm will let the user see the inventory again and ask them if want to buy again
                printf("\n");
                printInventory( price, quantity, code, items, size ); 
                printf( "\nDo you want to buy?(Y/N) ");
                scanf( "%c", &buying );
                fflush(stdin);
            } 
        }
    }

    // prints the receipt
    printf("\n");
    printReceipt( items , itemsBought , price , size ); 
}

// check if we have any stock left for this item
// returns true if we do, else false
void checkStock(int item, int bought, int *itemsBought, int *quantity, char *items[], int size) {
    if(*(quantity+item) < bought) {
        printf("There is only %d available, you go over by %d\n", *(quantity+item), abs(*(quantity+item)-bought));
        printf("Do you wish to buy the rest of the stock(Y/N): ");
        char buyAllStock = 'N';
        scanf("%c", &buyAllStock);
        fflush(stdin);

        if(buyAllStock == 'Y' || buyAllStock == 'y') {
            *(itemsBought+item) += *(quantity+item);
            *(quantity+item) = 0;
        }
    }
    else {
        *(quantity+item) -= bought;
        *(itemsBought+item) += bought;
    }

}




// Calculates total, including taxes and any discounts
double calcTotal( double total ) {
    double tax = .0825;
    total += total * tax;
    total = discount( total );

    return total;
}

// calculates discount
double discount( double total ) {
    bool student = isStudent();
    bool military = isMilitary();

    if( student || military ) total -= total * 0.1; // 10% off, if they are either
    if( student && military ) total -= total * 0.05; // 5% off if they are both

    return total;
}

// if they are part of the military, get 10% discount
bool isMilitary() {
    char military = 'N';
    printf( "Are you part of the military? (Y/N): " );
    scanf( "%c" , &military );
    fflush( stdin );

    if( military == 'Y' || military == 'y' ) return true;
    return false;
}

// if they are a student, get 10% discount
bool isStudent() {
    char student = 'N';
    printf( "Are you a student? (Y/N): " );
    scanf( "%c" , &student );
    fflush( stdin );

    if( student == 'Y' || student == 'y' ) return true;
    return false;
}




// Mehtod to print the receipt, will show item:quantity     $price
// at end it will take discounts
// then total at end
// Rate your experience
void printReceipt( char *items[], int *itemsBought  , double *price, int size ) {

    printf("****************** RECEIPT *******************");
    printf( "\n" );

    printf( "Items:\t\tPrice:\t\tNumber Bought:\n" );

    float total = 0.0;

    for(int i = 0; i < size; i++) {
        if( *(itemsBought+i) > 0) {
            printf("%s\t\t%0.2lf\t\t%d\n", *(items+i), *(price + i), *(itemsBought+i));
            total += *(itemsBought+i) * *(price+i);
        }
    }
    for( int i = 0; i < 46; i++ ) printf( "*" );
    printf("\n");

    total = calcTotal(total);

    printf( "\n" );
    printf("Total: $%0.2lf\n", total);
    printf("\nThanks for using GualMart! GOODBYE!\n");

    for( int i = 0; i < 46; i++ ) printf( "*" );
    printf( "\n" );
}