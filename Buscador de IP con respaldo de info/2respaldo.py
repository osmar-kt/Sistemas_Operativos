import os
import subprocess

#Crea Carpetas
os.mkdir("Archivos")
os.mkdir("Archivos/mp4")
os.mkdir("Archivos/pdf")
os.mkdir("Archivos/jpg")
print("Carpetas creadas")

#Busca archivos mp4,pdf,jpg
whoami = subprocess.run('whoami',stdout=subprocess.PIPE)
whoami = whoami.stdout.decode('utf-8')
Path = '/home/' + whoami[:-1]
buscaMp4 = subprocess.run(['find',Path,'-name','*.mp4'],stdout=subprocess.PIPE)
buscaPdf = subprocess.run(['find',Path,'-name','*.pdf'],stdout=subprocess.PIPE)
buscaJpg = subprocess.run(['find',Path,'-name','*.jpg'],stdout=subprocess.PIPE)
mp4 = buscaMp4.stdout.decode('utf-8').split('\n')
pdf = buscaPdf.stdout.decode('utf-8').split('\n')
jpg = buscaJpg.stdout.decode('utf-8').split('\n')
print("Busqueda completada")

#Copia archivos
for p in mp4: 
    subprocess.run(['cp',p,"Archivos/mp4"],stderr=subprocess.PIPE)
for p in pdf: 
    subprocess.run(['cp',p,"Archivos/pdf"],stderr=subprocess.PIPE)
for p in jpg: 
    subprocess.run(['cp',p,"Archivos/jpg"],stderr=subprocess.PIPE)
print("Archivos copiados")

#Comprime archivos
subprocess.run(['tar','-cvzf','Respaldo.tar.gz','Archivos'])