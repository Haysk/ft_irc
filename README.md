#Correction
https://github.com/mharriso/school21-checklists/blob/master/ng_5_ft_irc.pdf

# RFC1459 fr: 
http://abcdrfc.free.fr/rfc-vf/rfc1459.html

# Reponse erreur
401 ERR_NOSUCHNICK
" :No such nick/channel"

Utilisé pour indiquer que le pseudonyme passé en paramètre à la commande n'est pas actuellement utilisé.

402 ERR_NOSUCHSERVER
" :No such server"

Utilisé pour indiquer que le nom du serveur donné n'existe pas actuellement.

403 ERR_NOSUCHCHANNEL
" :No such channel"

Utilisé pour indiquer que le nom de canal donné est invalide.

404 ERR_CANNOTSENDTOCHAN
" :Cannot send to channel"

Envoyé à un utilisateur qui (a) soit n'est pas dans un canal en mode +n ou (b) n'est pas opérateur (ou mode +v) sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.

405 ERR_TOOMANYCHANNELS
" :You have joined too many channels"

Envoyé à un utilisateur quand il a atteint le nombre maximal de canaux qu'il est autorisé à accéder simultanément, s'il essaie d'en rejoindre un autre.

406 ERR_WASNOSUCHNICK
" :There was no such nickname"

Renvoyé par WHOWAS pour indiquer qu'il n'y a pas d'information dans l'historique concernant ce pseudonyme.

407 ERR_TOOMANYTARGETS
" :Duplicate recipients. No message delivered"

Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE utilisant le format de destination utilisateur@hôte pour lequel utilisateur@hôte a plusieurs occurrences.

409 ERR_NOORIGIN
":No origin specified"

Message PING ou PONG sans le paramètre origine qui est obligatoire puisque ces commandes doivent marcher sans préfixe.

411 ERR_NORECIPIENT
":No recipient given ()"

Pas de destinataire.

412 ERR_NOTEXTTOSEND
":No text to send"

Pas de texte à envoyer.

413 ERR_NOTOPLEVEL
" :No toplevel domain specified"

Domaine principal non spécifié.

414 ERR_WILDTOPLEVEL
" :Wildcard in toplevel domain"

Joker dans le domaine principal

Les erreurs 412-414 sont renvoyées par PRIVMSG pour indiquer que le message n'a pas été délivré. ERR_NOTOPLEVEL et ERR_WILDTOPLEVEL sont les erreurs renvoyées lors d'une utilisation invalide de "PRIVMSG $" ou de "PRIVMSG #<hôte>".

421 ERR_UNKNOWNCOMMAND
" :Unknown command"

Renvoyé à un client enregistré pour indiquer que la commande envoyée est inconnue du serveur.

422 ERR_NOMOTD
":MOTD File is missing"

Le fichier MOTD du serveur n'a pas pu être ouvert.

423 ERR_NOADMININFO
" :No administrative info available"

Renvoyé par un serveur en réponse à un message ADMIN quand il y a une erreur lors de la recherche des informations appropriées.

424 ERR_FILEERROR
":File error doing <opération> on "

Message d'erreur générique utilisé pour rapporter un échec d'opération de fichier durant le traitement d'un message.

431 ERR_NONICKNAMEGIVEN
":No nickname given"

Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.

432 ERR_ERRONEUSNICKNAME
" :Erroneus nickname"

Renvoyé après la réception d'un message NICK qui contient des caractères qui ne font pas partie du jeu autorisé. Voir les sections 1 et 2.2 pour les détails des pseudonymes valides.

433 ERR_NICKNAMEINUSE
" :Nickname is already in use"

Renvoyé quand le traitement d'un message NICK résulte en une tentative de changer de pseudonyme en un déjà existant.

436 ERR_NICKCOLLISION
" :Nickname collision KILL"

Renvoyé par un serveur à un client lorsqu'il détecte une collision de pseudonymes (enregistrement d'un pseudonyme qui existe déjà sur un autre serveur).

441 ERR_USERNOTINCHANNEL
" :They aren't on that channel"

