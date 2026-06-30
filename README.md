Forma de compilação: g++ main.cpp controlador.cpp cidade.cpp trajeto.cpp transporte.cpp passageiro.cpp viagem.cpp -o programa
Apos isso utliza "./programa" para inicializar
Persistência de Dados: Os arquivos só são salvos ao utilizar a opção de finalizar o programa (Opção 8). Se o programa parar por qualquer outro motivo, os dados não serão salvos.
Dados Salvos: São salvos unicamente os dados brutos cadastrados; os relatórios e históricos de viagens não serão guardados ao fechar o sistema.
Sensibilidade a Maiúsculas/Minúsculas: É necessário escrever exatamente o que está sendo pedido. Isso inclui o uso obrigatório de letras maiúsculas na hora de escolher o meio de transporte 
(T para Terrestre ou A para Aquático).
Entrada de Dados: O programa espera receber os tipos corretos de dados em cada campo. Digitar letras em campos numéricos (como distâncias, velocidades ou opções do menu) pode quebrar o fluxo de execução do sistema.
