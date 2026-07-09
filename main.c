#include <stdio.h>


char* get_file_content(char* file_path) {
  return "";
}

void print_content() {
  // Printer logic
}

int main(int argc, char* argv[]) {
  char* path = argv[1];
  if(path == NULL) {
    printf("ERROR: File path was not provided");
  }
  return 0;
}