Renvoyé par un serveur pour indiquer que l'utilisateur donné n'est pas dans le canal spécifié.

442 ERR_NOTONCHANNEL
" :You're not on that channel"

Renvoyé par le serveur quand un client essaie une commande affectant un canal dont il ne fait pas partie.

443 ERR_USERONCHANNEL
" :is already on channel"

Renvoyé quand un client essaie d'inviter un utilisateur sur un canal où il est déjà.

444 ERR_NOLOGIN
" :User not logged in"

Renvoyé par un SUMMON si la commande n'a pas pu être accomplie, car l'utilisateur n'est pas connecté.

445 ERR_SUMMONDISABLED
":SUMMON has been disabled"

Renvoyé en réponse à une commande SUMMON si le SUMMON est désactivé. Tout serveur qui ne gère pas les SUMMON doit retourner cette valeur.

446 ERR_USERSDISABLED
":USERS has been disabled"

Retourné en réponse à une commande USERS si la commande est désactivée. Tout serveur qui ne gère pas les USERS doit retourner cette valeur.

451 ERR_NOTREGISTERED
":You have not registered"

Retourné par le serveur pour indiquer à un client qu'il doit être enregistré avant que ses commandes soient traitées.

461 ERR_NEEDMOREPARAMS
" :Not enough parameters"

Renvoyé par un serveur par de nombreuses commandes, afin d'indiquer que le client n'a pas fourni assez de paramètres.

462 ERR_ALREADYREGISTRED
":You may not reregister"

Retourné par le serveur à tout lien qui tente de changer les détails enregistrés (tels que mot de passe et détails utilisateur du second message USER)

463 ERR_NOPERMFORHOST
":Your host isn't among the privileged"

Renvoyé à un client qui essaie de s'enregistrer sur un serveur qui n'accepte pas les connexions depuis cet hôte.

464 ERR_PASSWDMISMATCH
":Password incorrect"

Retourné pour indiquer l'échec d'une tentative d'enregistrement d'une connexion dû à un mot de passe incorrect ou manquant.

465 ERR_YOUREBANNEDCREEP
":You are banned from this server"

Retourné après une tentative de connexion et d'enregistrement sur un serveur configuré explicitement pour vous refuser les connexions.

467 ERR_KEYSET
" :Channel key already set"

Clé de canal déjà définie.

471 ERR_CHANNELISFULL
" :Cannot join channel (+l)"

Impossible de joindre le canal (+l)

472 ERR_UNKNOWNMODE
"<caractère> :is unknown mode char to me"

Mode inconnu.

473 ERR_INVITEONLYCHAN
" :Cannot join channel (+i)"

Impossible de joindre le canal (+i).

474 ERR_BANNEDFROMCHAN
" :Cannot join channel (+b)"

Impossible de joindre le canal (+b).

475 ERR_BADCHANNELKEY
" :Cannot join channel (+k)"

Impossible de joindre le canal (+k).

481 ERR_NOPRIVILEGES
":Permission Denied- You're not an IRC operator"

Toute commande qui requiert le privilège d'opérateur pour opérer doit retourner cette erreur pour indiquer son échec.

482 ERR_CHANOPRIVSNEEDED
" :You're not channel operator"

Toute commande qui requiert les privilèges 'chanop' (tels les messages MODE) doit retourner ce message à un client qui l'utilise sans être chanop sur le canal spécifié.

483 ERR_CANTKILLSERVER
":You cant kill a server!"

Toute tentative d'utiliser la commande KILL sur un serveur doit être refusée et cette erreur renvoyée directement au client.

491 ERR_NOOPERHOST
":No O-lines for your host"

Si un client envoie un message OPER et que le serveur n'a pas été configuré pour autoriser les connexions d'opérateurs de cet hôte, cette erreur doit être retournée.

501 ERR_UMODEUNKNOWNFLAG
":Unknown MODE flag"

Renvoyé par un serveur pour indiquer que le message MODE a été envoyé avec un pseudonyme et que le mode spécifié n'a pas été identifié.

