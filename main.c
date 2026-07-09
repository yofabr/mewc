#include <bits/pthreadtypes.h>
#include <stdio.h>


char* get_file_content(char* file_path) {

  FILE *fptr;

  fptr = fopen(file_path, "r");
  if(fptr == NULL) {
    printf("Unable to open file!");
    return "";
  }

  printf("fILE CONTENT: %s", fptr);
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
  get_file_content(path);
  return 0;
}
