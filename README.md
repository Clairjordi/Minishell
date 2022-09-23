# Minishell_gr

Cas a gerer : 
  -> infile non creer 
  -> variable environnement : ex PATH -> $PATH et "$PATH"
  -> le dernier file et celui qui contient l'information, les autres sont créés : ex echol "lol" > test > test1 > outfile -> seul oufile a l'information
  ->ctrl + \ : cat | ls puis ctrl + \ bash ecrit ^\ puis sort de l'attente de cat
  ->les signaux dans les heredoc
  -> resultat bash pour un ctrl + \ apres une attente de cat :
  	cat | grep q
		gdbgd
		tfnthf^\Quit (core dumped)
	ou
		qqqqqq
		qqqqqq
		^\Quit (core dumped)
  
  Plan d'action : 
  Parse
  	compter le nombre de quote (verifier si c'st un nombre pair)
  isoler les cmd
  trouver la cmd (son chemin et s'il elle existe)
  voir si on peut l'executer  
  builts in (cd (sans option) , pwd, echo + echo -n, export, unset, env, exit)
  gestion et creation des pipes (fichiers)
  gestion du heredoc
  gestion env
  

Exemple de quotes:
	echo "lol papa" -> lol papa
	echo "kwsv db'eb" -> kwsv db'eb
	echo "gfd"tre" -> NE PAS LE GERER donc retirer la double quote : gfdtre
	echo "'hihi 'ret'" -> 'hihi 'ret'
	echo "$$" ->  récupère le pid de script courant : afficher $$ ou recuperer le pid du fork ?
	echo "'$USER'" -> 'clorcery'
	echo "$USER" -> clorcery
	echo '$USER' -> $USER
	export "lol=echo mdr" -> $lol : mdr / "$lol" -> echo mdr: command not found


-----------------------
  MEMO : 
-gerer : export lol -> export+var sans "=val", s'ajoute dans export mais pas dans env
		possibilite de faire une specificite dans add_env - si pas de egal l'ajouter seulement a export sans "=""" - l'ajouter avec un realloc.
-verifier les includes dans le h vraiment necessaire
-gestion des Pipes : ouverture de 2 fd pour 1 pipe, s'il a plus d'1 pipe alors fermer les fd ouvert au fur et a mesure. pour tester : ulimits -30
-
