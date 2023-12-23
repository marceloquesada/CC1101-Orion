def Separator(arquivo = str):
    #Variavel para retornar registros
    registros = []
    #Separar o arquivo por linhas
    for arq in arquivo.split('\n'):
        #Procurar os valores de registradores
        dados = arq.split('|')
        #Caso tenham todos os dados...
        if len(dados) == 4 :
            #...separar os enderecos
            registros.append(dados[1:3])
            #Indicar o registrador encontrado
            print('Encontrado:',dados[0])
    #Retornar os valores encontrados
    return registros