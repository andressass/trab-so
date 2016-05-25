#############################################################################
# criaNprocessos
# Alunos: Andressa Sousa da Silveira e Rondinele Barbosa Prado
# Matriculas: 10/0053971 e 10/0039880
#
# Executa N processos de usuario
# 
#############################################################################

# Ao alterar o valor de N, deve-se garantir a presenca dos arquivos
# [pag_processo_0..pag_processo_N] na pasta docs
N=5

#Numero de repeticoes
Rep=1

#Loop de execucao de processos
for (( j=0; j < Rep; j++ ));
do
    for (( i=0; i < N; i++ ));
    do
        echo "Executando Processo: $i"
        ./procUsuario "$i" &
    done
done