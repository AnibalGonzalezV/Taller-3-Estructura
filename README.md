# DemoTaller3

El archivo transacciones.txt tiene la siguiente estructura:
int,string,string,double,string,string,string
Id,CuentaOrigen,CuentaDestino,Monto,Ubicacion,Fecha,Hora

un ejemplo seria:
1,12345,54321,15000.0,New York,2023-06-30,10:30

El comando para compilarlo es:
g++ main.cpp Banco.cpp Transaccion.cpp ArbolABB.cpp ArbolAVL.cpp -o main     y luego ./main
