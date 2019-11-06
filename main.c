/* Laboratory 1 - Advance Programming /
/* Compiler: gcc */

#include "advancePolynomialArithmetics.h"
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  char input;
  int n;

  do {
    printf("\n#################### Menu ####################");
    printf("\n1. Add and Subtract");
    printf("\n2. Multiply");
    printf("\n0. Exit");
    printf("\nChoose an option: ");
    scanf("\n%c", &input);
    if (input == '0') {
      return 0; // Program will be terminated if 0 is pressed
    }
    switch (input) {
    case '1':
      if (input == '1') {
        printf("Enter the degree of the polynomial to generate: ");
        scanf("%d", &n);

        struct Polynomial *polynomial = generatePolynomial(n);
        printf("\n##############################################");
        printf("\nGenerated polynomial:\n");
        printPolynomial(polynomial);

        struct Polynomial *copyPoly = copyPolynomial(polynomial);
        printf("\nPolynomial copy:\n");
        printPolynomial(copyPoly);

        printf("\nSubstrahend:\n");
        struct Polynomial *subtrahend = copyPolynomial(polynomial);
        printPolynomial(subtrahend);

        printf("\nPolynomial subtraction:\n");
        struct Polynomial *difference =
            subtractPolynomials(subtrahend, polynomial);
        printPolynomial(difference);

        printf("\nPolynomial sum:\n");
        struct Polynomial *sum = addPolynomials(polynomial, copyPoly);
        printPolynomial(sum);

        freePolynomial(sum);
        freePolynomial(subtrahend);
      }
      break;

    case '2':
      if (input == '2') {
        do {
          printf("\n##############################################");
          printf("\n1. Brute Force");
          printf("\n2. Decrease and Conquer");
          printf("\n3. Divide and Conquer");
          printf("\n4. Karatsuba");
          printf("\n5. The last three at once");
          printf("\n0. Back");
          printf("\n\nThose that use the Divide and Conquer method \nonly work "
                 "for polynomials of degree 2^k -1.");
          printf("\nChoose an option: ");
          scanf("\n%c", &input);
          if (input == '0') {
            break;
          }
          switch (input) { // Nested switch.
          case '1':
            if (input == '1') {
              printf("Enter the degree of the polynomial to generate: ");
              scanf("%d", &n);

              struct Polynomial *polynomial = generatePolynomial(n);
              printf("\n##############################################");
              printf("\nGenerated polynomial:\n");
              printPolynomial(polynomial);

              struct Polynomial *copyPoly = copyPolynomial(polynomial);
              printf("\nPolynomial copy:\n");
              printPolynomial(copyPoly);

              double time_spent = 0.0;

              clock_t begin = clock();

              printf("\nPolynomial product Brute force:\n");
              struct Polynomial *product =
                  multiplyPolynomials(polynomial, copyPoly);
              printPolynomial(product);

              clock_t end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              freePolynomial(product);
              freePolynomial(polynomial);
              freePolynomial(copyPoly);
            }
            break;
          case '2':
            if (input == '2') {
              printf("Enter the degree of the polynomial to generate: ");
              scanf("%d", &n);

              struct Polynomial *polynomial = generatePolynomial(n);
              printf("\n##############################################");
              printf("\nGenerated polynomial:\n");
              printPolynomial(polynomial);

              struct Polynomial *copyPoly = copyPolynomial(polynomial);
              printf("\nPolynomial copy:\n");
              printPolynomial(copyPoly);

              double time_spent = 0.0;

              clock_t begin = clock();

              printf("\nPolynomial product Decrease and conquer:\n");
              struct Polynomial *productDecrease =
                  decreaseAndConquer(polynomial, copyPoly);
              printPolynomial(productDecrease);

              clock_t end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              freePolynomial(productDecrease);
              freePolynomial(polynomial);
              freePolynomial(copyPoly);
            }
            break;
          case '3':
            if (input == '3') {
              printf("Enter the degree of the polynomial to generate: ");
              scanf("%d", &n);

              struct Polynomial *polynomial = generatePolynomial(n);
              printf("\n##############################################");
              printf("\nGenerated polynomial:\n");
              printPolynomial(polynomial);

              struct Polynomial *copyPoly = copyPolynomial(polynomial);
              printf("\nPolynomial copy:\n");
              printPolynomial(copyPoly);

              double time_spent = 0.0;

              clock_t begin = clock();

              printf("\nPolynomial product Divide:\n");
              struct Polynomial *product =
                  divideAndConquer(polynomial, copyPoly);
              printPolynomial(product);

              clock_t end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              freePolynomial(product);
              freePolynomial(polynomial);
              freePolynomial(copyPoly);
            }
            break;

          case '4':
            if (input == '4') {
              printf("Enter the degree of the polynomial to generate: ");
              scanf("%d", &n);

              struct Polynomial *polynomial = generatePolynomial(n);
              printf("\n##############################################");
              printf("\nGenerated polynomial:\n");
              printPolynomial(polynomial);

              struct Polynomial *copyPoly = copyPolynomial(polynomial);
              printf("\nPolynomial copy:\n");
              printPolynomial(copyPoly);

              double time_spent = 0.0;

              clock_t begin = clock();

              printf("\nPolynomial product karatsuba:\n");
              struct Polynomial *product = karatsuba(polynomial, copyPoly);
              printPolynomial(product);

              clock_t end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              freePolynomial(product);
              freePolynomial(polynomial);
              freePolynomial(copyPoly);
            }
            break;

          case '5':
            if (input == '5') {
              printf("Enter the degree of the polynomial to generate: ");
              scanf("%d", &n);

              struct Polynomial *polynomial = generatePolynomial(n);
              printf("\n##############################################");
              printf("\nGenerated polynomial:\n");
              printPolynomial(polynomial);

              struct Polynomial *copyPoly = copyPolynomial(polynomial);
              printf("\nPolynomial copy:\n");
              printPolynomial(copyPoly);

              double time_spent = 0.0;

              clock_t begin = clock();

              printf("\nPolynomial product Decrease and Conquer:\n");
              struct Polynomial *productDecrease =
                  decreaseAndConquer(polynomial, copyPoly);
              printPolynomial(productDecrease);

              clock_t end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              time_spent = 0.0;

              begin = clock();

              printf("\nPolynomial product Divide and Conquer:\n");
              struct Polynomial *product =
                  divideAndConquer(polynomial, copyPoly);
              printPolynomial(product);

              end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              time_spent = 0.0;

              begin = clock();

              printf("\nPolynomial product karatsuba:\n");
              struct Polynomial *product_karatsuba =
                  karatsuba(polynomial, copyPoly);
              printPolynomial(product);

              end = clock();
              time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
              printf("time elapsed is %f seconds", time_spent);

              freePolynomial(productDecrease);
              freePolynomial(product);
              freePolynomial(product_karatsuba);
              freePolynomial(polynomial);
              freePolynomial(copyPoly);
            }
            break;

          default:
            printf("\n############### Invalid option ###############\n");
            break;
          }
        } while (true);
      }
      break;

    default:
      printf("\n############### Invalid option ###############\n");
      break;
    }
  } while (true);

  return 0;
}
