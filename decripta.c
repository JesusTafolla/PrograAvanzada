/*----------------------------------------------------------------

* Programación avanzada: Manejo de archivos

* Fecha: 4 - Mar - 2022

* Autor:

* A01703178 Jesus Roberto Tafolla Aranda

*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define END 240

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;

int main(int argc, char* argv[]) {

int source, destination;
ulong source_size,source_size_packets;
uchar *txt_data;
uint i,j;

if (argc != 3) {
      fprintf(stderr, "usage: %s origen destination\n", argv[0]);
      return -1;
  }

  if ( (source = open(argv[1], O_RDONLY)) < 0 ) {
    perror(argv[0]);
    return -2;
  }

    source_size = lseek(source, 0, SEEK_END);
    lseek(source, 0, SEEK_SET);
    source_size_packets = source_size/8;

    txt_data = (uchar*) malloc(sizeof(uchar) * source_size);
    if (txt_data == NULL) {
  	  printf("%s: No memory space for TXT\n", argv[0]);
  	return -3;
  }

  read(source, txt_data, sizeof(uchar) * source_size);

  for (i = 0; i < source_size; i++) {
  	//for (j=0; j<7 ;j++){
      txt_data[i] = ~txt_data[i];
    //}
  }
  
  write(destination, txt_data, sizeof(uchar) *source_size);

  free(txt_data);
  close(source);
  close(destination);

return 0;
}