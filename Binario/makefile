CC = gcc
CFLAGS = -Wall
LASTBUILD = .lastbuild
RUNBAT = run_last.bat

# Compilar: make complemento2
%:
	$(CC) $(CFLAGS) $@.c -o $@.exe
	@echo $@.exe > $(LASTBUILD)
	@echo Compilado: $@.exe

# Ejecutar: make run
run:
	@for /f %%i in ($(LASTBUILD)) do ( \
		echo @echo Ejecutando: %%i > $(RUNBAT) && \
		echo %%i >> $(RUNBAT) \
	) && call $(RUNBAT)

# Limpiar: make clean
clean:
	del /f /q *.exe $(LASTBUILD) $(RUNBAT)
