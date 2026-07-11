#include <stdio.h>
#include <stdlib.h>


int count_lines(char* content) {
  return 0;
}

int compress_lined(char* file_path) {
  return 0;
}

int concatenate_files(char **file_paths) {
  return 0;
}

char* get_file_content(char* file_path) {
  FILE *fptr = fopen(file_path, "rb");
  if (fptr == NULL) {
    printf("Unable to open file!\n");
    return NULL;
  }

  fseek(fptr, 0, SEEK_END);
  long fsize = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  char *content = malloc(fsize + 1);
  if (content == NULL) {
    printf("Memory allocation failed!\n");
    fclose(fptr);
    return NULL;
  }

  size_t bytes_read = fread(content, 1, fsize, fptr);
  content[bytes_read] = '\0';

  fclose(fptr);
  return content;
}

void print_content(char* content) {
  if (content != NULL) {
    printf("%s", content);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("ERROR: File path was not provided\n");
    return 1;
  }

  char* path = argv[1];
  char* content = get_file_content(path);
  if (content != NULL) {
    print_content(content);
    free(content);
  }
  return 0;
}
