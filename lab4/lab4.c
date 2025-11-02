#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BLOCK_SIZE 128
#define BUF_SIZE 64
struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *msg) { write(2, msg, strlen(msg)); }
void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}
int main() {
  // 1. Increase heap size by 256
  char *initial_break = sbrk(0);
  /*printf("Initial program break: %p\n", initial_break);*/
  // Increase heap size by 256
  if (sbrk(256) == (void *)-1) {
    printf("sbrk failed");
  }

  // new break:

  /*char *new_break = sbrk(0);*/
  /*printf("New break is: %p\n", new_break);*/

  struct header *first_block = (struct header *)initial_break;
  struct header *second_block = (struct header *)(initial_break + BLOCK_SIZE);
  first_block->next = NULL;
  second_block->next = first_block;
  first_block->size = 128;
  second_block->size = 128;
  // here first_block +1 = first_block + 1*sizeof(first_block) which is the size
  // of header = 16
  char *first_payload = (char *)first_block + 1;
  char *second_payload = (char *)second_block + 1;
  /**/
  /*for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); i++) {*/
  /*  first_payload[i] = 0;*/
  /*  second_payload[i] = 1;*/
  /*}*/

  memset(first_block + 1, 0, BLOCK_SIZE - sizeof(struct header));
  memset(second_block + 1, 1, BLOCK_SIZE - sizeof(struct header));
  print_out("first block: %p\n", &first_block, sizeof(first_block));
  print_out("second block: %p\n", &second_block, sizeof(second_block));
  print_out("first block next: %p\n", &first_block->next,
            sizeof(first_block->next));
  print_out("first block size: %p\n", &first_block->size,
            sizeof(first_block->size));
  print_out("second block next: %p\n", &second_block->next,
            sizeof(second_block->next));
  print_out("second block size: %p\n", &second_block->size,
            sizeof(second_block)->size);
  for (int i = 0; i<BLOCK_SIZE - sizeof(struct header); i++){
   write(1,first_payload[i], strlen(first_payload[i]) ) ;
  }
}