502 ERR_USERSDONTMATCH
":Cant change mode for other users"

Erreur envoyée à tout utilisateur qui essaie de voir ou de modifier le mode utilisateur d'un autre client.

# Le format de message en 'pseudo' BNF:
Les messages du protocole doivent être extraits du flux continu d'octets. La solution actuelle consiste à désigner deux caractères donnés, CR et LF, comme séparateurs de messages. Les messages vides sont ignorés en silence, ce qui permet l'usage d'une suite de CR-LF entre les messages sans problèmes supplémentaires.

Le message extrait est décomposé en un <préfixe>, et liste de paramètres correspondant soit au composant ou .

La représentation BNF de ceci est :
::= [':' <préfixe> ]
<préfixe> ::= | [ '!' ] [ '@' <hôte> ]
::= { } |
::= ' ' { ' ' }
::= [ ':' | ]

::= <Toute séquence non vide d'octets à l'exclusion de ESPACE, NUL, CR, LF, le premier d'entre eux étant différent de ':'>
::= <Toute suite, éventuellement vide, d'octets, à l'exception de NUL, CR et LF>
::= CR LF

NOTES:

est constitué uniquement de caractère(s) ESPACE (0x20). Notez particulièrement que la TABULATION et tout autre caractère de contrôle sont considérés comme ESPACE-NON-BLANC.

Après avoir extrait la liste de paramètres, tous les paramètres sont égaux, et correspondent soit à soit à . est une simple astuce syntaxique pour autoriser ESPACE dans le paramètre.

Le fait que CR et LF ne puissent pas apparaître dans la chaîne paramètre est une simple assertion. Cela pourrait changer dans le futur.

Le caractère NUL n'est pas spécial dans la construction du message, et pourrait a priori être à l'intérieur d'un message, mais cela complexifierait la gestion ordinaire des chaînes en C. C'est pourquoi NUL n'est pas autorisé dans les messages.

Le dernier paramètre peut être une chaîne vide.

L'utilisation d'un préfixe étendu ([ '!' ] [ '@' <hôte> ]) ne doit pas être utilisé dans la communication entre serveurs, et est destiné uniquement à la communication serveur vers client, dans le but de fournir au client des informations utiles à propos de l'origine du message sans nécessiter de requêtes supplémentaires.

La plupart des messages du protocole spécifient une sémantique additionnelle, et la syntaxe pour les chaînes de paramètres extraites est dictée par leur position dans la liste. Par exemple, de nombreuses commandes de serveurs vont considérer que le premier paramètre après la commande est la liste de destinataires, ce qui peut être décrit avec :
::= <à> [ "," < destinataire > ]
<à> ::= | < utilisateur > '@' | |
::= ('#' | '&') <chaîne canal>
::= <hôte>
<hôte> ::= voir RFC 952 [DNS:4] pour les détails sur les noms d'hôte autorisés
::= { | | <spécial> }
::= ('#' | '$') <chaîne canal>
<chaîne canal> ::= <n'importe quel code 8bits excepté ESPACE, BELL, NUL, CR, LF et virgule (,)>

Les autres paramètres sont :
::= { }
::= 'a' ... 'z' | 'A' ... 'Z'
::= '0' ... '9'
<spécial> ::= '-' | '[' | ']' | '' | '`' | '^' | '{' | '}'

::= <n'importe quel code 8bits excepté ESPACE (0x20), NUL(0x0), CR(0xd), et LF(0xa) >

# Reponses aux commandes
300 RPL_NONE

Numéro de réponse bidon. Inutilisé.

302 RPL_USERHOST
":[<réponse>{<réponse>}]"

Format de réponse utilisé par USERHOST pour lister les réponses à la liste des requêtes. La chaîne de réponse est composée ainsi :
<réponse> ::= [''] '=' <'+'|'-'><hôte>
Le '' indique si le client est enregistré comme opérateur. Les caractères '-' ou '+' indiquent respectivement si le client a défini un message AWAY ou non.

303 RPL_ISON
":[ {}]"

