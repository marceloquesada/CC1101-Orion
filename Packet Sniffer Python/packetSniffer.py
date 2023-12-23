import os
import serial
from serial.tools import list_ports
from funcoesInternas import Separator

#Variavel para selecionar o diretorio do arquivo
diretorio = './Packet Sniffer Python/Registers-Config/'#'./Registers-Config/'

#Iniciando biblioteca serial
ser = serial.Serial()
#Variaveis para a comunicacao serial
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = 1
ser.setRTS(False)
ser.setDTR(False)

#Listar os documentos da pasta de configuracao de registradores
documentos = os.listdir(diretorio)

#Funcao para listar os possiveis arquivos de configuracao
def Listar():
    #Verifica o diretorio listado
    documentos = os.listdir(diretorio)
    #Ciclo entre os arquivos
    for documento in documentos:
        #Verifica se a extensao esta correta
        if '.txt' in documento:
            #Envia para o terminal
            print(documento)

#Latch para a interface no CMD
latch = True
#Variavel para registros
registros = []

#Loop de configuracao
while latch:
    #Print para o usuario
    Listar()
    #Receber input de usuario
    arquivoSelecionado = input('Escolha o arquivo de registradores (0 para sair): ')
    if arquivoSelecionado != '0':
        #Deixar usuario digitar somente nome do arquivo
        if not '.txt' in arquivoSelecionado:
            arquivoSelecionado += '.txt'
        #Verificar se o documento faz parte dos arquivos no diretorio
        if arquivoSelecionado in documentos:
            #Utilizar a funcao para separar a
            registros = Separator(open(diretorio+'/'+arquivoSelecionado).read())
            #Informar o numero de registradores encontrados
            print(len(registros),'registradores encontrados')
    else:
        #Terminar programa
        break

    #Continuando para configuracao do chip pelo arduino
    #Funcao para verificar portas
    ports = list_ports.comports()
    if ports != []:
        for port in ports:
            print(port.device)
        portSelecionado = input("Selecione a porta COM para iniciar a transferencia (0 para sair): ")
        if portSelecionado != '0':
            print("Entrou")
        else:
            break
    else:
        print("Nenhuma porta COM encontrada...")


    
print('Finalizando programa...')