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
N=4

for (( i=0; i < N; i++ ));
do
echo "output: $i"
./procUsuario "$i" &
done