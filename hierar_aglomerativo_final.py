#!/usr/bin/env python
import sys, random,string,math
import scipy
import os
from numpy import *
import csv

matriz2=ones((2465,2465))*1000.0
a=0
b=0

f=0
#distancia_centroides_v2
with open('distancia_centroides_v2.csv', 'rb') as csvfile:
     spamreader = csv.reader(csvfile, delimiter=',')
     for row in spamreader:
       x = ','.join(row)# ', '.join(row)
       arr=x.split(',') #2--name
       if(b>0):  
        for i in range(1,len(arr)):# todos los osciladores
          if(len(arr[i])>0):
           matriz2[b-1,i-1]=float(arr[i])
           if(float(arr[i])>f):
            f=float(arr[i]) 
          else: 
           matriz2[b,i]=1000.0
       b+=1    

size=2465
#matriz2= random.random((size, size))
etiquetas=range(1,size+1)


for i in range(0,size-1):
 for j in range(i+1,size):
  matriz2[i,j]=matriz2[j,i]


for i in range(0,size):
 matriz2[i,i]=1000000

##################33333

#print where(matriz == amin(matriz))#amin(matriz)
print 'matriz original'

#print matriz2#, amin(matriz2)#, matriz[1][1]
col, row = matriz2.shape

while(col>256):
 dis=amin(matriz2)
 x,y= where(matriz2 ==dis)
 ff=[]
 if(type(etiquetas[x[0]])!= int):
  if(type(etiquetas[y[0]])!= int):
   ff=etiquetas[x[0]]
   for i in etiquetas[y[0]]:
    ff.insert(0, i)
  else:
   ff=etiquetas[x[0]]
   ff.insert(0, etiquetas[y[0]])
 elif(type(etiquetas[y[0]])!= int):
  if(type(etiquetas[x[0]])!= int):
   ff=etiquetas[y[0]]
   for i in etiquetas[x[0]]:
    ff.insert(0, i)
  else:
   ff=etiquetas[y[0]]
   ff.insert(0, etiquetas[x[0]])
 else:
  ff.append(etiquetas[x[0]])
  ff.append(etiquetas[y[0]])

  #'nuevas distancias'
 new_d=(matriz2[y[0],:]+matriz2[x[0],:])/2.0
 if(y[0]>x[0]):
  new_d=delete(new_d, x[0], axis=0)
  new_d=delete(new_d, y[0]-1, axis=0)
 else:
  new_d=delete(new_d, y[0], axis=0)
  new_d=delete(new_d, x[0]-1, axis=0)

 val=[1000000]
 new_d2=insert(new_d, 0, val, 0)


 # 'se eliminan las filas'
 if(y[0]>x[0]):
  matriz2=delete(matriz2, x[0], axis=0)
  matriz2=delete(matriz2, y[0]-1, axis=0)
  matriz2=delete(matriz2, x[0], 1)
  matriz2=delete(matriz2, y[0]-1, 1)
  etiquetas.pop(x[0])
  etiquetas.pop(y[0]-1)
 else:
  matriz2=delete(matriz2, y[0], axis=0)
  matriz2=delete(matriz2, x[0]-1, axis=0)
  matriz2=delete(matriz2, y[0], 1)
  matriz2=delete(matriz2, x[0]-1, 1)
  etiquetas.pop(y[0])
  etiquetas.pop(x[0]-1)

 matriz2=insert(matriz2, 0, new_d, 1)
 matriz2=insert(matriz2, 0, new_d2, 0)

 etiquetas.insert(0, ff)
 #print dis, len(etiquetas), etiquetas
 col, row = matriz2.shape
 #print col, len(etiquetas)
 
#print dis, 
#for i in range(0,len(etiquetas)):


print etiquetas
