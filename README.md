# GualMart Inventory and Shopping System
## Overview
This C program simulates a basic shopping system called "GualMart" that manages inventory, allows customers to purchase items, and provides them with a receipt. The program generates a random inventory of items and quantities, handles customer purchases, calculates totals including taxes and discounts, and prints a receipt at the end of the transaction.

## Features
### 1. Inventory Generation
Generates a random number of items in stock.\
Each item has a unique code, a name, a price, and a random quantity between 0 and 50.
### 2. Shopping Process:
Users can view the inventory, select items to purchase, and specify quantities.\
The system checks stock availability and handles cases where the requested quantity exceeds the available stock.

### 3. Discounts:
The program checks if the customer is a student, military member, or both.\
A 10% discount is applied for either category, with an additional 5% discount if the customer qualifies for both.

### 4. Total Calculation:
Adds an 8.25% sales tax to the total.\
Applies discounts for eligible customers.

### 5. Receipt:
Displays the purchased items, their prices, and the total after taxes and discounts.\
Provides a friendly message at the end.

## Usage Instructions
### 1. User Interaction:
The program prompts the user to decide whether to view the inventory.\
The user selects items to buy by their index number and specifies the quantity.\
If the user wants to continue shopping, they can select more items.\
At the end of the shopping session, the program prints a receipt with the total and applies discounts if applicable.

### 2. Prompts and Inputs:
The user is asked if they are a student or military member to apply potential discounts.\
After shopping, the receipt is displayed with the total cost, including taxes and discounts.

## Code Explanation
### Key Functions:
inventoryMaker(): Generates the inventory with random quantities and item codes.\
printInventory(): Displays the available items, their codes, prices, and quantities.\
shopping(): Handles the customer’s shopping process, including item selection and quantity specification.\
checkStock(): Checks if the requested quantity is available in stock.\
calcTotal(): Calculates the total cost with taxes and discounts.\
discount(): Applies discounts based on military or student status.\
printReceipt(): Prints the final receipt with a breakdown of items bought and the total cost.\
**Additional Utility Functions:**\
randRange(): Generates a random double between a given range.\
isMilitary(): Asks if the customer is in the military to apply discounts.\
isStudent(): Asks if the customer is a student to apply discounts.

## How to Modify:
Item List: The items array in the main() function can be modified to include new products.\
Discount Rules: Modify the discount() function to change the discount percentages.\
Inventory Size: Adjust the size variable in main() to add or remove items from the inventory