# Taller 3 Estructura de Datos
# Sistema de Gestión de Transacciones Financieras

Autor 1: Anibal Alberto Gonzalez Veira, Rut: 20.303.483-0, Correo: anibal.gonzalez@alumnos.ucn.cl                    
Autor 2: Diego Andrés Véliz Muñoz, Rut: 20.797.904-K, Correo: diego.veliz@alumnos.ucn.cl

Comando para Compilacion: g++ Logic/main.cpp Domain/src/Banco.cpp Domain/src/Transaccion.cpp Domain/src/ArbolABB.cpp Domain/src/ArbolAVL.cpp -o main
Comando para Ejecutar: ./main

Se crean los siguientes objetos del tipo Transaccion con el archivo "transacciones.txt" atributos del siguiente tipo y nombre:
# ID(string),CuentaOrigen(string),CuentaDestino(string),Monto(double),Ubicacion(string),Fecha(string),Hora(string)

1,12345,54321,15000.0,Valparaiso,2023-06-30,10:30
2,03213,54322,5000.0,Rancagua,2023-06-30,11:00
3,98765,54323,20000.0,Desconocida,2023-06-30,11:30
4,00000,11111,151000.0,Coquimbo,2024-04-12,12:41
5,22222,33333,21000,Desconocida,2021-03-21,07:12
6,12345,01213,1000,Vallenar,2023-06-30,12:00
7,12345,54321,15000,Valparaiso,2023-06-30,12:05
8,12345,00000,4300,Valparaiso,2023-06-30,12:10
9,12345,01213,100000,Vallenar,2023-06-30,12:15
10,12345,54321,5000,Valparaiso,2023-06-30,12:20
11,12345,54321,1000,Desconocida,2023-06-30,12:25
12,12345,54321,200000,Valparaiso,2023-06-30,12:30

El Reporte de las Transacciones Fraudolentas y/o Sospechosas se guardaran en la carpeta Data, con el nombre de "transacciones_sospechosas.txt"

Para las transacciones sospechosas estan las siguientes reglas:
- Monto superior a 100000.
- Ubicacion con nombre "Desconocida".
- Frecuencia de transaccion alta en un corto periodo de tiempo (Máx. 3 transacciones por dia).
- Ubicaciones Diferentes en el mismo dia.
