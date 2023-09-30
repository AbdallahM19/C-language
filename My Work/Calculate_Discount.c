#include <stdio.h>

int main(void) {
    float originalPrice, finalPrice;
    float discount = 0.0;

    // Prompt the user to enter the original price of the product
    printf("Enter the original price of the product: ");
    scanf("%f", &originalPrice);

    // Check if the user is eligible for a discount based on the original price
    if (originalPrice >= 100) {
        discount = 0.10; // 10% discount for original price >= $100
    } else if (originalPrice >= 50) {
        discount = 0.05; // 5% discount for original price >= $50 and < $100
    }

    // Calculate the final price after applying the discount
    finalPrice = originalPrice - (originalPrice * discount);

    // Display the discount and final price
    if (discount > 0.0) {
        printf("Discount applied: %.0f%%\n", discount * 100);
    } else {
        printf("No discount applied.\n");
    }
    
    printf("Final price: $%.2f\n", finalPrice);

    return 0;
}