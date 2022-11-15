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
	echo "gfd"tre" -> NE PAS LE GERER : wrong quote syntax
	echo "'hihi 'ret'" -> 'hihi 'ret'
	echo "$$" ->  récupère le pid de script courant : afficher $$
	echo "'$USER'" -> 'clorcery'
	echo "$USER" -> clorcery
	echo '$USER' -> $USER
	export "lol=echo mdr" -> $lol : mdr / "$lol" -> echo mdr: command not found
	
Exemples de dollar :
	echo "$PATH>test" -> /nfs/homes/mcloarec/.local/bin:/nfs/homes/mcloarec/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin>test
	echo lkom$PATH -> lkom/nfs/homes/mcloarec/.local/bin:/nfs/homes/mcloarec/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
	echo lkom$PATHt -> lkom
	echo lkom$PATH+test -> lkom/nfs/homes/mcloarec/.local/bin:/nfs/homes/mcloarec/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin+test
	echo lkom$PATH_test -> lkom
	echo lkom$PATHhf645test -> lkom
	echo lkom$PATH'test' -> lkom/nfs/homes/mcloarec/.local/bin:/nfs/homes/mcloarec/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bintest
	echo $USER&lol 

Exemples de redirection : 
	echo afd> -> wrong redirection syntax
	echo "esg>" -> "esg>"
	<infile [cmd] -> affiche le resultat
	<infile grep long>outfile -> affiche le resultat dans le outfile
	< infile [cmd] >'>' outfile -> prendre > et fichier sont >, outfile
	< infile [cmd] >'>'outfile -> prendre > et fichier >outfile
	
	 

OK Gestion de pipes :
- < essai grep g>ile7 | wc -w  > ile8 -> la sortie de la premiere partie du pipe est redirige vers un outfile et donc il n'y a rien dans l'entree du pipe et donc la sortie de la 2eme partie du pipe vaut 0 vu qu'il n'y a rien dans son entree
OK - a | t | (fini avec un espace seulement) -> doit afficher une erreur


OK Gestion de la premiere position : 

exemples :
- essai < grep o | cat essai -> bash: grep: No such file or directory // lit le contenu du fichier avec cat
		=> lit jusqu'au bout et ne coupe pas le prompt
- essai < grep o | cot essai -> bash: grep: No such file or directory // Command 'cot' not found 
		=> continue de lire puis s'arrête et relance un prompt
- grep < essai o | cot essai -> Command 'cot' not found
		=> s'arrête et relance un prompt
		
Builtins : 
- cd tout seul -> renvoi au HOME (ne pas gerer)
- cd + un path -> (gérer avec chdir)
- < infile cd -> renvoi au HOME (ne pas gerer)
- cd ~ -> renvoi au HOME (gerer)
-----------------------
  MEMO : 
- gerer : export lol -> export+var sans "=val", s'ajoute dans export mais pas dans env
		possibilite de faire une specificite dans add_env - si pas de egal l'ajouter seulement a export sans "=""" - l'ajouter avec un realloc.
- verifier les includes dans le h vraiment necessaire
OK -gestion des Pipes : ouverture de 2 fd pour 1 pipe, s'il a plus d'1 pipe alors fermer les fd ouvert au fur et a mesure. pour tester : ulimit -n 30; ./minishell
OK - chaine vide dans le split
OK - demander si lorsque une variable d'environnement est renseignée seule, est-ce dans la gestion d'erreur l'afficher puis code errno ou non
OK - Gérer lorsqu'on fait entrer dans le prompt directement
OK - ctrl + \ : gerer dans cat (Quit core dumped) et autre cmd ouvrant un prompt si pas d'opt
OK - retirer les quotes des noms des outfiles avant de les open
OK - gerer le point : . .. ./ ou un dossier - avant exec pour eviter de fork 
OK- gerer le double prompt du ctrtl + c du cat

OK - quand wstatus a une autre valeur de 0 il faut l'interprete dans le waitpid(wstatus = 256 == 1 - wstatus = 512 == 2) -> demander à Thibaud
OK - gerer les espaces avec echo : actuellement on affiche la chaine vide - ex : a "" b
OK - Ctrl C dans le double heredoc
bof- < /dev/urandom cat|head -n 50|wc -w > file | wc -l > file -> a tester 
OK - export lol="echo zouzou" puis $lol -> execute echo donc marque zouzou
OK - unlink le heredoc
OK - changer g_g par g_*nom de variable parlant*
OK - remplacer envp par env
OK - lorsque l'on se deplace avec cd - mettre a jour oldpwd + pwd dans env et export
- bouger ft_check_name_envcpy du fichier unset.c
OK - a gerer : echo '> >> < * ? [ ] | ; [ ] | && ( ) & # $  <<' -> les doubles pipes ne doivent pas etre verifier dans les quotes
- cat | cat < missing -> ne doit pas ouvrir le premier cat
- echo "exit_code ->$? user ->$USER home -> $HOME" -> enleve exit_code avant le $?...

NORME : 


OK test a faire :
< essai grep '>'>'>">'outfile [ok]
cat infile >earhb>>rB>> [ok]

