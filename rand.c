#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "rand.h"

int get_rand(){
  int random = open("/dev/urandom", O_RDONLY);
  if (random < 0){
    printf("Opening /dev/urandom errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  int * number;
  int bytes = read(random, number, sizeof(number));
  if (bytes < 0){
    printf("Reading file errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  close(random);
  return number[0];
}

int main(){
  printf("-------------------------START-------------------------\n");
  printf("Generating Random Numbers:\n");
  int array[10];
  for (int i = 0; i < 10; i++){
    array[i] = get_rand();
    printf("Random Number %d: %d\n", i, array[i]);
  }

  int output = open("output.txt", O_CREAT | O_RDWR, 0644);
  if (output < 0){
    printf("Creating file errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  printf("\nWriting numbers to file...\n");
  int writing = write(output, array, sizeof(array));
  if (writing < 0){
    printf("Writing to file errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  close(output);

  printf("\nReading numbers from file...\n");
  int in[10];
  int input = open("output.txt", O_RDONLY);
  if (input < 0){
    printf("Opening file errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  int numbers = read(input, in, sizeof(in));
  if (numbers < 0){
    printf("Reading file errno: %d\nerror: %s\n",errno, strerror(errno));
    return 0;
  }
  close(input);
  printf("\nVerification that written values were the same:\n");
  for (int i = 0; i < 10; i ++){
    printf("Random Number %d: %d\n", i, in[i]);
  }
  printf("--------------------------END--------------------------\n");
  return 0;
}
