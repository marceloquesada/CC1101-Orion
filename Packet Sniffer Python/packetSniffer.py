import os
import serial
from serial.tools import list_ports
from funcoesInternas import Separator

#Variavel para selecionar o diretorio do arquivo
diretorio = './Registers-Config/'#'./Packet Sniffer Python/Registers-Config/'

#Iniciando biblioteca serial
ser = serial.Serial()
#Variaveis para a comunicacao serial
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
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
    print('---------------------')
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
            registros,hardware = Separator(open(diretorio+'/'+arquivoSelecionado).read())
            #Informar o numero de registradores encontrados
            print(len(registros),'registradores encontrados')
            #Continuar pelo programa
            break
    else:
        #Terminar programa
        latch = False
        break

#Continuando para configuracao do chip pelo arduino
while latch:
    print('---------------------')
    with open('./Registers-Config/ArduinoCode.txt','w') as arquivo:
        #Variaveis que serao escritas
        typedef = []
        spiRegConfig = []
        for reg in registros:
            #Escrever o define e o spi e salvar nas variaveis
            varRegistrador = hardware+'_'+reg[0]
            typedef.append('#define '+ varRegistrador+reg[1]+' //'+reg[3]+'\n')
            #Retirar os espacos
            varRegistrador = varRegistrador.replace(' ','')
            spiRegConfig.append(f'SpiWriteReg({varRegistrador},{reg[2]});\n')
        #Juntar as duas listas
        output = typedef + ['---------------------------------------------------\n'] + spiRegConfig
        #Salvar
        arquivo.writelines(output)
        latch = False
print('Finalizando programa...')