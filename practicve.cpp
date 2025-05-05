#include <stdio.h>
#include <string.h>

#define MAX 100 

// Arrays to store car info
char carBrand[MAX][50];
char carModel[MAX][50];
int carYear[MAX];
float carPrice[MAX];
int carCount = 0;

// Function declarations
void showWelcome();
int login();
void adminMenu();
void addCar();
void viewCars();

int main() {
int userType;

showWelcome();
userType = login();

if (userType == 1) {
    adminMenu(); // go to admin panel
} else if (userType == 2) {
    printf("\n Welcome, Buyer!\n");
    // buyerMenu(); // (we’ll build this later)
} else {
    printf("\n Login failed.\n");
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
printf("Password  : ");
scanf("%s", password);

if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
    return 1;
} else if (strcmp(username, "buyer") == 0 && strcmp(password, "buyer123") == 0) {
    return 2;
} else {
    return 0;
}
}

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
        viewCars();
    } else if (choice == 3) {
        printf("Exiting Admin Menu...\n");
        break;
    } else {
        printf("Invalid choice. Try again.\n");
    }
}
}

void addCar() {
if (carCount >= MAX) {
printf("  Cannot add more cars. Limit reached.\n");
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

printf("  Car added successfully!\n");
carCount++;
}

void viewCars() {
if (carCount == 0) {
printf("No cars added yet. \n");
return;
}


printf("\n--- All Cars ---\n");
for (int i = 0; i < carCount; i++) {
    printf("Car %d:\n", i + 1);
    printf("Brand: %s\n", carBrand[i]);
    printf("Model: %s\n", carModel[i]);
    printf("Year: %d\n", carYear[i]);
    printf("Price: %.2f\n", carPrice[i]);
    printf("-------------------------\n");
}
}