Format de réponse utilisé par ISON pour lister les réponses à la liste de requête.

301 RPL_AWAY
" :<message d'absence>"
305 RPL_UNAWAY
":You are no longer marked as being away"
306 RPL_NOWAWAY
":You have been marked as being away"

Ces trois réponses sont utilisées avec la commande AWAY (si elle est autorisée). RPL_AWAY est envoyé à tout client qui envoie un PRIVMSG à un client absent. RPL_AWAY n'est envoyé que par le serveur sur lequel le client est connecté. Les réponses RPL_UNAWAY et RPL_NOWAWAY sont envoyées quand un client retire et définit un message AWAY.

311 RPL_WHOISUSER
" <hôte> * :"
312 RPL_WHOISSERVER
" :"
313 RPL_WHOISOPERATOR
" :is an IRC operator"
317 RPL_WHOISIDLE
" :seconds idle"
318 RPL_ENDOFWHOIS
" :End of /WHOIS list"
319 RPL_WHOISCHANNELS
" :{[@|+]}"

Les réponses 311 à 313 et 317 à 319 sont toutes générées en réponse à un message WHOIS. S'il y a assez de paramètres, le serveur répondant doit soit formuler une réponse parmi les numéros ci-dessus (si le pseudo recherché a été trouvé) ou renvoyer un message d'erreur. Le '*' dans RPL_WHOISUSER est là en tant que littéral et non en tant que joker. Pour chaque jeu de réponses, seul RPL_WHOISCHANNELS peut apparaître plusieurs fois (pour les longues listes de noms de canaux). Les caractères '@' et '+' à côté du nom de canal indiquent si un client est opérateur de canal, ou si on l'a autorisé à parler dans un canal modéré. La réponse RPL_ENDOFWHOIS est utilisée pour marquer la fin de la réponse WHOIS.

314 RPL_WHOWASUSER
" <hôte> * :"
369 RPL_ENDOFWHOWAS
" :End of WHOWAS"

Lorsqu'il répond à un message WHOWAS, un serveur doit utiliser RPL_WHOWASUSER, RPL_WHOISSERVER ou ERR_WASNOSUCHNICK pour chacun des pseudonymes de la liste fournie. A la fin de toutes les réponses, il doit y avoir un RPL_ENDOFWHOWAS (même s'il n'y a eu qu'une réponse, et que c'était une erreur).

321 RPL_LISTSTART
"Channel :Users Name"
322 RPL_LIST
" <# visible> :"
323 RPL_LISTEND
":End of /LIST"

Les réponses RPL_LISTSTART, RPL_LIST, RPL_LISTEND marquent le début, les réponses proprement dites, et la fin du traitement d'une commande LIST. S'il n'y a aucun canal disponible, seules les réponses de début et de fin sont envoyées.

324 RPL_CHANNELMODEIS
" <paramètres de mode>"
331 RPL_NOTOPIC
" :No topic is set"
332 RPL_TOPIC
" :"

Lors de l'envoi d'un message TOPIC pour déterminer le sujet d'un canal, une de ces deux réponses est envoyée. Si le sujet est défini, RPL_TOPIC est renvoyée, sinon c'est RPL_NOTOPIC.

341 RPL_INVITING
" "

Renvoyé par un serveur pour indiquer que le message INVITE a été enregistré, et est en cours de transmission au client final.

342 RPL_SUMMONING
" :Summoning user to IRC"

Renvoyé par un serveur en réponse à un message SUMMON pour indiquer qu'il appelle cet utilisateur.

351 RPL_VERSION
". :"

Réponse du serveur indiquant les détails de sa version. est la version actuelle du programme utilisé (comprenant le numéro de mise à jour) et est utilisé pour indiquer si le serveur fonctionne en mode débugage.
Le champ peut contenir n'importe quel commentaire au sujet de la version, ou des détails supplémentaires sur la version.

352 RPL_WHOREPLY
" <hôte> <H|G>[*][@|+] : "
315 RPL_ENDOFWHO
" :End of /WHO list"

