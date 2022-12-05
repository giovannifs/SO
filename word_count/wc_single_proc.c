#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

size_t wc(const char *content) {
  size_t count = 0;

  for (bool inword = false; *content; ++content) {
    if (isspace(*content)) {
      if (inword) {
        inword = false;
      }
    } else {
      if (!inword) {
        inword = true;
        ++count;
      }
    }
  }
  return count;
}

size_t wc_file(const char *filename) {
  char *file_content = 0;
  long length;

  FILE *f = fopen(filename, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    // put the whole file into the memory (beware)
    file_content = malloc(length);
    if (file_content) {
      fread(file_content, 1, length, f);
    }
    fclose(f);

    // count word from this buffer
    return wc(file_content);
  }

  return -1;
}

// count words in file within dir_path
// we do not walk in subdirs
size_t wc_dir(const char *dir_path) {

  DIR *dir;
  struct dirent *ent;
  char filepath[1024]; // unsafe

  size_t count = 0;

  dir = opendir(dir_path);
  if (dir) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // if it is regular file
        sprintf(filepath, "%s/%s", dir_path, ent->d_name);
        count += wc_file(filepath);
      }
    }
  }
  closedir(dir);
  return count;
}

// it calculates the number of words in files
// stored under directory argv[1]
//
// we assume a depth 3 hierarchy.
// At level 1, we have the root
// at level 2, we have subdirs
// at level 3, we have files
//
// root--
//       |-- subdir-1
//       |-- subdir-2
//       |-- ...
//       |-- subdir-3
//
int main(int argc, char *argv[argc + 1]) {

  DIR *root_dir;
  struct dirent *ent;
  char filepath[1024]; // unsafe
  char *root_path = argv[1];

  size_t count = 0;

  root_dir = opendir(root_path);

  if (root_dir) {
    while ((ent = readdir(root_dir)) != NULL) {
      if (ent->d_type == DT_DIR) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          sprintf(filepath, "%s/%s", root_path, ent->d_name);
          // sums the subdir total
          count += wc_dir(filepath);
        }
      }
    }
    closedir(root_dir);
  }

  printf("%zu\n", count);
  return EXIT_SUCCESS;
}
