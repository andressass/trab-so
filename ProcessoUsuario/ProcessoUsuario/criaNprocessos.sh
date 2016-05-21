#############################################################################
# criaNprocessos
# Alunos: Andressa Sousa da Silveira e Rondinele Barbosa Prado
# Matriculas: 10/0053971 e 10/0039880
#
# Executa N processos de usuario
# 
#############################################################################

N=4

for (( i=0; i < N; i++ ));
do
echo "output: $i"
./procUsuario "$i" &
done