import os
import time

#Lista de ip
ip = []

#Buscamos nombre del equipo e ip de nuestro equipo
name = os.popen("logname").read()
ip3=os.popen("ip addr | grep 192.168").read() 
num3 = ip3.split('.')
num4 = ip3.split('/') 
numCon = num4[0].split('.')

#Buscamos las redes conectadas en un rango de 254
for i in range(61):
    os.system("clear")
    print("*-*-*Ejercicio #2 Sistemas Operativos - Nombre: Viorato Lozada Osmar-*-*-*")
    print("Fase 1 Buscar IP conectadas")
    print("Nombre del Equipo:"+name)
    print("IP de nuestro equipo: 192.168."+num3[2],"."+numCon[3])
    print("Buscando las redes conectadas.")
    lectura = "192.168."+num3[2]+"."+str(i+1)
    print("Lectura en Ejecución:"+str(lectura))
    print("IP Conectadas:\n"+str(ip))
    salida = os.popen("ping -c 1 "+str(lectura)+"| grep received").read()
    datos = salida.split(',')
    buscar = datos[1]
    if buscar.find("1") == 1: ip.append(str(lectura))

#Pausamos 5 seg el programa y limpiamos la consola
time.sleep(5)
os.system("clear")

#Realizamos la conexion con la ip que buscamos y conocemos
for j in range(len(ip)):
        print("Fase 2 Conexion")
        print("Conectando con:"+str(ip[j]))
        hname = os.popen("nslookup "+str(ip[j]+"| grep name")).read()
        dataname = hname.split('=')
        if len(dataname[0])!=0:
            nombrefinal = dataname[1].split('.')
            nf = nombrefinal[0].split(' ')
            print("La ip pertenece a:",nf[1])
            if ip[j] == "192.168.100.61":
                print("*Conectando con la IP",ip[j])
                os.system("sshpass -p contra scp /home/mxn/Course/Rangel/Python/2respaldo.py vm1@192.168.100.61:/home/vm1")
                print("Operacion copiar elemento realizada")
                os.system("sshpass -p contra ssh vm1@192.168.100.61 chmod +x /home/vm1/2respaldo.py")
                print("Permisos otorgados satisfactoriamente")
                os.system("sshpass -p contra ssh vm1@192.168.100.61 python3 /home/vm1/2respaldo.py")
                print("El archivo 2respaldo.py se ejecuto satisfactoriamente")
                os.system("sshpass -p contra scp vm1@192.168.100.61:/home/vm1/Respaldo.tar.gz /home/mxn/Course/Rangel/Python/")
                print("Los archivos comprimidos se encuentran en nuestro equipo")
                time.sleep(5)
                break

#Pausamos 5 seg el programa y limpiamos la consola
os.system("clear")
print("IP conectadas:")

#Si llegamos a esta parte del codigo los resultados fueron favorables
#Mostramos el total de ip y un mensaje final con el nombre del archivo comprimido
for h in range(len(ip)):
    print(ip[h])
print("Archivos dentro del equipo Host llevan el nombre de Respaldo.tar.gz")