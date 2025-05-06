#include <stdio.h>
#include <string.h>

#define MAX 100 // Maximum number of cars

// Arrays to store car information
char carBrand[MAX][50];
char carModel[MAX][50];
int carYear[MAX];
float carPrice[MAX];
int isSold[MAX]; // 0 = available, 1 = sold
int carCount = 0;

// Function declarations
void showWelcome();
int login();
void adminMenu();
void buyerMenu();
void addCar();
void viewCarsAdmin();
void viewAvailableCars();
void buyCar();

int main() {
int userType;


showWelcome();
userType = login();

if (userType == 1) {
    adminMenu();  // Admin logged in
} else if (userType == 2) {
    buyerMenu();  // Buyer logged in
} else {
    printf("\n? Login failed.\n");
}

return 0;
}

void showWelcome() {
printf("====================================\n");
printf(" USED CAR BUYING & SELLING SYSTEM\n");
printf("====================================\n\n");
}

int login() {
char username[30], password[30];


printf("Login:\n");
printf("Username: ");
scanf("%s", username);
printf("Password: ");
scanf("%s", password);

if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
    return 1;  // Admin
} else if (strcmp(username, "buyer") == 0 && strcmp(password, "buyer123") == 0) {
    return 2;  // Buyer
} else {
    return 0;  // Invalid
}
}

// Admin Panel
void adminMenu() {
int choice;
while (1) {
printf("\n===== Admin Menu =====\n");
printf("1. Add Car\n");
printf("2. View All Cars\n");
printf("3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);


    if (choice == 1) {
        addCar();
    } else if (choice == 2) {
        viewCarsAdmin();
    } else if (choice == 3) {
        printf("Exiting Admin Menu...\n");
        break;
    } else {
        printf("Invalid choice. Try again.\n");
    }
}
}

// Buyer Panel
void buyerMenu() {
int choice;
while (1) {
printf("\n===== Buyer Menu =====\n");
printf("1. View Available Cars\n");
printf("2. Buy a Car\n");
printf("3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);


    if (choice == 1) {
        viewAvailableCars();
    } else if (choice == 2) {
        buyCar();
    } else if (choice == 3) {
        printf("Exiting Buyer Menu...\n");
        break;
    } else {
        printf("Invalid choice. Try again.\n");
    }
}
}

void addCar() {
if (carCount >= MAX) {
printf("? Cannot add more cars. Limit reached.\n");
return;
}

printf("\nEnter Car Brand: ");
scanf("%s", carBrand[carCount]);

printf("Enter Car Model: ");
scanf("%s", carModel[carCount]);

printf("Enter Year: ");
scanf("%d", &carYear[carCount]);

printf("Enter Price: ");
scanf("%f", &carPrice[carCount]);

isSold[carCount] = 0;  // Car is available
carCount++;

printf("? Car added successfully!\n");
}

void viewCarsAdmin() {
if (carCount == 0) {
printf("No cars added yet.\n");
return;
}

printf("\n--- All Cars ---\n");
for (int i = 0; i < carCount; i++) {
    printf("Car %d:\n", i + 1);
    printf("Brand: %s\n", carBrand[i]);
    printf("Model: %s\n", carModel[i]);
    printf("Year: %d\n", carYear[i]);
    printf("Price: %.2f\n", carPrice[i]);
    printf("Status: %s\n", isSold[i] ? "Sold" : "Available");
    printf("------------------------\n");
}
}

void viewAvailableCars() {
int found = 0;
printf("\n--- Available Cars ---\n");
for (int i = 0; i < carCount; i++) {
if (!isSold[i]) {
printf("Car ID: %d\n", i + 1);
printf("Brand: %s\n", carBrand[i]);
printf("Model: %s\n", carModel[i]);
printf("Year: %d\n", carYear[i]);
printf("Price: %.2f\n", carPrice[i]);
printf("------------------------\n");
found = 1;
}
}
if (!found) {
printf("No available cars at the moment.\n");
}
}

void buyCar() {
int id;
viewAvailableCars();


printf("Enter Car ID to Buy: ");
scanf("%d", &id);

if (id < 1 || id > carCount) {
    printf("Invalid Car ID.\n");
    return;
}

if (isSold[id - 1]) {
    printf("This car is already sold.\n");
    return;
}

isSold[id - 1] = 1;  // Mark as sold
printf("? You bought the car: %s %s (%.2f)\n",
       carBrand[id - 1],
       carModel[id - 1],
       carPrice[id - 1]);
}