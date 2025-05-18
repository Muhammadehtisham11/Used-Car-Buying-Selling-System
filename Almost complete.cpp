#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // This library For isdigit 

#define MAX 100
#define DATA_FILE "car_data.txt"
#define BUYER_FILE "buyers.txt"

// Car structure 
typedef struct {
    char brand[50];
    char model[50];
    int year;
    float price;
    int isSold;
} Car;

// Buyer structure
typedef struct {
    char username[30];
    char password[30];
} Buyer;

Car cars[MAX];
Buyer buyers[MAX];
int carCount = 0;
int buyerCount = 0;

// Function declaration

void stylePattern1();
void showWelcome();
void stylePattern2();
int login();
void adminMenu();
void buyerMenu();
void addCar();
void viewCarsAdmin();
void viewAvailableCars();
void buyCar();
void saveCarsToFile();
void loadCarsFromFile();
void searchCar();
void sortCarsByPrice();
void showSoldCars();
void registerBuyer();
int buyerLogin(char *username, char *password);
void loadBuyersFromFile();
void saveBuyersToFile();
void clearInputBuffer();
int getIntInput(const char *prompt, int min, int max);
float getFloatInput(const char *prompt, float min);

int main() 
{
	
    stylePattern1();
	showWelcome();
	stylePattern2();
    loadCarsFromFile();
    loadBuyersFromFile();

    int userType = login();

    if (userType == 1) {
        adminMenu();
    } 
	else if (userType == 2) {
        buyerMenu();
    } 
	else {
        printf("\nLogin failed.\n");
    }

    saveCarsToFile();
    saveBuyersToFile();
    return 0;
}
void stylePattern1(){
	for (int i=15;i>=1;i--){
		for(int space=1;space<=15-i;space++){
			printf(" ");
	} 
	for (int j=1;j<=i;j++){
		printf("*  ");
	}
	printf("\n");
}
}

void showWelcome() 
{
    printf("\n====================================\n");
    printf("   USED CAR BUYING & SELLING SYSTEM\n");
    printf("====================================\n");
}
void stylePattern2(){
	for (int i=1;i<=15;i++){
		for(int space=1;space<=15-i;space++){
		 printf(" ");
	}
	for (int j=1;j<=i;j++){
		printf("*  ");
	}

		printf("\n");
	}
}


int login() {
    char username[30], password[30];

    printf("\nLogin\n------\n");
    printf("Username: ");
    scanf("%s",& username);
    printf("Password: ");
    scanf("%s", &password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1; // It will return admin menu
    } 
	else if (buyerLogin(username, password)) {
        return 2; // It will return Buyer menu
    }
    return 0; // if the above conditions false
}

void adminMenu() {
    int choice;
    do {
    	printf("\n====Wellcome to Admin Menu====\n");
        printf("\n===== Admin Menu =====\n");
        printf("1. Add Car\n");
        printf("2. View All Cars\n");
        printf("3. View Sold Cars\n");
        printf("4. Search Cars\n");
        printf("5. Sort Cars by Price\n");
        printf("6. Exit\n");
        choice = getIntInput("Enter choice: ", 1, 6);

        switch (choice) {
            case 1: addCar(); 
			break;
            case 2: viewCarsAdmin(); 
			break;
            case 3: showSoldCars(); 
			break;
            case 4: searchCar(); 
			break;
            case 5: sortCarsByPrice(); 
			break;
            case 6: printf("Exiting...\n"); 
			break;
        }
    } while (choice != 6);
}

void buyerMenu() {
    int choice;
    do {
    	printf("\n====Wellcome to Buyer Menu====\n");
        printf("\n===== Buyer Menu =====\n");
        printf("1. View Available Cars\n");
        printf("2. Buy a Car\n");
        printf("3. Search Car\n");
        printf("4. Register New Buyer\n");
        printf("5. Exit\n");
        choice = getIntInput("Enter choice: ", 1, 5);

        switch (choice) {
            case 1: viewAvailableCars(); 
			break;
            case 2: buyCar(); 
			break;
            case 3: searchCar(); 
			break;
            case 4: registerBuyer();
			 break;
            case 5: printf("Exiting...\n");
			 break;
        }
    } while (choice != 5);
}

void addCar() {
    if (carCount >= MAX) {
        printf("\nError: You Have reached limit ofMaximum cars!\n");
        return;
    }

    printf("\nEnter Car Details:\n");
    printf("Brand: ");
    scanf("%49s", cars[carCount].brand);
    printf("Model: ");
    scanf("%49s", cars[carCount].model);
    cars[carCount].year = getIntInput("Year (1900-2025): ", 1900, 2025);
    cars[carCount].price = getFloatInput("Price (Rs): ", 0);
    cars[carCount].isSold = 0;

    carCount++;
    printf("\nAdded successfully! Good Luck\n");
}

void viewCarsAdmin() {
    if (carCount == 0) {
        printf("\nNo cars in inventory.\n");
        return;
    }

    printf("\n%-5s %-15s %-15s %-8s %-10s %s\n", 
           "ID", "Brand", "Model", "Year", "Price", "Status");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < carCount; i++) {
        printf("%-5d %-15s %-15s %-8d Rs%-9.2f %s\n", 
               i + 1, cars[i].brand, cars[i].model, cars[i].year, 
               cars[i].price, cars[i].isSold ? "Sold" : "Available");
    }
}

