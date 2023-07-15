#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define MAX_SIZE 100000

void* alloc_executable_memory(size_t size);
typedef char* (*jitted)(void);

int main() {
	FILE *file;
	char* data = alloc_executable_memory(MAX_SIZE);

	file = fopen("raw.bin", "rb");
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	if (file == NULL) {
		return 1;
	}

	int i = 0;
	char c;
	
	while (i < MAX_SIZE && i < size) {
		data[i] = fgetc(file);
		printf("%hhx", data[i]);
		i++;
	}
	printf("\n");
	printf("File is %i bytes long, jitting\n", i);

	jitted function = (jitted) data;
	char* value = function();
	printf("Jitted function is %s\n", value);

	munmap(data, MAX_SIZE);
}

void* alloc_executable_memory(size_t size) {
  void* ptr = mmap(0, size,
                   PROT_READ | PROT_WRITE | PROT_EXEC,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (ptr == (void*)-1) {
    perror("mmap");
    return NULL;
  }
  return ptr;
}
