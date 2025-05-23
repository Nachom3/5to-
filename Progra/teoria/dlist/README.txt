Compilamos primero la implementación:
-----------------
$ gcc -c dlist.c
-----------------

Si todo anduvo bien, generó un dlist.o en el directorio.

Luego, podemos compilar el archivo main.c, dándole
nombre "main" al binario (en lugar de "a.out"), y
diciendole que tiene que tomar algunas funciones
de dlist.o:
----------------------------
$ gcc -o main main.c dlist.o
----------------------------

Ejecutamos "main" para verificar que haga lo esperado. 
En linux:
$ ./main

En windows:
$ main