void viewAvailableCars() {
    int found = 0;
    printf("\nAvailable Cars:\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < carCount; i++) {
        if (!cars[i].isSold) {
            printf("ID: %d | %s %s (%d) | Rs%.2f\n", 
                   i + 1, cars[i].brand, cars[i].model, 
                   cars[i].year, cars[i].price);
            found = 1;
        }
    }
    if (!found) printf("No cars available.\n");
}

void buyCar() {
    viewAvailableCars();
    if (carCount == 0) return;

    int id = getIntInput("\nEnter Car ID to buy (0 to cancel): ", 0, carCount);
    if (id == 0) return;

    if (cars[id - 1].isSold) {
        printf("\nError: Car already sold!\n");
        return;
    }

    char confirm;
    printf("Confirm purchase of %s %s (Y/N)? ", cars[id - 1].brand, cars[id - 1].model);
    scanf(" %c", &confirm);

    if (toupper(confirm) == 'Y') {
        cars[id - 1].isSold = 1;
        printf("\nPurchase successful! Thank you.\n");
    } else {
        printf("\nPurchase cancelled.\n");
    }
}

void saveCarsToFile() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("\nError: Cannot save car data!\n");
        return;
    }

    for (int i = 0; i < carCount; i++) {
        fprintf(fp, "%s %s %d %.2f %d\n", 
                cars[i].brand, cars[i].model, cars[i].year, 
                cars[i].price, cars[i].isSold);
    }
    fclose(fp);
}

void loadCarsFromFile() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) return;

    while (fscanf(fp, "%s %s %d %f %d", 
                 cars[carCount].brand, cars[carCount].model, 
                 &cars[carCount].year, &cars[carCount].price, 
                 &cars[carCount].isSold) == 5) {
        carCount++;
    }
    fclose(fp);
}

void searchCar() {
    char query[50];
    printf("\nEnter search term (brand/model): ");
    scanf("%49s", query);

    int found = 0;
    for (int i = 0; i < carCount; i++) {
        if (strstr(cars[i].brand, query) || strstr(cars[i].model, query)) {
            printf("\nID: %d | %s %s (%d) | Rs%.2f | %s\n", 
                   i + 1, cars[i].brand, cars[i].model, 
                   cars[i].year, cars[i].price, 
                   cars[i].isSold ? "Sold" : "Available");
            found = 1;
        }
    }
    if (!found) printf("\nNo matching cars found.\n");
}

void sortCarsByPrice() {
    for (int i = 0; i < carCount - 1; i++) {
        for (int j = 0; j < carCount - i - 1; j++) {
            if (cars[j].price > cars[j + 1].price) {
                Car temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
    printf("\nCars sorted by price (low to high).\n");
    viewCarsAdmin();
}

void showSoldCars() {
    int found = 0;
    printf("\nSold Cars:\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < carCount; i++) {
        if (cars[i].isSold) {
            printf("ID: %d | %s %s (%d) | Rs%.2f\n", 
                   i + 1, cars[i].brand, cars[i].model, 
                   cars[i].year, cars[i].price);
            found = 1;
        }
    }
    if (!found) printf("No sold cars.\n");
}

void registerBuyer() {
    if (buyerCount >= MAX) {
        printf("\nError: Buyer limit reached!\n");
        return;
    }

    char username[30];
    printf("\nRegister New Buyer\n");
    
    // Check for existing username
    int valid = 0;
    while (!valid) {
        printf("Username: ");
        scanf("%29s", username);
        valid = 1;
        
        for (int i = 0; i < buyerCount; i++) {
            if (strcmp(username, buyers[i].username) == 0) {
                printf("Error: Username already exists!\n");
                valid = 0;
                break;
            }
        }
    }

    printf("Password: ");
    scanf("%29s", buyers[buyerCount].password);
    strcpy(buyers[buyerCount].username, username);
    buyerCount++;
    printf("\nRegistration successful!\n");
}

int buyerLogin(char *username, char *password) {
    for (int i = 0; i < buyerCount; i++) {
        if (strcmp(username, buyers[i].username) == 0 && 
            strcmp(password, buyers[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loadBuyersFromFile() {
    FILE *fp = fopen(BUYER_FILE, "r");
    if (!fp) return;

    while (fscanf(fp, "%s %s", 
                 buyers[buyerCount].username, 
                 buyers[buyerCount].password) == 2) {
        buyerCount++;
    }
    fclose(fp);
}

void saveBuyersToFile() {
    FILE *fp = fopen(BUYER_FILE, "w");
    if (!fp) {
        printf("\nError: Cannot save buyer data!\n");
        return;
    }

    for (int i = 0; i < buyerCount; i++) {
        fprintf(fp, "%s %s\n", buyers[i].username, buyers[i].password);
    }
    fclose(fp);
}

       // Utility functions
void clearInputBuffer() {
    while (getchar() != '\n');
}

int getIntInput(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        if (value < min || value > max) {
            printf("Input must be between %d and %d.\n", min, max);
            continue;
        }
        return value;
    }
}

float getFloatInput(const char *prompt, float min) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        if (value < min) {
            printf("Input must be at least %.2f.\n", min);
            continue;
        }
        return value;
    }
}