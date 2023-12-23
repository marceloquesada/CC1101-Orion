import os

#Variavel para selecionar o diretorio do arquivo
diretorio = './Packet Sniffer Python/Registers-Config/'
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

#Loop de configuracao
while latch:
    #Print para o usuario
    Listar()
    #Receber input de usuario
    arquivoSelecionado = input('Escolha o arquivo que deseja compilar: ')
    #Deixar usuario digitar somente nome do arquivo
    if not '.txt' in arquivoSelecionado:
        arquivoSelecionado += '.txt'
    if arquivoSelecionado in documentos:
            print(arquivoSelecionado)