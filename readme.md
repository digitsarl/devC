



        	**************** MANIPULATION DES OBSERVATIONS *****************



Prérequis 

pour pouvoir exécuter ce programme, il faudrait avoir installé le compilateur gcc!

        


		  ********* Vérification de l'installation : ********** 

    

Ouvrez une console et tapez la commande gcc --version . Si vous obtenez comme résultat "commande introuvable", alors vous devriez installer gcc . 

Dépendant de votre système d'exploitation, suivez les étapes suivantes :

 

Sur Windows :
     nous ne disposons pas de ce compilateur par défaut, il va alors falloir l'installer ! 

  Nous allons installer gcc grâce à l'IDE Code::Blocks qui est gratuit et livrée avec notre compilateur . Pour ce faire, nous irons à l'adresse http://www.codeblocks.org/downloads/binaries pour la télécharger et nous choisirons la version ayant MINGW (codeblocks-20.03mingw-32bit-setup.exe version la plus récente actuellement ) . Puis on nous l'installerons .





		********** Exécution de l'application ***********

     Les différents fichiers du programme sont:

	-- Le dossier src contenant les différents fichiers sources
	-- Le dossier Executable
	-- Le dossier data contenant deux fichiers "observations.txt" (pour les observations) et "observations_externes.txt" (pour les observations des températures externes) 
	-- Le fichier makefile
	-- Le fichier readme.txt
	
	
	

	Pour executer le programme, tapez la commande 'make' et la liste des différentes observations s'affichera dans votre console.
	
	NB: Au cas où vous voulez utiliser un autre fichier des observations, veuillez à le copier dans le dossier "data" et à renseigner son nom dans le fichier Main.c.
	 



Édité le 10/08/2022
 
