#include <stdio.h>
#include <go32.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
  int i;
  printf("%04lx : %04x %04x %04x\n",
	 _go32_info_block.linear_address_of_transfer_buffer >> 4,
	 _go32_my_cs(), _go32_my_ds(), _go32_info_block.selector_for_linear_memory);
  if (argc < 2)
    return 0;
  for (i=0; i<atoi(argv[1]); i++)
  {
    printf("[%02d] ", i);
    fflush(stdout);
    system(argv[0]);
  }
  return 0;
}
