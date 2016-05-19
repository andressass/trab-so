#############################################################################
# Processo de Usuario
# Aluno(s):	Andressa Sousa da Silveira 10/0053971
#	     	Rondinele Barbosa Prado 10/0039880
#	    
#############################################################################

#----------------------------------------------------------------------------
# Suporte
#----------------------------------------------------------------------------

Suporte somente aos seguintes métodos de bibliotecas java:

	java/io/PrintStream.println
	java/lang/StringBuffer.toString
	java/lang/StringBuffer.append

#----------------------------------------------------------------------------
# Compilação e execucao
#----------------------------------------------------------------------------

Para compilar digite:

	Em sistemas unix:
		$ make all_unix

	Em sistemas Windows:
		$ make all_win


Para executar digite:

	Em sistemas unix:
		$ /.jvm <arquivo_class> <String de caracteres>

		ou

		$ .jvm <arquivo_class> <String de caracteres>

		exemplo

		$ ./jvm docs/HelloWorld.class bla bla bla


	Em sistemas Windows:
		$. a.exe <arquivo_entrada> <String de caracteres>



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

docs/		- diretorio contendo a documentacao referente ao projeto

include/	- diretorio contendo arquivos de interface

src/		- diretorio contendo os arquivos .c

lib/		- classes exemplo

