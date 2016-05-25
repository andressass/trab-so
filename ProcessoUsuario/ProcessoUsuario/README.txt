#############################################################################
# Processo de Usuario
# Alunos:	Andressa Sousa da Silveira 10/0053971
#	     	Rondinele Barbosa Prado 10/0039880
#	    
#############################################################################


#----------------------------------------------------------------------------
# Compilação e execucao
#----------------------------------------------------------------------------

Para compilar digite:

	$ make all


Para executar digite:

	$ ./procUsuario <N>
	ou
	$ ./bin/procUsuario <N>

Para executar N processos digite:

	$ ./criaNProcessos.sh
	(Definir no valor de N no arquivo criaNProcessos.sh)

#----------------------------------------------------------------------------
# Documentacao do sistema
#----------------------------------------------------------------------------

A documentacao do sistema eh gerada pelo software doxygen


A documentacao atual se encontra em docs/doxygen
		
	> Para abrir a documentacao entre em docs/documentacao_html
	  ou docs/doxygen/index.html


Para gerar uma nova documentacao eh necessaria a instalacao dos softwares:
	 
	> doxygen - Software de geracao de documentacao a partir de codigo
		> http://www.doxygen.org
	
	> graphviz - Software para a geracao de diagramas
		> http://www.graphviz.org

Para gerar uma nova documentação doxygen basta executar

	$ make doxygen 


#----------------------------------------------------------------------------
# Descricao dos diretorios
#----------------------------------------------------------------------------

bin/		- diretorio contendo os arquivos binarios executaveis

docs/		- diretorio contendo a documentacao e documentos necessários
		  para a execução do software (pag_processo_N)

include/	- diretorio contendo arquivos de interface

src/		- diretorio contendo os arquivos .c

lib/		- classes exemplo

