#include <stdio.h>
#include <stdlib.h>
#include <quarto.h>

int
main(argc, argv)
     char **argv;
     int argc;
{
     FILE *fp;
     Game *gamep;
     char *filename, *str;
     int ret;
  
     filename = argv[1];

     fp = fopen(filename, "r");
     if ((ret = parse(fp, &gamep)) != 0) {
         printf("Cannot parse %s (err %d)\n", filename, ret);
         return ret;
     }
     fclose(fp);

     if ((ret = explain_string(gamep, &str)) != 0) {
         printf("Cannot explain %s (err %d)\n", filename, ret);
         return ret;
     }
     printf("%s\n", str);
  
     return 0;
}
