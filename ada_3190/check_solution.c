#include <stdio.h>
int main() {
  char c;
  int x = 0, y = 0;
  printf("please enter starting coordinates (x y)\n");
  scanf("%d %d", &x, &y);
  printf("press ctrl-d after input directions (N, S, E, W)\n");
  while ((c = getchar()) != EOF) {
    switch(c) {
      case 'N': y++; break;
      case 'S': y--; break;
      case 'E': x++; break;
      case 'W': x--; break;
      default: break;
    }
  }
  printf("\nthe end coordinates are: (%d, %d)\n", x, y);
  return 0;
}