def Separator(arquivo = str):
    #Variavel para retornar registros
    registros = []
    hardware = ''
    dados = ''
    #Separar o arquivo por linhas
    for arq in arquivo.split('\n'):
        #Procurar os valores de registradores
        dados = arq.split('|')
        #Caso tenham todos os dados...
        if len(dados) == 4 :
            #...separar os enderecos
            registros.append(dados)
            #Indicar o registrador encontrado
            print('Encontrado:',dados[0])
        else:
            dados = str(arq)
            if ('-' not in dados) and (len(dados) > 0):
                hardware = dados.replace('# Packet sniffer stttings for ','').replace(' ','')
    #Retornar os valores encontrados
    return registros, hardware