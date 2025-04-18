#include <stdio.h>
#include <string.h>
#include <time.h>

static int customer_id_counter = 1000;
static int billing_counter = 1;

int generateCustomerID()
{
    return customer_id_counter++;
}

int generateBillingCode()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int billing_code = tm.tm_year + 1900;
    billing_code = billing_code*100 + (tm.tm_mon + 1);
    billing_code = billing_code*100 + tm.tm_mday;
    billing_code = billing_code*1000 + billing_counter++;
    
    return billing_code; 
}

typedef struct {
    char name[50];
    float price;
    char unit[10];
    int quantity;
} Item;

int main()
{
    char name[100];
    long long phone_number; 
    int customer_id, billing_code;
    
    Item groceries[] = {
        {"Sugar", 40.00, "kg", 0},
        {"Tea", 80.00, "kg", 0},
        {"Rice", 105.00, "kg", 0},
        {"Edible Oil", 108.00, "l", 0},
        {"Wheat Flour", 72.00, "kg", 0}
    };
    int num_groceries = 5;
    
    Item beverages[] = {
        {"Sprite", 50.00, "l", 0},
        {"Coke", 60.00, "l", 0},
        {"Fruit Juice", 70.00, "l", 0},
        {"Fanta", 55.00, "l", 0}
    };
    int num_beverages = 4;
    
    Item snacks[] = {
        {"Noodles", 20.00, "pack", 0},
        {"Pasta", 25.00, "pack", 0},
        {"Chips", 15.00, "pack", 0},
        {"Cookies", 30.00, "pack", 0}
    };
    int num_snacks = 4;

    printf("-------------------\n");
    printf("Billing System\n");
    printf("-------------------\n");
    printf("Customer Details\n");

    printf("Customer Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    do {
        printf("Customer Phone Number: ");
        scanf("%lld", &phone_number);
        
        if (phone_number < 1000000000 || phone_number > 9999999999) {
            printf("Invalid phone number. Please enter a 10-digit number.\n");
        }
    } while (phone_number < 1000000000 || phone_number > 9999999999);

    customer_id = generateCustomerID();
    billing_code = generateBillingCode();

    printf("\nCustomer Registered: \n");
    printf("Name: %s\nPhone_Number: %lld\nCustomer ID: %d\nBilling Code: %d\n", name, phone_number, customer_id, billing_code);
    printf("-------------------\n");

    int choice = 0;
    int groceries_total = 0, beverages_total = 0, snacks_total = 0, total_bill = 0;
    
    printf("Groceries: \n\n");
    printf("0. Skip to next category\n");
    for (int i = 0; i < num_groceries; i++) {
        printf("%d. %s (1 %s) - Rs. %.2f\n", i+1, groceries[i].name, groceries[i].unit, groceries[i].price);
    }
    
    do {
        printf("\nSelect grocery item (0 to finish): ");
        scanf("%d", &choice);
        
        if (choice > 0 && choice <= num_groceries) {
            printf("Enter quantity for %s: ", groceries[choice-1].name);
            scanf("%d", &groceries[choice-1].quantity);
        }
    } while (choice != 0);
    
    printf("\n-------------------\n");
    printf("Beverages: \n\n");
    printf("0. Skip to next category\n");
    for (int i = 0; i < num_beverages; i++) {
        printf("%d. %s (1 %s) - Rs. %.2f\n", i+1, beverages[i].name, beverages[i].unit, beverages[i].price);
    }
    
    do {
        printf("\nSelect beverage item (0 to finish): ");
        scanf("%d", &choice);
        
        if (choice > 0 && choice <= num_beverages) {
            printf("Enter quantity for %s: ", beverages[choice-1].name);
            scanf("%d", &beverages[choice-1].quantity);
        }
    } while (choice != 0);
    
    printf("\n-------------------\n");
    printf("Snacks: \n\n");
    printf("0. Skip to next category\n");
    for (int i = 0; i < num_snacks; i++) {
        printf("%d. %s (1 %s) - Rs. %.2f\n", i+1, snacks[i].name, snacks[i].unit, snacks[i].price);
    }
    
    do {
        printf("\nSelect snack item (0 to finish): ");
        scanf("%d", &choice);
        
        if (choice > 0 && choice <= num_snacks) {
            printf("Enter quantity for %s: ", snacks[choice-1].name);
            scanf("%d", &snacks[choice-1].quantity);
        }
    } while (choice != 0);
    
    printf("\n-------------------\n");
    
    printf("Grocery Items:\n");
    for (int i = 0; i < num_groceries; i++) {
        if (groceries[i].quantity > 0) {
            int item_cost = groceries[i].quantity * groceries[i].price;
            printf("%s: Rs. %d\n", groceries[i].name, item_cost);
            groceries_total += item_cost;
        }
    }
    printf("-    -    -    -\n");
    printf("Total Groceries Amount: Rs. %d\n", groceries_total);
    printf("-------------------\n");
    
    printf("Beverage Items:\n");
    for (int i = 0; i < num_beverages; i++) {
        if (beverages[i].quantity > 0) {
            int item_cost = beverages[i].quantity * beverages[i].price;
            printf("%s: Rs. %d\n", beverages[i].name, item_cost);
            beverages_total += item_cost;
        }
    }
    printf("-    -    -    -\n");
    printf("Total Beverages Amount: Rs. %d\n", beverages_total);
    printf("-------------------\n");
    
    printf("Snack Items:\n");
    for (int i = 0; i < num_snacks; i++) {
        if (snacks[i].quantity > 0) {
            int item_cost = snacks[i].quantity * snacks[i].price;
            printf("%s: Rs. %d\n", snacks[i].name, item_cost);
            snacks_total += item_cost;
        }
    }
    printf("-    -    -    -\n");
    printf("Total Snacks Amount: Rs. %d\n", snacks_total);
    printf("-------------------\n");
    
    total_bill = groceries_total + beverages_total + snacks_total;
    printf("Total Bill Amount: Rs. %d\n", total_bill);
    printf("-------------------\n");
    
    float discount_percentage = 0.0;
    float discount_amount = 0.0;
    float final_amount = 0.0;
    
    printf("Enter discount percentage: ");
    scanf("%f", &discount_percentage);
    
    if (discount_percentage < 0) discount_percentage = 0;
    if (discount_percentage > 100) discount_percentage = 100;
    
    discount_amount = total_bill * (discount_percentage / 100.0);
    final_amount = total_bill - discount_amount;
    
    printf("-------------------\n");
    printf("Discount applied: %.2f%%\n", discount_percentage);
    printf("Discount amount: Rs. %.2f\n", discount_amount);
    printf("-    -    -    -\n");
    printf("Final Billing Amount: Rs. %.2f\n", final_amount);
    printf("-------------------\n");
    
    printf("--------------------------------------------------\n");
    printf("                     *******                 \n");
    printf("                       K.U.                     \n");
    printf("                   SUPER MARKET                     \n");
    printf("                *****************                 \n");
    
    printf("Customer Name: %s\n", name);   
    printf("Customer Phone Number: %lld\n", phone_number);
    printf("Customer ID: %d\n", customer_id);
    printf("Billing Code: %d\n", billing_code);
    
    printf("+--------------------+---------------+------------+---------------+\n");
    printf("| %-18s | %-13s | %-10s | %-13s |\n", "Product Name", "Price/Unit", "Quantity", "Total Cost");
    printf("+--------------------+---------------+------------+---------------+\n");
    
    for (int i = 0; i < num_groceries; i++) {
        if (groceries[i].quantity > 0) {
            printf("| %-18s | Rs. %-9.2f | %-10d | Rs. %-9.2f |\n", 
                groceries[i].name, groceries[i].price, groceries[i].quantity,
                groceries[i].quantity * groceries[i].price);
        }
    }
    
    for (int i = 0; i < num_beverages; i++) {
        if (beverages[i].quantity > 0) {
            printf("| %-18s | Rs. %-9.2f | %-10d | Rs. %-9.2f |\n", 
                beverages[i].name, beverages[i].price, beverages[i].quantity,
                beverages[i].quantity * beverages[i].price);
        }
    }
    
    for (int i = 0; i < num_snacks; i++) {
        if (snacks[i].quantity > 0) {
            printf("| %-18s | Rs. %-9.2f | %-10d | Rs. %-9.2f |\n", 
                snacks[i].name, snacks[i].price, snacks[i].quantity,
                snacks[i].quantity * snacks[i].price);
        }
    }
    
    printf("+--------------------+---------------+------------+---------------+\n");
    
    printf("Groceries Total Amount: Rs. %d\n", groceries_total);
    printf("Beverages Total Amount: Rs. %d\n", beverages_total);
    printf("Snacks Total Amount: Rs. %d\n\n", snacks_total);
    
    printf("Total Bill Amount: Rs. %d\n", total_bill);

    printf("Discount (%.2f%%): Rs. %.2f\n", discount_percentage, discount_amount);
    printf("-    -    -    -    -\n");
    printf("Final Bill Amount: Rs. %.2f\n", final_amount);
    printf("*  -  *  -  *  -  *  -  *\n");
    
    printf("Thank you for shopping with us!\n");
    printf("Do Visit Again\n");
    printf("--------------------------------------------------\n");
    
    return 0;
}