La paire RPL_WHOREPLY et RPL_ENDOFWHO est utilisée en réponse à un message WHO. Le RPL_WHOREPLY n'est envoyé que s'il y a une correspondance à la requête WHO. S'il y a une liste de paramètres fournie avec le message WHO, un RPL_ENDOFWHO doit être envoyé après le traitement de chaque élément de la liste, étant l'élément.

353 RPL_NAMREPLY
" :[[@|+] [[@|+] [...]]]"
366 RPL_ENDOFNAMES
" :End of /NAMES list"

En réponse à un message NAMES, une paire consistant de RPL_NAMREPLY et RPL_ENDOFNAMES est renvoyée par le serveur au client. S'il n'y a pas de canal résultant de la requête, seul RPL_ENDOFNAMES est retourné. L'exception à cela est lorsqu'un message NAMES est envoyé sans paramètre et que tous les canaux et contenus visibles sont renvoyés en une suite de message RPL_NAMEREPLY avec un RPL_ENDOFNAMES indiquant la fin.

364 RPL_LINKS
" : "
365 RPL_ENDOFLINKS
" :End of /LINKS list"

En réponse à un message LINKS, un serveur doit répondre en utilisant le nombre RPL_LINKS, et indiquer la fin de la liste avec une réponse RPL_ENDOFLINKS.

367 RPL_BANLIST
" "
368 RPL_ENDOFBANLIST
" :End of channel ban list"

Quand il liste les bannissements actifs pour un canal donné, un serveur doit renvoyer la liste en utilisant les messages RPL_BANLIST et RPL_ENDOFBANLIST. Un RPL_BANLIST différent doit être utilisé pour chaque identification de bannissement. Après avoir listé les identifications de bannissement (s'il y en a), un RPL_ENDOFBANLIST doit être renvoyé.

371 RPL_INFO
":<chaîne>"
374 RPL_ENDOFINFO
":End of /INFO list"

Un serveur répondant à un message INFO doit envoyer toute sa série d'info en une suite de réponses RPL_INFO, avec un RPL_ENDOFINFO pour indiquer la fin des réponses.

375 RPL_MOTDSTART
":- Message of the day - "
372 RPL_MOTD
":- "
376 RPL_ENDOFMOTD
":End of /MOTD command"

Lorsqu'il répond à un message MOTD et que le fichier MOTD est trouvé, le fichier est affiché ligne par ligne, chaque ligne ne devant pas dépasser 80 caractères, en utilisant des réponses au format RPL_MOTD. Celles-ci doivent être encadrées par un RPL_MOTDSTART (avant les RPL_MOTDs) et un RPL_ENDOFMOTD (après).

381 RPL_YOUREOPER
":You are now an IRC operator"

RPL_YOUREOPER est renvoyé à un client qui vient d'émettre un message OPER et a obtenu le statut d'opérateur.

382 RPL_REHASHING
" :Rehashing"

Si l'option REHASH est activée et qu'un opérateur envoie un message REHASH, un RPL_REHASHING est renvoyé à l'opérateur.

391 RPL_TIME
" :<chaîne indiquant l'heure locale du serveur>"

Lorsqu'il répond à un message TIME, un serveur doit répondre en utilisant le format RPL_TIME ci-dessus. La chaîne montrant l'heure ne doit contenir que le jour et l'heure corrects. Il n'y a pas d'obligation supplémentaire.

392 RPL_USERSSTART
":UserID Terminal Hôte"
393 RPL_USERS
":%-8s %-9s %-8s"
394 RPL_ENDOFUSERS
":End of users"
395 RPL_NOUSERS
":Nobody logged in"

Si le message USERS est géré par un serveur, les réponses RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS et RPL_NOUSERS sont utilisées. RPL_USERSSTART doit être envoyé en premier, suivi par soit une séquence de RPL_USERS soit un unique RPL_NOUSER. Enfin, vient un RPL_ENDOFUSERS.

200 RPL_TRACELINK
"Link <version & niveau de débugage> "
201 RPL_TRACECONNECTING
"Try. "
202 RPL_TRACEHANDSHAKE
"H.S. "
203 RPL_TRACEUNKNOWN
"???? []"
204 RPL_TRACEOPERATOR
"Oper "
205 RPL_TRACEUSER
"User "
206 RPL_TRACESERVER
"Serv S C <pseudo!utilisateur|!>@<hôte|serveur>"
208 RPL_TRACENEWTYPE
" 0 "
261 RPL_TRACELOG
"File <niveau de débugage>"

Les RPL_TRACE* sont tous renvoyés par le serveur en réponse à un message TRACE. Le nombre de messages retournés dépend de la nature du message TRACE, et s'il a été envoyé par un opérateur ou non. Il n'y a pas d'ordre définissant lequel doit être le premier. Les réponses RPL_TRACEUNKNOWN, RPL_TRACECONNECTING et RPL_TRACEHANDSHAKE sont toutes utilisées pour des connexions qui n'ont pas été complètement établies, et sont soit inconnues, soit toujours en cours de connexion, soit dans la phase terminale de la 'poignée de main du serveur'. RPL_TRACELINK est envoyé par tout serveur qui traite un message TRACE et doit le transmettre à un autre serveur. La liste de RPL_TRACELINK envoyée en réponse à une commande TRACE traversant le réseau IRC devrait refléter la connectivité actuelle des serveurs le long du chemin. RPL_TRACENEWTYPE est utilisé pour toute connexion qui n'entre pas dans les autres catégories, mais qui est néanmoins affichée.

211 RPL_STATSLINKINFO
" <messages envoyés> <octets envoyés> <message reçus> <octets reçus> "
212 RPL_STATSCOMMANDS
" "
213 RPL_STATSCLINE
"C <hôte> * "
214 RPL_STATSNLINE
"N <hôte> * "
215 RPL_STATSILINE
"I <hôte> * <hôte> "
216 RPL_STATSKLINE
"K <hôte> * <nom d'utilisateur> "
218 RPL_STATSYLINE
"Y <fréquence des PINGS> <fréquence de connexion> "
219 RPL_ENDOFSTATS
" :End of /STATS report"
241 RPL_STATSLLINE
"L <masque d'hôte> * "
242 RPL_STATSUPTIME
":Server Up %d days %d:%02d:%02d"
243 RPL_STATSOLINE
"O <masque d'hôte> * "
244 RPL_STATSHLINE
"H <masque d'hôte> * "

221 RPL_UMODEIS
"<chaîne de mode utilisateur>"

Pour répondre à une requête au sujet du mode du client, RPL_UMODEIS est renvoyé.

251 RPL_LUSERCLIENT
":There are users and invisible on servers"
252 RPL_LUSEROP
" :operator(s) online"
253 RPL_LUSERUNKNOWN
" :unknown connection(s)"
254 RPL_LUSERCHANNELS
" :channels formed"
255 RPL_LUSERME
":I have clients and servers"

Lors du traitement d'un message LUSERS, le serveur envoie un lot de réponses parmi RPL_LUSERCLIENT, RPL_LUSEROP, RPL_USERUNKNOWN, RPL_LUSERCHANNELS et RPL_LUSERME. Lorsqu'il répond, un serveur doit envoyer RPL_LUSERCLIENT et RPL_LUSERME. Les autres réponses ne sont renvoyées que si le nombre trouvé n'est pas nul.

256 RPL_ADMINME
" :Administrative info"
257 RPL_ADMINLOC1
":"
258 RPL_ADMINLOC2
":"
259 RPL_ADMINEMAIL
":"

Lorsqu'il répond à un message ADMIN, un serveur doit renvoyer les réponses RLP_ADMINME à RPL_ADMINEMAIL et fournir un texte de message avec chacune. Pour RPL_ADMINLOC1, on attend une description de la ville et de l'état où se trouve le serveur, suivie des détails de l'université et du département (RPL_ADMINLOC2), et finalement le contact administratif pour ce serveur (avec obligatoirement une adresse email) dans RPL_ADMINEMAIL.